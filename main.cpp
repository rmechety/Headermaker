


#include <iostream>
#include <unistd.h>



//Parcourir dossier src a la recherche de .c

//Ouvrir chaque .c et stocker les prototypes de chaques fonctions

#include <dirent.h>
#include <iomanip>
#include <fstream>



//type whitespace name parenthesise type paramname type paramname type paramname parenthesise endl openbrace
int ft_is_proto(std::string line)
{
    if((line.find(" ") != line.npos && line.find(" ") != 0 && line.find(" ") != 1) || 
        (line.find("\t") != line.npos && line.find("\t") != 0 && line.find("\t") != 1))
    {
        int ret = line.find(" ");
        if(ret == line.npos || ret == 0 || ret == 1)
            ret = line.find("\t");
        if(line.find("(") != line.npos && line.find("(") > ret)
            return 1;
    }
    return 0;
}

std::string *ft_get_file_prototypes(std::string srcfilename)
{
    std::string *prototypes;

    std::fstream srcfile;

    srcfile.open(srcfilename,ios::in);
    
    std::string line;
    std::string nxtline;
    while(std::getline(file, line))
    {
        if(ft_is_proto(line))
        {
            prototypes.append(line);
        }
    }

    return *prototypes;
}

int main(int ac, char **av)
{
    int nbofsrcfile = 0;
    DIR *dir;
    struct dirent *current;
    std::string *prototypes ;

    if(ac < 3)
    {
        std::cout << "You need to give the src folder and the header you want to create"<< std::endl;
        return 0;
    }

    std::string srcfolder(av[1]);
    std::string header_name(av[1]);
    if(header_name[0] != '/')
        header_name = getcwd(NULL,0) + header_name;

    if((dir = opendir(srcfolder)) == NULL)
    {
        std::cout << "error opening the dir : " << srcfolder << std::endl;
    }
    while((current = readdir(dir)) != NULL)
    {
        if(current.d_type == DT_REG)
        {
            prototypes = ft_get_file_prototypes();
            nbofsrcfile++;
        }
    }

}