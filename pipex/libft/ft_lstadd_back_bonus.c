/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 23:15:17 by asouinia          #+#    #+#             */
/*   Updated: 2022/03/18 12:59:00 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!new)
		return ;
	if (*lst)
	{
		last = ft_lstlast(*lst);
		new->next = NULL;
		last->next = new;
	}
	else
	{
		new->next = NULL;
		*lst = new;
	}
}
