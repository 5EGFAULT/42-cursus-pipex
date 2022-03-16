/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:29:03 by asouinia          #+#    #+#             */
/*   Updated: 2022/03/16 21:49:22 by asouinia         ###   ########.fr       */
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
 * @return return nothing
 * @param argc  
 */
void	loop_cmds(int argc, char **argv, char **envp )
{
	int fdinout[2];
	int fdpipe0[2];
	int fdpipe1[2];
	char	ssss[82];
	int i;
	int fdtmpreadpipe[2];

	fdinout[0] = open(argv[1], O_RDONLY);	
	if (fdinout[0] < 0|| pipe(fdpipe0) < 0)
	{
		perror("");
		exit(-1);
	}
	fdtmpreadpipe[0] = fdpipe0[0];
	if ( dup2(fdinout[0], fdpipe0[0]) < 0)
	{
		perror("");
		exit(-1);
	}
	//close(fdinout[0]);
	i = 1;
	while (++i < argc - 2)
	{
		exec_cmmand(fdpipe0, argv[i], envp);	
		fdpipe1[0] = fdtmpreadpipe[0];
		fdpipe1[1] = fdpipe0[1];
		if (pipe(fdpipe0) < 0)
		{
			perror("");
			exit(-1);
		}
		fdtmpreadpipe[0] = fdpipe0[0];
		if (dup2(fdpipe1[0], fdpipe0[0]) < 0)
		{
			perror("");
			exit(-1);
		}
		//close(fdpipe0[0]);
		//close(fdpipe0[1]);
	}
	//close(fdpipe1[1]);
		//fdpipe1[0] = fdtmpreadpipe[0];
		//fdpipe1[1] = fdpipe0[1];
		//if (pipe(fdpipe0) < 0)
		//{
		//	perror("");
		//	exit(-1);
		//}
		
	fdinout[1] = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (fdinout[1] < 0  || dup2( fdinout[1], fdtmpreadpipe[1]) < 0)
	{
		perror("");
		exit(-1);
	}
	//close(fdinout[1]);
	//write(fdpipe0[1],"hell",4);
	exec_cmmand(fdtmpreadpipe, argv[i], envp);
		while (--i > 1)
	{
		wait(NULL);
	}
	read(fdpipe0[0],ssss,80);
	write(2, ssss,80);
	//printf("\n%s\n",str);

	
	//close(fdpipe0[0]);
	//close(fdpipe0[1]);
}

int	exec_cmmand(int *fdpipe, char *cmd, char **envp)
{
	int		pid;
	char	**splited_cmd;
	char	*str;
	//int		fddup[2];

	pid = fork();
	
	if (pid < 0)
	{
		perror("");
		exit(-1);
	}
	if (pid == 0)
	{
		if (dup2(fdpipe[0], 0) < 0 ||dup2(fdpipe[1], 1) < 0)
		{
			
			perror("");
			exit(-1);
		}
		//close(fdpipe[0]);
		//close(fdpipe[1]);
		splited_cmd = ft_split(cmd, ' ');
		if (!splited_cmd)
		{
			perror("");
			exit(-1);
		}
		str = ft_strjoin("/usr/bin/",  splited_cmd[0]);
		if (access(str ,X_OK))
		{
			str = ft_strjoin("/bin/",  splited_cmd[0]);
			if (access(str ,X_OK))
			{
				perror("");
				exit(-1);
			}
		}
		if (execve(str, splited_cmd, envp) < 0)
		{
			perror("");
			exit(-1);
		}
	}
	return (pid);
}
