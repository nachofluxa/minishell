/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtinsII.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifluxa-c <ifluxa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:02:36 by nachofluxa        #+#    #+#             */
/*   Updated: 2025/04/15 19:40:35 by ifluxa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/builtins.h"
#include "errors/errors.h"
#include "freedom/freedom.h"
#include "libft/libft.h"
#include "history/history.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

static void	iter_env(char **envp, int j)
{
	freedom((void **)(envp + j));
	while (envp[j + 1])
	{
		envp[j] = envp[j + 1];
		j++;
	}
	envp[j] = (void *)0;
}

int	ft_unset(t_command *command, char **envp)
{
	int		i;
	int		j;

	i = 0;
	while (command->args[++i])
	{
		j = -1;
		while (envp[++j])
		{
			if (ft_strncmp(envp[j], command->args[i],
					ft_strlen(command->args[i])) == 0
				&& envp[j][ft_strlen(command->args[i])] == '=')
			{
				iter_env(envp, j);
				break ;
			}
		}
	}
	return (0);
}

int	ft_export(t_command *command, char **envp)
{
	int	i;
	int	size;

	i = 0;
	if (!command->args[1])
		return (ft_env(NULL, envp));
	while (command->args[++i])
	{
		size = 0;
		if (command->args[i][size] == '=')
		{
			args_error("export", command->args[i], 3);
			break ;
		}
		while (command->args[i][size] && command->args[i][size] != '=')
			size++;
		if (command->args[i][size] == '=')
			set_environ(envp, command->args, size, i);
	}
	return (0);
}

int	ft_env(t_command *command, char **envp)
{
	int	i;
	int	j;

	i = -1;
	if ((command && command->args[1]) || !envp || !*envp)
	{
		args_error("env", command->args[1], 2);
		return (1);
	}
	while (envp[++i])
	{
		j = -1;
		while (envp[i][++j])
			write(1, &envp[i][j], 1);
		write(1, "\n", 1);
	}
	return (0);
}

int	ft_exit(t_command *command)
{
	size_t	position;

	printf("exit\n");
	if (!command->args || !command->args[1])
	{
		manage_history((void *)0, CLEAN);
		exit(0);
	}
	if (command->args[2])
	{
		command_error(command, 1);
		return (1);
	}
	position = 0;
	while (ft_isdigit(command->args[1][position]))
		position++;
	if (command->args[1][position])
	{
		manage_history((void *)0, CLEAN);
		args_error("exit", command->args[1], 4);
		exit(2);
	}
	exit(ft_atoi(command->args[1]) % 256);
}
