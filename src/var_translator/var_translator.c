/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_translator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifluxa-c <ifluxa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:30:07 by nachofluxa        #+#    #+#             */
/*   Updated: 2025/04/29 12:18:21 by ifluxa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "freedom/freedom.h"
#include <stdlib.h>
#include <stdio.h>

static char	*get_var_value(char *var_name, char **env, int exitno)
{
	int		i;
	char	*var_value;

	if (*var_name == '?')
		return (ft_itoa(exitno));
	var_value = NULL;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var_name, ft_strlen(var_name)) == 0
			&& env[i][ft_strlen(var_name)] == '=')
		{
			var_value = ft_strdup(env[i] + ft_strlen(var_name) + 1);
			break ;
		}
		i++;
	}
	if (!var_value)
		var_value = ft_strdup("");
	return (var_value);
}

static char	*create_new_str(char *result, char *var_start,
							char *var_end, char *var_value)
{
	char	*temp;
	size_t	new_len;

	new_len = ft_strlen(result) - (var_end - var_start) + ft_strlen(var_value);
	temp = (char *)malloc(new_len + 1);
	if (!temp)
		return (NULL);
	ft_strlcpy(temp, result, var_start - result + 1);
	ft_strlcat(temp, var_value, new_len + 1);
	ft_strlcat(temp, var_end, new_len + 1);
	return (temp);
}

static char	*to_var_end(char *str)
{
	if (*str == '?')
		str++;
	else
		while (*str && (ft_isalnum(*str) || *str == '_'))
			str++;
	if (*str == '"' || *str == '\'')
		str--;
	return (str);
}

static char	*handle_variable(char **current, char *result, char **env, int exit)
{
	char	*vstart;
	char	*vend;
	char	*var_name;
	char	*var_value;
	char	*temp;

	vstart = *current;
	vend = *current + 1;
	if (!ft_isalpha(*vend) && *vend != '_' && *vend != '?')
		(*current)++;
	if (!ft_isalpha(*vend) && *vend != '_' && *vend != '?')
		return (result);
	vend = to_var_end(vend);
	var_name = ft_substr(vstart + 1, 0, ft_strlen(vstart) - ft_strlen(vend));
	if (!var_name)
		return (NULL);
	var_value = get_var_value(var_name, env, exit);
	if (ft_strlen(vend) > 1 && (vend[1] == '\'' || vend[1] == '"'))
		vend++;
	temp = create_new_str(result, vstart, vend, var_value);
	*current = temp + (vstart - result) + ft_strlen(var_value);
	freedom((void **)&var_name);
	freedom((void **)&var_value);
	freedom((void **)&result);
	return (temp);
}

char	*var_translator(char *input, char **envp, int exitno)
{
	char	*result;
	char	*current;
	int		in_single_quotes;
	int		in_double_quotes;

	result = ft_strdup(input);
	current = result;
	in_single_quotes = 0;
	in_double_quotes = 0;
	while (*current)
	{
		if (*current == '"')
			in_double_quotes = !in_double_quotes;
		else if (*current == '\'' && !in_double_quotes)
			in_single_quotes = !in_single_quotes;
		if (*current == '$' && !in_single_quotes)
			result = handle_variable(&current, result, envp, exitno);
		else
			current++;
	}
	return (result);
}
