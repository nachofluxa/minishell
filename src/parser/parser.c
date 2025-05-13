/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifluxa-c <ifluxa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:35:47 by nachofluxa        #+#    #+#             */
/*   Updated: 2025/04/15 19:55:23 by ifluxa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parser.h"
#include "freedom/freedom.h"
#include "libft/libft.h"
#include <stdlib.h>

void	free_command(t_command **command)
{
	size_t	position;

	if (*command)
	{
		position = 0;
		while ((*command)->args[position])
			freedom((void **)((*command)->args + position++));
		freedom((void **)&((*command)->args));
		freedom((void **)&((*command)->input));
		freedom((void **)&((*command)->output));
		freedom((void **)command);
	}
}

static t_command	*init_command(size_t size)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (command)
	{
		command->input = (void *)0;
		command->output = (void *)0;
		command->args = ft_calloc(size + 1, sizeof(char *));
		if (!command->args)
			freedom((void **)&command);
	}
	return (command);
}

static void	insert_file(char **dst, char **org)
{
	if (*dst)
		freedom((void **)dst);
	*dst = *org;
}

t_command	*parser(char **lexems)
{
	static size_t	size = 0;
	char			*lexem;
	t_command		*command;

	if (!*lexems)
		return (init_command(size));
	if (**lexems != '>' && **lexems != '<')
		size++;
	command = parser(lexems + 1);
	if (**lexems != '>' && **lexems != '<')
		size--;
	if (!command)
		return ((void *)0);
	lexem = ft_strdup(*lexems);
	if (!lexem)
		free_command(&command);
	else if (*lexem == '>')
		insert_file(&command->output, &lexem);
	else if (*lexem == '<')
		insert_file(&command->input, &lexem);
	else
		command->args[size] = lexem;
	return (command);
}
