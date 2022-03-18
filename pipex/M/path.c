/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouinia <asouinia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 12:47:19 by asouinia          #+#    #+#             */
/*   Updated: 2022/03/18 12:02:11 by asouinia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"

char	**get_paths(char **envp)
{
	char **paths;
	char **result;
	char *tmp;
	int i;

	i = 0;
	result = ft_split(get_env_var(envp, "PATH"), ':');
	if (!result)
		return (NULL);
	while (result[i++])
		;
	paths = malloc(sizeof(char *) * (i + 1));
	i = 0;
	tmp = ft_substr(result[0], 4, ft_strlen(result[0]));
	paths[0] = ft_strjoin(tmp, "/");
	free(tmp);
	while (result[++i])
	{
		paths[i] = ft_strjoin(result[i], "/");
	}
	free_2d(result);
	return (paths);
}

char	*get_cmd_full_path(char **envp, char *cmd)
{
	char *path;
	char **all_paths;
	int		i;

	all_paths = get_paths(envp);
	i = -1;
	while (all_paths && all_paths[++i])
	{
		path = ft_strjoin(all_paths[i], cmd);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
	}
	return (cmd);
}