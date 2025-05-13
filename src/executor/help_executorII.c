/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_executorII.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifluxa-c <ifluxa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 18:22:37 by nachofluxa        #+#    #+#             */
/*   Updated: 2025/04/29 12:33:20 by ifluxa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/executor.h"
#include "freedom/freedom.h"
#include "parser/parser.h"
#include "path/path.h"
#include "builtins/builtins.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>

int	count_commands(t_command **command)
{
	int	i;

	i = 0;
	while (command[i])
		i++;
	return (i);
}

int	execute_command(t_command *command, char **envp)
{
	char	*path;

	if (!command->args || !command->args[0])
		exit(0);
	path = pathfinder(command->args[0], envp);
	if (path)
		execve(path, command->args, envp);
	freedom((void **)&path);
	printf("minishell: command not found: %s\n", command->args[0]);
	exit (127);
}

void	close_auxfd(int (*auxfd)[2])
{
	if (auxfd)
	{
		close((*auxfd)[0]);
		close((*auxfd)[1]);
		freedom((void **)&auxfd);
	}
}

void	free_auxfd(int (*auxfd)[2])
{
	int	fd0;
	int	fd1;

	fd0 = (*auxfd)[0];
	fd1 = (*auxfd)[1];
	close(fd0);
	close(fd1);
	freedom((void **)&auxfd);
}
