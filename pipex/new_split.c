/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 17:28:14 by asouinia          #+#    #+#             */
/*   Updated: 2022/03/19 17:33:37 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	inter_split(char *str, int i, char **s)
{
	char	*tmp;

	s[0] = ft_memcpy(s[0], str, i - 1);
	s[0][i - 1] = '\0';
	tmp = s[0];
	s[0] = ft_strtrim(s[0], " ");
	free(tmp);
	s[1] = ft_strdup(str + i + 1);
	tmp = s[1];
	s[1] = ft_strtrim(s[1], "\"'");
	free(tmp);
}

char	**ft_new_split(char *str, char c)
{
	int		i;
	char	**s;

	s = malloc(sizeof(char *) * 3);
	if (!s)
	{
		perror("pipex: ");
		exit(1);
	}
	s[2] = NULL;
	i = 0;
	while (str && str[i] && str[i] != c)
			++i;
	s[0] = malloc(sizeof(char) * (i));
	if (!s[0])
	{
		perror("pipex: ");
		exit(1);
	}
	inter_split(str, i, s);
	return (s);
}
