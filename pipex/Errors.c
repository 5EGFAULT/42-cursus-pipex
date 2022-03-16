/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 22:31:32 by asouinia          #+#    #+#             */
/*   Updated: 2022/03/15 23:18:58 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"

int	catch_errors(int argc, char **argv)
{
	int		fd;
	fd = open(argv[1], O_RDONLY);
	if (argc != 5 || fd < 0)
	{
		perror("pipex");
		exit (5);
	}
	if (catch_file_error(argv[1], O_RDONLY))
	{
		perror("cant open infile in read only");
		return (0);
	}
	if (catch_file_error(argv[1], O_RDWR))
	{
		perror("cant open infile in read only");
		return (0);
	}
	if (catch_file_error(argv[argc - 1], O_RDWR))
	{
		perror("cant open outfile in read only");
		return (0);
	}
	if (catch_file_error(argv[argc - 1], O_WRONLY))
	{
		perror("cant open outfile in write only");
		return (0);
	}
	return (1);
}
int	catch_file_error(char *path, int permission)
{
	int		fd;
	char	str[10];
	fd = open(path, permission);
	if (read(fd, str, 10) < 0)
	{
		close(fd);
		return (0);
	}
	return (1);
}