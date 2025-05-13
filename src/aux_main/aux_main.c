/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifluxa-c <ifluxa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 18:02:47 by nachofluxa        #+#    #+#             */
/*   Updated: 2025/04/15 19:35:42 by ifluxa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "libft/libft.h"
#include "freedom/freedom.h"
#include "lexer/lexer.h"
#include "parser/parser.h"
#include "aux_main/aux_main.h"

static void	free_command_strs(char **command_strings)
{
	size_t	position;

	position = 0;
	while (command_strings[position])
	{
		freedom((void **)(command_strings + position));
		position++;
	}
	freedom((void **)&command_strings);
}

static void	process_lexems(char **lexems, t_command **commands, size_t pos)
{
	size_t	position2;

	commands[pos] = parser(lexems);
	position2 = 0;
	while (commands[pos]->args[position2])
		remove_quotes(commands[pos]->args[position2++]);
	position2 = 0;
	while (lexems[position2])
		freedom((void **)(lexems + position2++));
	freedom((void **)&lexems);
}

t_command	**allocate_cmds(char **command_strings)
{
	size_t		i;
	t_command	**commands;

	i = 0;
	while (command_strings[i])
		i++;
	commands = ft_calloc(i + 1, sizeof(t_command *));
	if (!commands)
	{
		perror("minishell");
		return ((void *)0);
	}
	return (commands);
}

char	**get_cmd_str(char	*input, char **envp, int exitno)
{
	char	**command_strings;

	input = initial_translation(input, envp, exitno);
	if (!input)
		return ((void *)0);
	command_strings = divide_input(input);
	freedom((void **)&input);
	if (!command_strings)
	{
		perror("minishell");
		return ((void *)0);
	}
	return (command_strings);
}

t_command	**process_input(char *input, char **envp, int exitno)
{
	char		**command_strings;
	char		**lexems;
	t_command	**commands;
	size_t		position1;

	command_strings = get_cmd_str(input, envp, exitno);
	if (!command_strings)
		return ((void *)0);
	commands = allocate_cmds(command_strings);
	if (!commands)
		return ((void *)0);
	position1 = 0;
	while (command_strings[position1])
	{
		lexems = lexer(command_strings[position1]);
		process_lexems(lexems, commands, position1);
		if (!commands[position1])
			free_command(commands + position1--);
		position1++;
	}
	free_command_strs(command_strings);
	return (commands);
}
