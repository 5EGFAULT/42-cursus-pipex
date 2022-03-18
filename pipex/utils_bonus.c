/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 14:15:03 by asouinia          #+#    #+#             */
/*   Updated: 2022/03/18 12:12:38 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"

void	free_2d(char **ptr)
{
	int i;

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