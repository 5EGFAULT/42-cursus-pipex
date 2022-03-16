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
void	loop_cmds(int argc, char **argv, char **envp )
{
	int fdinout[2];
	int fdpipe0[2];
	int i; 
	int in;

	fdinout[0] = open(argv[1], O_RDONLY);	
	if (fdinout[0] < 0|| pipe(fdpipe0) < 0)
	{
		perror("");
		exit(-1);
	}
	in = fdinout[0];
	i = 1;
	exec_cmmand(fdpipe0, argv[2], envp, in);	
	fdinout[1] = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0777);
	exec_cmmand(fdinout, argv[3], envp, fdpipe0[0]);
}

int	exec_cmmand(int *fdpipe, char *cmd, char **envp, int in)
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
		if (dup2(in, 0) < 0 ||dup2(fdpipe[1], 1) < 0)
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
