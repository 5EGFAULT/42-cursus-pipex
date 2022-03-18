/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 14:15:03 by asouinia          #+#    #+#             */
/*   Updated: 2022/03/18 20:46:26 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex_bonus.h"

void	free_2d(char **ptr)
{
	int	i;

	if (!ptr)
		return ;
	i = -1;
	while (ptr[++i])
		free(ptr[i]);
	free(ptr);
}

void	del_content(void *content)
{
	free(content);
}

t_cmd	*new_cmd(char *cmd, int idx, int islast)
{
	t_cmd	*c;

	c = malloc(sizeof(t_cmd));
	if (!c)
	{
		perror("pipex: ");
		exit(errno);
	}
	c->idx = idx;
	c->cmd = cmd;
	if (!islast)
	{
		c->pipefd = malloc(sizeof(int) * 2);
		if (!c->pipefd || pipe(c->pipefd) < 0)
		{
			perror("pipex: ");
			exit(errno);
		}
	}
	else
		c->pipefd = NULL;
	return (c);
}

t_file	*new_file(char *file, int idx, int perm)
{
	t_file	*c;

	c = malloc(sizeof(t_file));
	if (!c)
	{
		perror("pipex: ");
		exit(errno);
	}
	c->idx = idx;
	c->file = file;
	c->fd = open(file, perm, 0644);
	if (c->fd < 0)
	{
		perror("pipex: ");
		exit(errno);
	}
	return (c);
}
