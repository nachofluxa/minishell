/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifluxa-c <ifluxa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:29:02 by nachofluxa        #+#    #+#             */
/*   Updated: 2025/04/15 19:41:47 by ifluxa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer.h"
#include "freedom/freedom.h"
#include "libft/libft.h"
#include <stdlib.h>

static size_t	limitpos(char *input)
{
	size_t	position;
	char	quote;

	position = 0;
	while (input[position])
	{
		if (input[position] == ' ' || input[position] == '\t')
			break ;
		if (input[position] == '\'' || input[position] == '"')
		{
			quote = input[position++];
			while (input[position] != quote)
				position++;
		}
		position++;
	}
	return (position);
}

char	**lexer(char *input)
{
	static size_t	size = 0;
	size_t			position;
	char			**lexems;

	while (*input == ' ' || *input == '\t')
		input++;
	if (!*input && size == 0)
		return ((void *)0);
	else if (!*input)
		return (ft_calloc(size + 1, sizeof(char *)));
	position = limitpos(input);
	size++;
	lexems = lexer(input + position);
	size--;
	if (!lexems)
		return ((void *)0);
	lexems[size] = ft_substr(input, 0, position);
	if (lexems[size])
		return (lexems);
	position = size + 1;
	while (lexems[position])
		freedom((void **)(lexems + position++));
	return ((void *)0);
}
