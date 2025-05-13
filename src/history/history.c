/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachofluxa <nachofluxa@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:50:37 by nachofluxa        #+#    #+#             */
/*   Updated: 2025/04/29 12:51:16 by nachofluxa       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "history/history.h"
#include "libft/libft.h"
#include "freedom/freedom.h"
#include "get_next_line/get_next_line.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include <unistd.h>

void	save_history(char *commands[MAX_HISTORY], const int last)
{
	size_t	position;
	int		fd;

	fd = open("/tmp/history.txt", O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (!fd)
	{
		perror("minishell");
		return ;
	}
	position = 0;
	if (commands[last + 1])
		position = last + 1;
	while (position % MAX_HISTORY != last)
		ft_putendl_fd(commands[position++], fd);
	close(fd);
}

void	load_history(char *(*commands)[MAX_HISTORY], size_t *position)
{
	char	*command;
	int		fd;

	(*position) = 0;
	while ((*position) < MAX_HISTORY)
		(*commands)[(*position)++] = (void *)0;
	fd = open("/tmp/history.txt", O_RDONLY);
	if (!fd)
		return ;
	(*position) = 0;
	while ((*position) < MAX_HISTORY)
	{
		command = get_next_line(fd);
		if (!command)
			break ;
		if (command[ft_strlen(command) - 1] == '\n')
			command[ft_strlen(command) - 1] = '\0';
		add_history(command);
		(*commands)[(*position)++] = command;
	}
	close(fd);
}

void	my_clean_history(char *(*commands)[MAX_HISTORY])
{
	size_t	position;

	rl_clear_history();
	position = 0;
	while (position < MAX_HISTORY)
		freedom((void **)((*commands) + position++));
}

void	manage_history(char *str, t_state state)
{
	static size_t	position = 0;
	static char		*commands[MAX_HISTORY];

	if (state == SAVE)
		save_history(commands, position);
	else if (state == CLEAN)
		my_clean_history(&commands);
	else if (state == LOAD)
		load_history(&commands, &position);
	else
	{
		add_history(str);
		commands[position++] = ft_strdup(str);
	}
}
