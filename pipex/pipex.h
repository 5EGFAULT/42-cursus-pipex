/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 20:40:13 by asouinia          #+#    #+#             */
/*   Updated: 2022/03/18 20:34:12 by asouinia         ###   ########.fr       */
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
	int		idx;
	char	*cmd;
	int		inout[2];
	int		*pipefd;
}				t_cmd;

typedef struct s_file
{
	int		idx;
	char	*file;
	int		fd;
}				t_file;

typedef struct s_d_list
{
	void			*content;
	struct s_d_list	*next;
	struct s_d_list	*prev;
}				t_d_list;

void	del_content(void *);

//!			s_d_list_0.c
t_d_list	*ft_d_lstnew(void *content);
void		ft_d_lstadd_front(t_d_list **lst, t_d_list *new);
int			ft_d_lstsize(t_d_list *lst);
t_d_list	*ft_d_lstlast(t_d_list *lst);
void		ft_d_lstadd_back(t_d_list **lst, t_d_list *new);
//!			s_d_list_1.c
void		ft_d_lstdelone(t_d_list *lst, void (*del)(void *));
void		ft_d_lstclear(t_d_list **lst, void (*del)(void *));
void		ft_d_lstiter(t_d_list *lst, void (*f)(void *));
void		ft_d_lstdelfront(t_d_list **lst, void (*del)(void *));
void		ft_d_lstiter_back(t_d_list *lst, void (*f)(void *));
void		loop_cmds(t_d_list *files, t_d_list *cmds, char **envp , int argc);
int			exec_cmmand(t_cmd *cmd, char **envp);
char		*get_env_var(char **envp, char *env_var);
void		free_2d(char **ptr);
char		**get_paths(char **envp);
char		*get_cmd_full_path(char **envp, char *cmd);
t_cmd		*new_cmd(char *cmd, int idx, int islast);
t_file		*new_file(char *file, int idx, int perm);
int			init_files(int argc, char **argv, t_d_list **files);
void		init_cmds(int argc, char **argv, t_d_list **cmds, int start);
#endif
