/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 20:42:40 by asouinia          #+#    #+#             */
/*   Updated: 2022/03/18 21:04:50 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_d_list	*cmds;
	t_d_list	*files;
	int			start;

	if (argc != 5)
	{
		write(2, "pipex: must have at 5 Args\n", 28);
		exit(-1);
	}
	cmds = NULL;
	files = NULL;
	start = init_files(argc, argv, &files);
	init_cmds(argc, argv, &cmds, start);
	loop_cmds(files, cmds, envp, argc);
	return (0);
}

int	init_files(int argc, char **argv, t_d_list **files)
{
	t_file		*file;
	int			start;

	start = 1;
	file = new_file(argv[1], 1, O_RDONLY);
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
