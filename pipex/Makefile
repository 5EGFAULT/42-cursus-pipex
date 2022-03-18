NAME	:= pipex
SRC		:=  env.c    main.c   path.c   utils.c s_d_list_0.c s_d_list_1.c pipe.c
SRCB	:=  env_bonus.c    main_bonus.c   path_bonus.c   utils_bonus.c s_d_list_0_bonus.c s_d_list_1_bonus.c get_next_line_bonus.c get_next_line_utils_bonus.c  pipe_bonus.c
OBJ		:= $(patsubst %.c, %.o, $(SRC)) 
OBJB	:= $(patsubst %.c, %.o, $(SRCB)) 
CC		:= gcc
FLAGS	:= -Wall -Wextra -Werror  #-g -fsanitize=address 
LIBFT	:= ./libft/libft.a

.PHONY: all clean fclean re bonus

all: $(NAME)
$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(FLAGS)  $(LIBFT) $(OBJ) -o $(NAME)
%.o: %.c
	$(CC) $(FLAGS) -c $<  -o $@
$(LIBFT):
	@make -C ./libft
clean:
	@rm -f $(OBJ) $(OBJB)
	@make -C ./libft fclean
fclean: clean
	@rm -f $(NAME)
re: fclean all
bonus: $(LIBFT) $(OBJB)
	@$(CC) $(FLAGS) $(LIBFT) $(OBJB) -o $(NAME)