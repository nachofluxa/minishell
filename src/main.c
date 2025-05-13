/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachofluxa <nachofluxa@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 18:03:11 by nachofluxa        #+#    #+#             */
/*   Updated: 2025/04/29 13:12:53 by nachofluxa       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "freedom/freedom.h"
#include "parser/parser.h"
#include "executor/executor.h"
#include "history/history.h"
#include "checker/checker.h"
#include "builtins/builtins.h"
#include "aux_main/aux_main.h"
#include "signals/signals.h"
#include "libft/libft.h"

void	free_commands(t_command **commands)
{
	size_t	position;

	position = 0;
	while (commands[position])
		free_command(commands + position++);
	freedom((void **)&commands);
}

void	handle_history(char *input)
{
	manage_history(input, INSERT);
	manage_history(input, SAVE);
}

static char	*manage_loop_aux(void)
{
	char	*input;
	int		position;

	setup_signals();
	input = readline("$ > ");
	setup_signals2();
	if (!input)
		return ((void *)0);
	position = 0;
	while (input[position] == ' ' || input[position] == '\t')
		position++;
	if (!input[position])
	{
		freedom((void **)&input);
		return ("\0");
	}
	return (input);
}

void	manage_loop(char **envp)
{
	char		*input;
	t_command	**commands;
	int			exitno;

	exitno = 0;
	while (1)
	{
		input = manage_loop_aux();
		if (!input)
			break ;
		if (!*input)
			continue ;
		handle_history(input);
		if (checker(input) == -1)
			freedom((void **)&input);
		if (!input)
			continue ;
		commands = process_input(input, envp, exitno);
		freedom((void **)&input);
		if (!commands)
			break ;
		exitno = execute_commands(commands, envp, exitno);
		free_commands(commands);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	**my_envp;
	size_t	position;

	(void)argc;
	(void)argv;
	manage_history((void *)0, LOAD);
	my_envp = get_env(envp);
	manage_loop(my_envp);
	position = 0;
	while (my_envp[position])
		freedom((void **)(my_envp + position++));
	freedom((void **)&my_envp);
	manage_history((void *)0, CLEAN);
	printf("exit\n");
	return (0);
}
