#include "./pipex.h"
int	main(int argc, char **argv, char **envp)
{
	if (argc != 5)
	{
		perror("pipex: must have 4 Args");
		exit(-1);
	}
	loop_cmds(argc, argv, envp);
	//system("leaks pipex");
	//while (1)
	//{
	//	;
	//}
	
	return (0);
}
void	loop_cmds(int argc, char **argv, char **envp )
{
	int fdinout[2];
	int fdpipe0[2];
	int inout[2];
	int i; 

	fdinout[0] = open(argv[1], O_RDONLY);	
	if (fdinout[0] < 0|| pipe(fdpipe0) < 0)
	{
		perror("pipex: ");
		exit(1);
	}
	inout[0] = fdinout[0];
	inout[1] = fdpipe0[1];
	i = 1;
	exec_cmmand(inout, argv[2], envp, fdpipe0);	
	fdinout[1] = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0777);
	close(fdpipe0[1]);
	inout[1] = fdinout[1];
	inout[0] = fdpipe0[0];
	exec_cmmand(inout, argv[3], envp, fdpipe0);
	close(fdpipe0[0]);
	close(fdinout[0]);
	close(fdinout[1]);
	wait(NULL);
	wait(NULL);
}

int	exec_cmmand(int	*inout, char *cmd, char **envp, int *fdpipe)
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
		if (dup2(inout[0], 0) < 0 ||dup2(inout[1], 1) < 0)
		{
			
			perror("pipex: ");
			exit(errno);
		}
		close(inout[0]);
		close(inout[1]);
		close(fdpipe[0]);
		close(fdpipe[1]);
		splited_cmd = ft_split(cmd, ' ');
		if (!splited_cmd)
		{
			perror("pipex: ");
			exit(1);
		}
		str = get_cmd_full_path(envp, splited_cmd[0]);
		if (execve(str, splited_cmd, envp) < 0)
		{
			perror("pipex: ");
			exit(1);
		}
	}
	return (pid);
}
