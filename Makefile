NAME			= pipex

MANDATORY_SRCS	= mandatory/pipex.c mandatory/pipex_utils.c mandatory/path_utils.c
MANDATORY_DIR	= mandatory

BONUS_SRCS		=
BONUS_DIR		= bonus

INCLUDES 		= -Imandatory -Ibonus -Ilibft/includes


CC 				= cc
CFLAGS 			= -Wall -Wextra -Werror 
LIBFLAGS		= -Llibft -lft



M_OBJS = $(MANDATORY_SRCS:.c=.o)

%.o:%.c Makefile 
	@$(CC) $(CFLAGS) $(INCLUDES) -c  $< -o $@

all: $(NAME)


$(NAME) : Makefile $(M_OBJS)
	@make -s -C libft
	$(CC) $(CFLAGS) $(INCLUDES) $(M_OBJS)  $(LIBFLAGS) -o $(NAME)

clean:
	@rm -f $(M_OBJS)
	@make  clean -s -C libft

fclean: clean
	@rm -f $(NAME)
	@make fclean -s -C libft

re: fclean all

.PHONY: all clean fclean re