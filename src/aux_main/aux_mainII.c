/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_mainII.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifluxa-c <ifluxa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 18:33:28 by nachofluxa        #+#    #+#             */
/*   Updated: 2025/04/29 12:39:01 by ifluxa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "libft/libft.h"
#include "var_translator/var_translator.h"
#include "file_translator/file_translator.h"
#include "freedom/freedom.h"
#include "lexer/lexer.h"
#include "get_next_line/get_next_line.h"
#include "parser/parser.h"
#include "path/path.h"
#include "executor/executor.h"
#include "history/history.h"
#include "checker/checker.h"
#include "aux_main/aux_main.h"

static char	**free_command_strings(char **command_strings, size_t size)
{
	while (command_strings[size])
		freedom((void **)(command_strings + size));
	freedom((void **)&command_strings);
	return ((void *)0);
}

static void	handle_quotes(const char *input, size_t *position)
{
	char	quote;

	if (input[*position] == '\'' || input[*position] == '"')
	{
		quote = input[*position];
		(*position)++;
		while (input[*position] && input[*position] != quote)
			(*position)++;
	}
}

char	**divide_input(char *input)
{
	static size_t	size = 0;
	size_t			position;
	char			**command_strings;

	if (!*input && size == 0)
		return ((void *)0);
	if (!*input)
		return (ft_calloc(size + 1, sizeof(char *)));
	position = 0;
	while (input[position] && input[position] != '|')
	{
		handle_quotes(input, &position);
		position++;
	}
	if (input[position])
		position++;
	size++;
	command_strings = divide_input(input + position);
	size--;
	if (input[position])
		position--;
	command_strings[size] = ft_substr(input, 0, position);
	if (!command_strings[size])
		return (free_command_strings(command_strings, size));
	return (command_strings);
}

char	*initial_translation(char *input, char **envp, int exitno)
{
	char	*var_translation;
	char	*file_translation;

	var_translation = var_translator(input, envp, exitno);
	if (!var_translation)
		return ((void *)0);
	file_translation = file_translator(var_translation);
	freedom((void **)&var_translation);
	return (file_translation);
}

void	remove_quotes(char *input)
{
	size_t	position;
	size_t	disp;
	char	quote;

	position = 0;
	disp = 0;
	while (input[position + disp])
	{
		if (input[position + disp] == '"'
			|| input[position + disp] == '\'')
		{
			quote = input[position + disp++];
			while (input[position + disp] != quote)
			{
				input[position] = input[position + disp];
				position++;
			}
			disp++;
		}
		input[position] = input[position + disp];
		if (input[position + disp] && input[position + disp] != '"'
			&& input[position + disp] != '\'')
			position++;
	}
	input[position] = input[position + disp];
}
