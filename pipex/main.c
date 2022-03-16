/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:29:03 by asouinia          #+#    #+#             */
/*   Updated: 2022/03/16 13:17:27 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"
int	main(int argc, char **argv, char **envp)
{
	if (argc != 5)
	{
		perror("must have 4 Args");
		exit(-1);
	}
	loop_cmds(argc, argv, envp);
	return (0);
}
/**
 * @brief loop around cmds and execute then one by one using command
 * 
 * @param argc 
 */
void	loop_cmds(int argc, char **argv, char **envp )
{
	int fdinout[2];
	int fdpipe[2];
	int i;
	int status;

	fdinout[0] = open(argv[1], O_RDONLY);	
	fdinout[1] = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT);	
	if (fdinout[0] < 0 || fdinout[1] < 0 || pipe(fdpipe) < 0 || dup2(fdpipe[0], fdinout[0]) < 0)
	{
		perror("");
		exit(-1);
	}
	i = 0;
	while (++i < argc - 1)
	{
		waitpid(exec_cmmand(fdpipe, argv[i], envp), &status,0);
	}
	
}

int	exec_cmmand(int *fdpipe, char *cmd, char **envp)
{
	int		pid;
	char	**splited_cmd;

	pid = fork();
	if (pid < 0 || dup2(fdpipe[1], 1) < 0)
	{
		perror("");
		exit(-1);
	}
	if (pid == 0)
	{
		splited_cmd = ft_split(cmd, ' ');
		if (!splited_cmd)
		{
			perror("");
			exit(-1);
		}
		if (execve(splited_cmd[0], splited_cmd, envp) < 0)
		{
			perror("");
			exit(-1);
		}
	}
	return (pid);
}
