/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 22:44:57 by asouinia          #+#    #+#             */
/*   Updated: 2022/03/14 17:59:36 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*set_rest_to_str(char **rest)
{
	char	*s;
	char	*tmp;

	s = NULL;
	if (*rest)
	{
		s = ft_strjoin_gnl(s, *rest, ft_strlen_gnl(*rest));
		tmp = *rest;
		if (ft_strchr_gnl(s, '\n'))
		{
			*rest = ft_substr_gnl(*rest, BUFFER_SIZE);
		}
		else
		{
			*rest = NULL;
		}
		free(tmp);
	}
	return (s);
}

int	loop_checks(char *buf, char **rest, char **s, int len)
{
	char		*tmp;

	buf[len] = '\0';
	tmp = *s;
	*s = ft_strjoin_gnl(*s, buf, len);
	free(tmp);
	if (!*s)
	{
		free(buf);
		free(*rest);
		return (1);
	}
	if (ft_strchr_gnl(*s, '\n'))
	{
		*rest = ft_substr_gnl(buf, len);
		free(buf);
		return (1);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	char		*s;
	char		*buf;
	int			len;
	static char	*rest[OPEN_MAX] = {};

	s = NULL;
	if (fd > -1 && rest[fd])
		s = set_rest_to_str(&rest[fd]);
	if (fd > -1 && rest[fd])
		return (s);
	buf = (char *)malloc(BUFFER_SIZE + 1);
	if (buf == NULL)
		return (NULL);
	len = 1;
	while (len > 0)
	{
		len = read(fd, buf, BUFFER_SIZE);
		if (len > 0 && loop_checks(buf, &rest[fd], &s, len))
			return (s);
	}
	free(buf);
	return (s);
}
