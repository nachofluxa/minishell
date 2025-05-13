/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachofluxa <nachofluxa@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:02:33 by nachofluxa        #+#    #+#             */
/*   Updated: 2025/04/29 13:05:48 by nachofluxa       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/builtins.h"
#include "freedom/freedom.h"
#include "errors/errors.h"
#include "libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <fcntl.h>

int	ft_echo(t_command *cmd)
{
	int	i;
	int	j;
	int	new_line_flag;

	i = 0;
	new_line_flag = 1;
	while (cmd->args[i + 1] && cmd->args[i + 1][0] == '-')
	{
		j = 1;
		while (cmd->args[i + 1][j] == 'n')
			j++;
		if (cmd->args[i + 1][j])
			break ;
		new_line_flag = 0;
		i++;
	}
	while (cmd->args[++i])
	{
		write(STDOUT_FILENO, cmd->args[i], ft_strlen(cmd->args[i]));
		if (cmd->args[i + 1] && *cmd->args[i + 1] != '>')
			write(STDOUT_FILENO, " ", 1);
	}
	write(STDOUT_FILENO, "\n", new_line_flag);
	return (0);
}

static char	*get_path(t_command *command)
{
	char	*path;

	if (!command->args || !command->args[1])
	{
		path = getenv("HOME");
		if (!path)
			return (NULL);
	}
	else
	{
		path = ft_strdup(command->args[1]);
		if (!path)
			return (NULL);
	}
	return (path);
}

int	ft_cd(t_command *command)
{
	char	*path;

	if (command->args && command->args[1] && command->args[2])
	{
		args_error("cd", command->args[2], 0);
		return (1);
	}
	path = get_path(command);
	if (!path)
		return (0);
	if (chdir(path) == -1)
	{
		args_error("cd", command->args[1], 0);
		if (path != getenv("HOME"))
			freedom((void **)&path);
		return (1);
	}
	if (path != getenv("HOME"))
		freedom((void **)&path);
	return (0);
}

int	ft_pwd(t_command *command)
{
	char	*path;

	(void)command;
	path = malloc(PATH_MAX);
	if (!path)
		return (1);
	if (getcwd(path, PATH_MAX) != NULL)
	{
		printf("%s\n", path);
		freedom((void **)&path);
		return (0);
	}
	else
	{
		freedom((void **)&path);
		return (1);
	}
}

int	check_builtins(t_command *command, char **envp)
{
	size_t	size;

	if (!command)
		return (127);
	size = ft_strlen(command->args[0]);
	if (size == 0)
		command_error(command, 0);
	else if (ft_strncmp(command->args[0], "echo", size) == 0 && size == 4)
		return (ft_echo(command));
	else if (ft_strncmp(command->args[0], "cd", size) == 0 && size == 2)
		return (ft_cd(command));
	else if (ft_strncmp(command->args[0], "pwd", size) == 0 && size == 3)
		return (ft_pwd(command));
	else if (ft_strncmp(command->args[0], "export", size) == 0 && size == 6)
		return (ft_export(command, envp));
	else if (ft_strncmp(command->args[0], "unset", size) == 0 && size == 5)
		return (ft_unset(command, envp));
	else if (ft_strncmp(command->args[0], "env", size) == 0 && size == 3)
		return (ft_env(command, envp));
	else if (ft_strncmp(command->args[0], "exit", size) == 0 && size == 4)
		return (ft_exit(command));
	else
		command_error(command, 0);
	return (127);
}
