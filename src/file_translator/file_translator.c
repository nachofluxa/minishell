/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_translator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachofluxa <nachofluxa@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:29:28 by nachofluxa        #+#    #+#             */
/*   Updated: 2025/04/15 10:29:28 by nachofluxa       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "freedom/freedom.h"
#include "libft/libft.h"
#include <stddef.h>
#include <stdio.h>

static char	*strfile(char *input)
{
	size_t	position;
	char	quote;

	position = 0;
	while (input[position] && input[position] != '>' && input[position] != '<')
	{
		if (input[position] == '"' || input[position] == '\'')
		{
			quote = input[position++];
			while (input[position] != quote)
				position++;
		}
		position++;
	}
	if (!input[position])
		return ((void *)0);
	return (input + position);
}

static char	*strendfile(char *str)
{
	size_t	position;

	position = 1;
	if (*str == str[position])
		position++;
	while (str[position] == ' ')
		position++;
	while (str[position] && str[position] != ' ' && str[position] != '>'
		&& str[position] != '<' && str[position] != '"'
		&& str[position] != '\'' && str[position] != '|')
		position++;
	return (str + position);
}

static char	*file_name(char *str)
{
	size_t	start;
	size_t	end;
	char	*left;
	char	*right;
	char	*filestr;

	end = 1;
	if (str[end] == *str)
		end++;
	left = ft_substr(str, 0, end);
	start = end;
	while (str[start] == ' ')
		start++;
	end = start;
	while (str[end] && str[end] != ' ' && str[end] != '>' && str[end] != '<'
		&& str[end] != '"' && str[end] != '\'' && str[end] != '|')
		end++;
	right = ft_substr(str, start, end - start);
	filestr = ft_strjoin(left, right);
	freedom((void **)&left);
	freedom((void **)&right);
	right = filestr;
	filestr = ft_strjoin(" ", right);
	freedom((void **)&right);
	return (filestr);
}

char	*file_translator(char *input)
{
	char	*file;
	char	*file_end;
	char	*left;
	char	*right;
	char	*aux;

	file = strfile(input);
	if (!file)
		return (ft_strdup(input));
	file_end = strendfile(file);
	right = file_translator(file_end);
	left = file_name(file);
	aux = ft_strjoin(left, right);
	freedom((void **)&left);
	freedom((void **)&right);
	right = aux;
	left = ft_substr(input, 0, ft_strlen(input) - ft_strlen(file));
	aux = ft_strjoin(left, right);
	freedom((void **)&left);
	freedom((void **)&right);
	return (aux);
}
