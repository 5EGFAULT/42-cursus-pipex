NAME	:= pipex
SRC		:=  env.c    main.c  ft_split.c ft_substr.c path.c   utils.c s_d_list_0.c s_d_list_1.c pipe.c ft_strjoin.c ft_strlen.c ft_strncmp.c
SRCB	:=  env_bonus.c ft_split_bonus.c ft_substr_bonus.c   main_bonus.c   path_bonus.c   utils_bonus.c s_d_list_0_bonus.c s_d_list_1_bonus.c get_next_line_bonus.c get_next_line_utils_bonus.c  pipe_bonus.c ft_strjoin_bonus.c ft_strlen_bonus.c ft_strncmp_bonus.c
OBJ		:= $(patsubst %.c, %.o, $(SRC)) 
OBJB	:= $(patsubst %.c, %.o, $(SRCB)) 
CC		:= gcc
FLAGS	:= -Wall -Wextra -Werror  #-g -fsanitize=address 

.PHONY: all clean fclean re bonus

all: $(NAME)
$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) -o $(NAME)
%.o: %.c
	$(CC) $(FLAGS) -c $<  -o $@
clean:
	@rm -f $(OBJ) $(OBJB)
fclean: clean
	@rm -f $(NAME)
re: fclean all
bonus: $(OBJB)
	@$(CC) $(FLAGS) $(OBJB) -o $(NAME)