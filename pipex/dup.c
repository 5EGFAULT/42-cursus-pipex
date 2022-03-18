/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 12:31:25 by asouinia          #+#    #+#             */
/*   Updated: 2022/03/18 12:31:26 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./pipex.h"
int main(void)
{
	int fd;
	int p1[2];
	int p2[2];
	int fdin;
	int fdout;

	fdin = open("in", O_RDONLY);
	fdout= open("out", O_WRONLY | O_TRUNC | O_CREAT);
	if (fdin < 0 || fdout <0 || pipe(p1) < 0 || pipe(p2) < 0)
	{
		perror("");
		exit(errno);
	}	
	int readfdd = dup2(fdin, 0);
	//dup2(p2[0], fdin);
	//dup2(p1[0], p2[0]);
	//dup2(0, p1[0]);
	dup2(fdin, p2[0]);
	dup2(p2[0], p1[0]);
	dup2(p1[0], 0);

	dup2(fdout, p2[1]);
	dup2(p2[1], p1[1]);
	dup2(p1[1], 1);

	//dup2(p2[1], fdout);
	//dup2(p1[1], p2[1]);
	//dup2(1, p1[1]);

	//int writefdd = dup2(1, 1);
	char str[2000];
	int strl = read(0, str, 200);
	str[strl] = '\0';
	printf("%s",str);
	return (0);
}