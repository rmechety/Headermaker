NAME		=	Headermaker

# --   Directory   -- #
OBJ_DIR     =	objs

INC_DIR		=	.

# --  Search All files in SRCS  -- #
SRC_DIR = src
SRCSS =	src/main.cpp

SRCS = $(SRCSS:src/%.cpp=%.cpp)


# --  Redirection in OBJS  -- #
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:%.cpp=%.o))

CC			=	clang++
CFLAGS      =   -Wall -Wextra -Werror

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

.PHONY: all clean fclean re