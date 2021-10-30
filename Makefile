NAME		=	Headermaker


BIN = /usr/bin/Headermaker

UNAME = $(shell uname)

ifeq ($(UNAME), Linux)
	BIN = /usr/bin/Headermaker
endif
ifeq ($(UNAME), Darwin)
	BIN = /usr/local/bin/Headermaker
endif

# --   Directory   -- #
OBJ_DIR     =	objs

INC_DIR		=	.

# --  Search All files in SRCS  -- #
SRC_DIR = src
SRCSS =	src/main.cpp

SRCS = $(SRCSS:src/%.cpp=%.cpp)
PWD = $(shell pwd)
HOME = $(shell echo $HOME)

# --  Redirection in OBJS  -- #
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:%.cpp=%.o))

CC			=	clang++
CFLAGS      =

all :
	mkdir -p $(OBJ_DIR)
	make $(NAME) --no-print-directory

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -o $@ -c $< -I $(INC_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

install: re
		sudo cp Headermaker $(BIN)
		make fclean
installinpath: re		
		echo "PATH=PATH:"$(PWD) >> $(HOME)/.zshrc

.PHONY: all clean fclean re
