/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 21:01:27 by asouinia          #+#    #+#             */
/*   Updated: 2022/03/19 17:35:37 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"

static void	setio(t_d_list *files, t_d_list *tmp, t_cmd *cc)
{
	if (tmp->prev)
		cc->inout[0] = ((t_cmd *)tmp->prev->content)->pipefd[0];
	else
		cc->inout[0] = ((t_file *)files->content)->fd;
	if (cc->pipefd)
		cc->inout[1] = cc->pipefd[1];
	else
		cc->inout[1] = ((t_file *)ft_d_lstlast(files)->content)->fd;
}

void	loop_cmds(t_d_list *files, t_d_list *cmds, char **envp, int argc)
{
	t_d_list	*tmp;
	t_cmd		*cc;
	int			i;

	tmp = cmds;
	if (((t_file *)files->content)->fd < 0)
	{
		close(((t_cmd *)tmp->content)->pipefd[1]);
		tmp = cmds->next;
	}
	while (tmp)
	{
		cc = tmp->content;
		setio(files, tmp, cc);
		exec_cmmand(cc, envp);
		close(cc->inout[1]);
		close(cc->inout[0]);
		tmp = tmp->next;
	}
	i = 1;
	while (++i < argc)
		wait(NULL);
}

static char	ft_quote(char *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return (' ');
	while (cmd[i] && cmd[i] != '"' && cmd[i] != '\'')
		++i;
	if (cmd[i] != '\0')
		return (cmd[i]);
	return (' ');
}

static void	exec_inter(t_cmd *cmd, char **envp)
{
	char	**splited_cmd;
	char	*str;

	if (ft_quote(cmd->cmd) == ' ')
		splited_cmd = ft_split(cmd->cmd, ' ');
	else
		splited_cmd = ft_new_split(cmd->cmd, ft_quote(cmd->cmd));
	if (!splited_cmd)
	{
		perror("pipex: ");
		exit(1);
	}
	str = get_cmd_full_path(envp, splited_cmd[0]);
	if (access(str, X_OK) < 0)
	{
		write(2, "pipex: command not found : ", 28);
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
		exit(127);
	}
	execve(str, splited_cmd, envp);
	perror("pipex: ");
	exit(errno);
}

int	exec_cmmand(t_cmd *cmd, char **envp)
{
	int		pid;

	pid = fork();
	if (pid < 0)
	{
		perror("pipex: ");
		exit(1);
	}
	if (pid == 0)
	{
		if (dup2(cmd->inout[0], 0) < 0 || dup2(cmd->inout[1], 1) < 0)
		{
			perror("pipex: ");
			exit(errno);
		}
		close(cmd->inout[0]);
		close(cmd->inout[1]);
		if (cmd->pipefd)
		{			
			close(cmd->pipefd[0]);
			close(cmd->pipefd[1]);
		}
		exec_inter(cmd, envp);
	}
	return (pid);
}
