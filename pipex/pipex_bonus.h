/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 20:40:13 by asouinia          #+#    #+#             */
/*   Updated: 2022/03/17 21:11:31 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_PIPEX_H
# define SO_PIPEX_H
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <errno.h>
# include "./libft/libft.h"

typedef struct s_cmd
{
	
	int	input[2];
	int	pipefd[2];
}				t_cmd;

typedef struct s_d_list
{
	int				content;
	struct s_d_list	*next;
	struct s_d_list	*prev;
}				t_d_list;
//!			s_d_list_0.c
t_d_list	*ft_d_lstnew(int content);
void		ft_d_lstadd_front(t_d_list **lst, t_d_list *new);
int			ft_d_lstsize(t_d_list *lst);
t_d_list	*ft_d_lstlast(t_d_list *lst);
void		ft_d_lstadd_back(t_d_list **lst, t_d_list *new);
//!			s_d_list_1.c
void		ft_d_lstdelone(t_d_list *lst);
void		ft_d_lstclear(t_d_list **lst);
void		ft_d_lstiter(t_d_list *lst, void (*f)(int));
void		ft_d_lstdelfront(t_d_list **lst);
void		ft_d_lstiter_back(t_d_list *lst, void (*f)(int));

void	loop_cmds(int argc, char **argv, char **envp );
int		exec_cmmand(int	*inout, char *cmd, char **envp, int *fdpipe);
char	*get_env_var(char **envp, char *env_var);
void	free_2d(char **ptr);
char	**get_paths(char **envp);
char	*get_cmd_full_path(char **envp, char *cmd);

#endif
