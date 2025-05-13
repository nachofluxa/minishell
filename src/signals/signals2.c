/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachofluxa <nachofluxa@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 20:07:07 by nachofluxa        #+#    #+#             */
/*   Updated: 2025/04/29 12:51:29 by nachofluxa       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals/signals.h"
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

static void	sigint_handler2(int signo)
{
	(void)signo;
	g_received_signal = SIGINT;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_redisplay();
}

void	setup_signals2(void)
{
	struct sigaction	sa;

	sa.sa_handler = sigint_handler2;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		perror("Error en sigaction(SIGINT)");
}
