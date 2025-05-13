/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachofluxa <nachofluxa@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:38:13 by nachofluxa        #+#    #+#             */
/*   Updated: 2025/04/21 20:49:42 by nachofluxa       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path/path.h"
#include "freedom/freedom.h"
#include "libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

char	**ini_paths(char **envp)
{
	char	**paths;
	size_t	position;

	position = 0;
	while (envp[position] && ft_strncmp(envp[position], "PATH=", 5) != 0)
		position++;
	if (!envp[position])
		return ((void *)0);
	paths = ft_split(envp[position] + 5, ':');
	if (!paths)
		return (NULL);
	return (paths);
}

static char	*last_step(char **paths, char *full_path)
{
	int	i;

	i = -1;
	while (paths[++i])
		freedom((void **)(paths + i));
	freedom((void **)&paths);
	return (full_path);
}

static char	*check_paths(char *aux, char **paths)
{
	char	*full_path;
	size_t	i;

	i = -1;
	full_path = NULL;
	while (paths[++i])
	{
		full_path = ft_strjoin(paths[i], aux);
		if (full_path)
		{
			if (access(full_path, F_OK) == 0 && access(full_path, X_OK) == 0)
				return (full_path);
			freedom((void **)&full_path);
		}
	}
	return (NULL);
}

char	*pathfinder(char *str, char **envp)
{
	char	**paths;
	char	*aux;
	char	*full_path;

	if (access(str, F_OK) == 0 && access(str, X_OK) == 0)
		return (ft_strdup(str));
	aux = ft_strjoin("/", str);
	if (!aux)
		return (NULL);
	paths = ini_paths(envp);
	if (!paths)
	{
		freedom((void **)&aux);
		return (NULL);
	}
	full_path = check_paths(aux, paths);
	freedom((void **)&aux);
	return (last_step(paths, full_path));
}
