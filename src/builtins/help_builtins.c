/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachofluxa <nachofluxa@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:02:39 by nachofluxa        #+#    #+#             */
/*   Updated: 2025/04/15 16:09:59 by nachofluxa       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/builtins.h"
#include "freedom/freedom.h"
#include "libft/libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void	set_environ(char **envp, char **args, int size, int i)
{
	int		j;

	j = 0;
	while (envp[j])
	{
		if (envp[j] && ft_strncmp(envp[j], args[i], size) == 0
			&& envp[j][size] == '=')
		{
			freedom((void **)&envp[j]);
			envp[j] = ft_strdup(args[i]);
			return ;
		}
		j++;
	}
	envp[j] = ft_strdup(args[i]);
	envp[j + 1] = NULL;
}

char	**get_env(char **envp)
{
	int		i;
	char	**new_env;

	i = 0;
	while (envp[i])
		i++;
	new_env = ft_calloc(i * 2, sizeof(char *));
	if (!new_env)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		new_env[i] = ft_strdup(envp[i]);
		i++;
	}
	return (new_env);
}
