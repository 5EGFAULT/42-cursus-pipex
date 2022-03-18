/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:30:11 by asouinia          #+#    #+#             */
/*   Updated: 2022/03/18 12:18:52 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_PIPEX_H
# define SO_PIPEX_H
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <errno.h>
# include "./libft/libft.h"

void	loop_cmds(int argc, char **argv, char **envp );
int		exec_cmmand(int	*inout, char *cmd, char **envp, int *fdpipe);
char	*get_env_var(char **envp, char *env_var);
void	free_2d(char **ptr);
char	**get_paths(char **envp);
char	*get_cmd_full_path(char **envp, char *cmd);

#endif
