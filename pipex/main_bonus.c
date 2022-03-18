/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 20:42:40 by asouinia          #+#    #+#             */
/*   Updated: 2022/03/18 21:59:46 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_d_list	*cmds;
	t_d_list	*files;
	int			start;

	if (argc < 3)
	{
		perror("pipex: must have at least 3 Args");
		exit(-1);
	}
	cmds = NULL;
	files = NULL;
	start = init_files(argc, argv, &files);
	init_cmds(argc, argv, &cmds, start);
	loop_cmds(files, cmds, envp, argc);
	return (0);
}

int	her_doc(char *limiter)
{
	int		pip[2];
	char	*str;
	char	*testlimitter;

	if (pipe(pip) < 0)
	{
		perror("pipex: ");
		exit(errno);
	}
	testlimitter = ft_strjoin(limiter, "\n");
	write(1, "heredoc> ", 10);
	str = get_next_line(0);
	while (ft_strncmp(str, testlimitter, ft_strlen(testlimitter)))
	{
		write(pip[1], str, ft_strlen(str));
		write(1, "heredoc> ", 10);
		free(str);
		str = get_next_line(0);
	}
	close(pip[1]);
	free(str);
	free(testlimitter);
	return (pip[0]);
}

t_file	*new_her_doc(char *limiter, int idx)
{
	t_file	*c;

	c = malloc(sizeof(t_file));
	if (!c)
	{
		perror("pipex: ");
		exit(errno);
	}
	c->idx = idx;
	c->file = "her_doc";
	c->fd = her_doc(limiter);
	return (c);
}

int	init_files(int argc, char **argv, t_d_list **files)
{
	t_file		*file;
	int			start;

	start = 1;
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
	{
		start = 2;
		file = new_her_doc(argv[2], 2);
	}
	else
	{
		file = new_file(argv[1], 1, O_RDONLY);
	}
	ft_d_lstadd_back(files, ft_d_lstnew(file));
	file = new_file(argv[argc - 1], argc - 1, O_WRONLY | O_TRUNC | O_CREAT);
	ft_d_lstadd_back(files, ft_d_lstnew(file));
	return (start);
}

void	init_cmds(int argc, char **argv, t_d_list **cmds, int start)
{
	t_cmd	*cmd;
	int		i;

	i = start;
	while (++i < argc - 2)
	{
		cmd = new_cmd(argv[i], i, 0);
		ft_d_lstadd_back(cmds, ft_d_lstnew(cmd));
	}
	cmd = new_cmd(argv[argc - 2], argc - 2, 1);
	ft_d_lstadd_back(cmds, ft_d_lstnew(cmd));
}
