/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 22:45:09 by asouinia          #+#    #+#             */
/*   Updated: 2022/03/14 18:00:00 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# define BUFFER_SIZE 1

size_t	ft_strlen_gnl(const char *s);
char	*ft_strjoin_gnl(char *s1, char const *s2, int len);
char	*ft_strchr_gnl(const char *s, int c);
char	*ft_substr_gnl(char *s, size_t len);
char	*get_next_line(int fd);

#endif