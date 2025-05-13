/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exitno.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifluxa-c <ifluxa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:21:27 by ifluxa-c          #+#    #+#             */
/*   Updated: 2025/04/29 12:22:14 by ifluxa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parser.h"
#include <exitno/exitno.h>
#include <stdio.h>
#include "libft/libft.h"

int	ft_wifexited(int status)
{
	return (((status) & 0x7f) == 0);
}

int	ft_wexitstatus(int status)
{
	return (((status) & 0xff00) >> 8);
}

int	ft_wifsignaled(int status)
{
	return (((status) & 0x7f) != 0 && ((status) & 0x7f) != 0x7f);
}

int	ft_wtermsig(int status)
{
	return ((status) & 0x7f);
}

int	get_exitno(int status, int pos, t_command *cmd, int *exitno)
{
	int	last_status;

	if (cmd->args && cmd->args[0] && (ft_strncmp(cmd->args[0], "cd", 2) == 0
			|| ft_strncmp(cmd->args[0], "exit", 4) == 0
			|| ft_strncmp(cmd->args[0], "export", 6) == 0
			|| ft_strncmp(cmd->args[0], "unset", 5) == 0))
		return (*exitno);
	last_status = 0;
	if (pos > 0 && ft_wifexited(status))
		last_status = ft_wexitstatus(status);
	else if (pos > 0 && ft_wifsignaled(status))
		last_status = 128 + ft_wtermsig(status);
	return (last_status);
}
