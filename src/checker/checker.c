/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifluxa-c <ifluxa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:17:50 by nachofluxa        #+#    #+#             */
/*   Updated: 2025/04/21 19:35:24 by ifluxa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker/checker.h"
#include "errors/errors.h"
#include "libft/libft.h"
#include "freedom/freedom.h"
#include "parser/parser.h"

static int	check_quotes(char **input)
{
	int	i;
	int	j;
	int	single_quote;
	int	double_quote;

	single_quote = 0;
	double_quote = 0;
	i = -1;
	while (input[++i])
	{
		j = -1;
		while (input[i][++j])
		{
			if (input[i][j] == '\'' && double_quote == 0)
				single_quote = !single_quote;
			else if (input[i][j] == '\"' && single_quote == 0)
				double_quote = !double_quote;
		}
	}
	if (single_quote || double_quote)
		return (-1);
	return (0);
}

static int	check_double_output(char **input)
{
	int	i;
	int	j;

	i = 0;
	while (input[i])
	{
		j = 0;
		while (input[i][j])
		{
			if (input[i][j] == '<' && input[i][j + 1] == '<')
			{
				j += 2;
				while (input[i][j] == ' ' || input[i][j] == '\t')
					j++;
				if (input[i][j] == '\0' && !input[i + 1])
					return (-1);
			}
			else
				j++;
		}
		i++;
	}
	return (0);
}

static int	check_input_output(char **input)
{
	int	i;
	int	j;

	i = 0;
	while (input[i])
	{
		j = 0;
		while (input[i][j])
		{
			if (input[i][j] == '<' || input[i][j] == '>')
			{
				j++;
				while (input[i][j] == ' ' || input[i][j] == '\t')
					j++;
				if (input[i][j] == '\0' && !input[i + 1])
					return (-1);
			}
			else
				j++;
		}
		i++;
	}
	return (0);
}

static int	check_pipe(char **input)
{
	int	i;
	int	j;

	i = 0;
	while (input[i])
	{
		j = 0;
		while (input[i][j])
		{
			if (input[i][j] == '|')
			{
				j++;
				if (input[i][j] == '|')
					return (-1);
				while (input[i][j] == ' ' || input[i][j] == '\t')
					j++;
				if (input[i][j] == '\0' && !input[i + 1])
					return (-1);
			}
			else
				j++;
		}
		i++;
	}
	return (0);
}

int	checker(char *input)
{
	int		lets_free;
	char	**aux_args;
	size_t	position;

	lets_free = 0;
	aux_args = ft_split(input, ' ');
	if (!aux_args)
		return (-1);
	if (!aux_args[0])
		freedom((void **)&aux_args);
	if (!aux_args)
		return (-1);
	if (check_quotes(aux_args) == -1)
		lets_free = checker_errors(0);
	if (check_double_output(aux_args) == -1)
		lets_free = checker_errors(1);
	if (check_input_output(aux_args) == -1)
		lets_free = checker_errors(1);
	if (check_pipe(aux_args) == -1)
		lets_free = checker_errors(2);
	position = 0;
	while (aux_args[position])
		freedom((void **)(aux_args + position++));
	freedom((void **)&aux_args);
	return (lets_free);
}
