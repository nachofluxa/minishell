/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachofluxa <nachofluxa@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:09:19 by nachofluxa        #+#    #+#             */
/*   Updated: 2025/04/29 13:04:34 by nachofluxa       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors/errors.h"
#include <stdio.h>

void	command_error(t_command *command, int type)
{
	if (type == 0)
		printf("minishell: command not found: '%s'\n", command->args[0]);
	else if (type == 1)
		printf("%s: too many arguments\n", command->args[0]);
}

void	args_error(char *command, char *args, int type)
{
	if (type == 0)
		printf("%s: no such file or directory: '%s'\n", command, args);
	else if (type == 1)
		printf("%s: not enough arguments\n", command);
	else if (type == 2)
		printf("%s: %s: no such file or directory\n", command, args);
	else if (type == 3)
		printf("%s: %s: not a valid identifier\n", command, args);
	else if (type == 4)
		printf("%s: %s: numeric argument required\n", command, args);
}

int	checker_errors(int type)
{
	if (type == 0)
		printf("ERROR: There is an open quote.\n");
	else if (type == 1)
		printf("minishell: parse error near '\\n'\n");
	else if (type == 2)
		printf("ERROR: There is a command missing after pipe.\n");
	else if (type == 3)
		printf("minishell: no such file or directory\n");
	return (-1);
}
