NAME =	inverse

SRC_DIR		=	./src/
OBJ_DIR		=	obj/

SRC			=	main.cpp   \

OBJ			=	$(addprefix $(OBJ_DIR), $(SRC:.cpp=.o))

CC				=	g++
CFLAGS			=	-Wall -Wextra -Werror -std=c++11

$(OBJ_DIR)%.o:	$(SRC_DIR)%.cpp Makefile
		@mkdir -p $(OBJ_DIR)
		$(CC) ${CFLAGS} -o $@ -c $<

$(NAME)		:	$(OBJ)
		$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

all			:	$(NAME)

clean		:
		@rm -rf $(OBJ_DIR)

fclean		:	clean
		@rm -rf $(NAME) $(NAME_BONUS)

re			:	fclean	all

.PHONY		:	all clean fclean re