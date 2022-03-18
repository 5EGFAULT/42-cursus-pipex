/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 20:42:40 by asouinia          #+#    #+#             */
/*   Updated: 2022/03/18 16:33:43 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_d_list *cmds;
	t_d_list *files;


	cmds = NULL;
	files = NULL;
	init_files(argc, argv, &files);
	init_cmds(argc, argv, &cmds);
	loop_cmds(files, cmds, envp);
	//system("leaks pipex");
	while (1)
	{
		;
	}
	//system("lsof | grep pipex"); // only get 0 in 1 out 2  err
	return (0);
}
void	init_files(int argc, char **argv, t_d_list **files)
{
	t_file		*file;
	file = new_file(argv[1], 1, O_RDONLY);
	ft_d_lstadd_back(files, ft_d_lstnew(file));
	file = new_file(argv[argc - 1], argc - 1, O_WRONLY | O_TRUNC | O_CREAT);
	ft_d_lstadd_back(files, ft_d_lstnew(file));
}
void	init_cmds(int argc, char **argv, t_d_list **cmds)
{
	t_cmd *cmd;
	int	i;

	i = 1;
	while (++i < argc - 2)
	{
		cmd = new_cmd(argv[i], i, 0);
		ft_d_lstadd_back(cmds, ft_d_lstnew(cmd));
	}
	cmd = new_cmd(argv[argc - 2], argc - 2, 1);
	ft_d_lstadd_back(cmds, ft_d_lstnew(cmd));		
}

void printc(void *s)
{
	t_cmd *c = s;
	fprintf(stderr, " cmmand  %s \n", c->cmd );
}
void printfi(void *s)
{
	t_file *c = s;
	fprintf(stderr, " file :  %s \n", c->file );
}

void	loop_cmds(t_d_list *files, t_d_list *cmds, char **envp )
{
	int fdinout[2];
	//int fdpipe[2];
	t_cmd	*cc;
	int i; 

	fdinout[0] = ((t_file *)files->content)->fd;	
	cc = cmds->content;
	ft_d_lstiter(cmds, printc);
	ft_d_lstiter(files, printfi);
	exit(0);
	if (cc->pipefd)
	{
		cc->inout[1] = ((t_cmd *)cmds->content)->pipefd[1];
	}
	else
	{
		cc->inout[1] = 2;
	}
	cc->inout[0] = fdinout[0];	
	i = 1;
	exec_cmmand(cmds->content, envp);	
	fdinout[1] = ((t_file *)ft_d_lstlast(files)->content)->fd;
	//close(fdpipe[1]);
	close(cc->inout[1]);
	close(cc->inout[0]);
	
	//inout[1] = fdinout[1];
	//inout[0] = fdpipe[0];
	cc = cmds->next->content;
	cc->inout[1] = fdinout[1];
	cc->inout[0] =  ((t_cmd *)cmds->content)->pipefd[0];
	exec_cmmand(cc, envp);
	close(cc->inout[1]);
	close(cc->inout[0]);
	//close(fdpipe[0]);
	wait(NULL);
	wait(NULL);
}

int	exec_cmmand(t_cmd *cmd, char **envp)
{
	int		pid;
	char	**splited_cmd;
	char	*str;

	pid = fork();
	
	if (pid < 0)
	{
		perror("pipex: ");
		exit(1);
	}
	if (pid == 0)
	{
		if (dup2(cmd->inout[0], 0) < 0 ||dup2(cmd->inout[1], 1) < 0)
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
		splited_cmd = ft_split(cmd->cmd, ' ');
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
		if (execve(str, splited_cmd, envp) < 0)
		{
			perror("pipex: ");
			exit(errno);
		}
	}
	return (pid);
}
