
#define HEADER                                                                 \
	"/* "                                                                      \
	"************************************************************************" \
	"** */\n"                                                                  \
	"/*                                                                      " \
	"      */\n"                                                               \
	"/*                                                        :::      "      \
	"::::::::   */\n"                                                          \
	"/*   main.c                                             :+:      :+:    " \
	":+:   */\n"                                                               \
	"/*                                                    +:+ +:+         "   \
	"+:+     */\n"                                                             \
	"/*   By: rmechety <rmechety@student.42.fr>          +#+  +:+       +#+  " \
	"      */\n"                                                               \
	"/*                                                +#+#+#+#+#+   +#+     " \
	"      */\n"                                                               \
	"/*   Created: 2021/07/08 13:02:43 by rmechety          #+#    #+#       " \
	"      */\n"                                                               \
	"/*   Updated: 2021/10/17 15:02:09 by rmechety         ###   ########.fr " \
	"      */\n"                                                               \
	"/*                                                                      " \
	"      */\n"                                                               \
	"/* "                                                                      \
	"************************************************************************" \
	"** */\n"

#include <dirent.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <unistd.h>

int ft_is_proto(std::string line)
{
	unsigned long ret;
	if (line[0] == ' ' || line[0] == '\t')
		return 0;
	if (line[0] == '*' || line[0] == '/')
		return 0;
	if (line.find("static") != line.npos && line.find("static") == 0)
		return 0;
	if ((line.find(" ") != line.npos && line.find(" ") != 0 &&
		 line.find(" ") != 1) ||
		(line.find("\t") != line.npos && line.find("\t") != 0 &&
		 line.find("\t") != 1))
	{

		ret = line.find(" ");
		if (ret == line.npos || line.find("\t") < ret)
			ret = line.find("\t");

		if (line.find("(") != line.npos && line.find("(") > ret)
				return 1;
	}
	return 0;
}

std::string ft_get_file_prototypes(std::string srcfilename)
{
	std::string prototypes;
	std::string line;
	std::fstream srcfile;

	srcfile.open(srcfilename, std::fstream::in);

	while (std::getline(srcfile, line))
	{
		if (ft_is_proto(line))
			prototypes.append(line + ";" + "\n");
	}
	return prototypes;
}

std::string ft_get_all_proto_of_src(std::string dirname)
{
	std::string prototypes;
	DIR *dir;
	struct dirent *current;

	if ((dir = opendir(dirname.c_str())) == NULL)
	{
		std::cout << "error opening the dir : " << dirname << std::endl;
		std::exit(1);
	}
	while ((current = readdir(dir)) != NULL)
	{

		if (current->d_type == DT_REG && std::string(current->d_name).find(".c") != std::string(current->d_name).npos)
		{
				prototypes.append("/* "
						"------------------------------------------------"
						"-------------------------- */\n");
			int len = std::string("FILE = " + dirname + "/" + std::string(current->d_name)).length();

			int nbspace = 80 - 4 - len;
			if(nbspace > 0)
			{

				std::string spaces( nbspace / 2, ' ');

				prototypes.append("/*" + spaces);

				prototypes.append("FILE = " + dirname + "/" +  std::string(current->d_name));

				if(len % 2 == 1)
					prototypes.append(spaces + " " + "*/\n");
				else
					prototypes.append(spaces + "*/\n");
			}
			prototypes.append("/* "
							  "------------------------------------------------"
							  "-------------------------- */\n");
			prototypes.append(ft_get_file_prototypes(dirname + "/" + current->d_name) + "\n");
		}

		if (current->d_type == DT_DIR && std::string(current->d_name) != ".." &&
			std::string(current->d_name) != "." && std::string(current->d_name).find(".") != 0)
		{
			prototypes.append(ft_get_all_proto_of_src(
				dirname + "/" + std::string(current->d_name)));
		}
	}
	return prototypes;
}

int main(int ac, char **av)
{
	if (ac < 3)
	{
		std::cout << "You need to give the src folder and the header you want "
					 "to create"
				  << std::endl;
		return 0;
	}

	std::fstream header;

	std::string srcfolder(av[1]);
	std::string header_name(av[2]);
	std::string header_cap(header_name);

	if (header_name[0] != '/')
		header_name = std::string(getcwd(NULL, 0)) + "/" + header_name;

	header.open(header_name, std::fstream::out);

	if (!header)
	{
		std::cout << "Error opening the header file : " << header_name
				  << std::endl;
		std::exit(1);
	}

	header << HEADER << std::endl;

	if (header_cap.find(".h") != header_cap.npos)
		header_cap.erase(header_cap.find(".h"), header_cap.find(".h") + 2);

	if (header_cap.find("/") != header_cap.npos)
		header_cap = header_cap.substr(header_cap.rfind("/") + 1);

	if (srcfolder.find("/") != srcfolder.npos && srcfolder.find("/") != 1)
		srcfolder.erase(srcfolder.rfind("/"));

	for (char &c : header_cap)
	{
		c = toupper(c);
	}

	header << "#ifndef " << header_cap << "_H" << std::endl;
	header << "# define " << header_cap << "_H" << std::endl << std::endl;

	if (ac > 4)
	{
		if (std::string(av[3]) == "-inc")
		{
			int i = 4;
			std::string to_inc;

			while (i < ac)
			{
				to_inc = av[i];
				if (to_inc.find(".h") == to_inc.npos)
					to_inc.append(".h");
				header << "#include \"" << to_inc << "\"" << std::endl;
				i++;
			}

			header << std::endl;
		}
	}

	header << ft_get_all_proto_of_src(srcfolder) << std::endl;

	header << "#endif" << std::endl;
	header.close();
}