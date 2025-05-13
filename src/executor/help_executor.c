/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachofluxa <nachofluxa@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:27:26 by nachofluxa        #+#    #+#             */
/*   Updated: 2025/04/21 21:07:06 by nachofluxa       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/executor.h"
#include "libft/libft.h"
#include "var_translator/var_translator.h"
#include "freedom/freedom.h"
#include "parser/parser.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include "signals/signals.h"

int	open_output(char *file)
{
	int	fd;

	if (!file)
		return (1);
	fd = -1;
	if (file[1] == '>')
		fd = open(file + 2, O_CREAT | O_APPEND | O_WRONLY, 0644);
	else
		fd = open(file + 1, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd == -1)
		perror("minishell");
	if (fd == -1)
		return (0);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (1);
}

static int	get_heredoc(char *eof, char **envp, int exitno)
{
	char	*input;
	char	*translated_input;
	int		fd;

	setup_heredoc_signals();
	fd = open("/tmp/heredoc.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
		return (-1);
	input = readline("(heredoc)> ");
	while (input && (ft_strncmp(input, eof, ft_strlen(eof)) != 0
			|| ft_strlen(eof) != ft_strlen(input)))
	{
		translated_input = var_translator(input, envp, exitno);
		freedom((void **)&input);
		ft_putendl_fd(translated_input, fd);
		freedom((void **)&translated_input);
		input = readline("(heredoc)> ");
	}
	if (!input)
		printf("minishell: warning: expected %s\n", eof);
	freedom((void **)&input);
	close(fd);
	setup_signals2();
	return (open("/tmp/heredoc.txt", O_RDONLY));
}

int	open_input(char *file, char **envp, int exitno)
{
	int		fd;

	if (!file)
		return (1);
	fd = -1;
	if (file[1] == '<')
		fd = get_heredoc(file + 2, envp, exitno);
	else
		fd = open(file + 1, O_RDONLY);
	if (fd == -1)
		perror("minishell");
	if (fd == -1)
		return (0);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (1);
}

int	is_builtin(t_command *command)
{
	size_t	size;

	if (!command || !command->args || !command->args[0])
		return (0);
	size = strlen(command->args[0]);
	if (ft_strncmp(command->args[0], "echo", size) == 0
		|| ft_strncmp(command->args[0], "cd", size) == 0
		|| ft_strncmp(command->args[0], "pwd", size) == 0
		|| ft_strncmp(command->args[0], "export", size) == 0
		|| ft_strncmp(command->args[0], "unset", size) == 0
		|| ft_strncmp(command->args[0], "env", size) == 0
		|| ft_strncmp(command->args[0], "exit", size) == 0)
		return (1);
	return (0);
}

int	lets_see_the_builtin(t_command *command)
{
	size_t	size;

	if (!command || !command->args || !command->args[0])
		return (0);
	size = strlen(command->args[0]);
	if (ft_strncmp(command->args[0], "cd", size) == 0
		|| ft_strncmp(command->args[0], "exit", size) == 0
		|| ft_strncmp(command->args[0], "export", size) == 0
		|| ft_strncmp(command->args[0], "unset", size) == 0)
		return (1);
	return (0);
}
