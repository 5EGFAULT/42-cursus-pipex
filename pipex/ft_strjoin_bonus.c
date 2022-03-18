/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 00:06:03 by asouinia          #+#    #+#             */
/*   Updated: 2022/03/18 21:49:52 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s;
	int		i;
	int		j;

	i = -1;
	j = -1;
	if (!s1 || !s2)
		return (0);
	s = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!s)
		return (0);
	while (s1[++j])
		s[j] = s1[j];
	while (s2[++i])
		s[i + j] = s2[i];
	s[i + j] = '\0';
	return (s);
}
