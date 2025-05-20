NAME =	truth_table

SRC_DIR		=	./src/
OBJ_DIR		=	obj/

IMPS_DIR	=	./includes/implementations/
HDRS_DIR	=	./includes/headers/

MAIN_INC	= -I $(HDRS_DIR) -I $(IMPS_DIR)

IMPS		=	$(shell find $(IMPS_DIR) -type f -name "*.ipp")
HDRS		= 	$(shell find $(HDRS_DIR) -type f -name "*.hpp")

SRC			=	main.cpp   \

OBJ			=	$(addprefix $(OBJ_DIR), $(SRC:.cpp=.o))

CC				=	g++
CFLAGS			=	-Wall -Wextra -Werror -std=c++11

$(OBJ_DIR)%.o:	$(SRC_DIR)%.cpp $(HDRS) $(IMPS) Makefile
		@mkdir -p $(OBJ_DIR)
		$(CC) ${CFLAGS}  $(MAIN_INC) -o $@ -c $<

$(NAME)		:	$(OBJ) $(HDRS) $(IMPS)
		$(CC) $(CFLAGS) $(OBJ) $(MAIN_INC) -o $(NAME)

all			:	$(NAME)

clean		:
		@rm -rf $(OBJ_DIR) $(OBJ_BONUS_DIR)

fclean		:	clean
		@rm -rf $(NAME) $(NAME_BONUS)

re			:	fclean	all

.PHONY		:	all clean fclean re