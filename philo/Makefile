NAME 			= philo
CC				= gcc
CFLAGS			= -Wall -Wextra -Werror #-g -fsanitize=thread


INCLUDE 		= -Iinc 


HEADER			= inc/philo.h

SRC_DIR 		= src/
OBJ_DIR 		= obj/
SRC 			:=	main.c  monitor.c  philo.c  utils.c	parse.c		
SRC				:= $(addprefix $(SRC_DIR), $(SRC))
OBJ				= $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

#_____Colors_____#
DEF_COLOR	=	\033[1;39m
WHITE_BOLD	=	\033[1m
RED			=	\033[1;31m
GREEN		=	\033[1;32m
YELLOW		=	\033[1;33m
BLUE		=	\033[1;34m
CIAN		=	\033[1;36m


all : $(NAME)

re : fclean all

$(NAME) : $(OBJ) 
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "🤔 $(RED)$(NAME)s $(BLUE)are ready to work!$(DEF_COLOR)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER) Makefile | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "$(WHITE_BOLD)Object$(YELLOW) $@ $(GREEN)created!$(DEF_COLOR)"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "$(WHITE_BOLD)Created obj dir!$(DEF_COLOR)"

clean :
	@rm -rf $(OBJ_DIR)
	@echo "$(WHITE_BOLD)🧼 Removed object files from philo!$(DEF_COLOR)"

fclean : clean 
	@rm -f $(NAME)
	@echo "$(WHITE_BOLD)🧼 Removed $(NAME) file!$(DEF_COLOR)"

test : 

.PHONY : all clean fclean re
