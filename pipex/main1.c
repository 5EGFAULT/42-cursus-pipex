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
	int inout[2];
	int i; 

	fdinout[0] = open(argv[1], O_RDONLY);	
	if (fdinout[0] < 0|| pipe(fdpipe0) < 0)
	{
		perror("");
		exit(-1);
	}
	inout[0] = fdinout[0];
	i = 1;
	fprintf(stdout,"  1  in  %d  out %d \n",in , fdpipe0[1]);
	exec_cmmand(fdpipe0, argv[2], envp, in );	
	fdinout[1] = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0777);
	close(fdpipe0[1]);
	//fdinout[1] = 2;
	fprintf(stdout,"  2  in  %d  out %d \n",fdpipe0[0] , fdinout[1]);
	exec_cmmand(fdinout[1], argv[3], envp, fdpipe0[0]);
	close(fdpipe0[0]);

	//close(fdinout[1]);
	//close(fdinout[0]);
	//close(fdinout[1]);
	//waitpid(-1, NULL, 0);
	//waitpid(-1, NULL, 0);
	//while ()
	//{
	//	/* code */
	//}
	wait(NULL);
	fprintf(stdout," sssssss 2  in  %d  out %d \n",fdpipe0[0] , fdinout[1]);
	wait(NULL);
	fprintf(stdout," sssssss 2  in  %d  out %d \n",fdpipe0[0] , fdinout[1]);
	
	//close(fdinout[1]);
}

int	exec_cmmand(int *out, char *cmd, char **envp, int in)
{
	int		pid;
	char	**splited_cmd;
	char	*str;

	pid = fork();
	
	if (pid < 0)
	{
		perror("");
		exit(-1);
	}
	//fprintf(stdout,"in  %d  out %d  pid %d \n",in , out, pid);
	if (pid == 0)
	{
		fprintf(stdout,"in  %d  out %d \n",in , out[1]);
		if (dup2(in, 0) < 0 ||dup2(out, 1) < 0)
		{
			
			perror("");
			exit(-1);
		}
		close(in);
		close(out[0]);
		close(out[1]);
		splited_cmd = ft_split(cmd, ' ');
		if (!splited_cmd)
		{
			perror("");
			exit(-1);
		}
		str = get_cmd_full_path(envp, splited_cmd[0]);
		//if (!ft_strncmp(splited_cmd[1], "0", 1))
		//	dup2(2, 1);
		//str = "";
		if (execve(str, splited_cmd, envp) < 0)
		{
			perror("");
			exit(-1);
		}
	}
	return (pid);
}
