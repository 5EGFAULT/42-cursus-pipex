/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:30:11 by asouinia          #+#    #+#             */
/*   Updated: 2022/03/15 22:48:23 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_PIPEX_H
# define SO_PIPEX_H
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <errno.h>
# include "./libft/libft.h"

//!	Errors.c
int	catch_errors(int argc, char **argv);
int	catch_file_error(char *path, int permission);

#endif