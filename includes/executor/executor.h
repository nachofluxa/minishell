/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifluxa-c <ifluxa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:45:29 by nachofluxa        #+#    #+#             */
/*   Updated: 2025/04/29 12:25:51 by ifluxa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "parser/parser.h"

int		execute_commands(t_command **cmds, char **envp, int exitno);
int		open_output(char *file);
int		open_input(char *file, char **envp, int exitno);
int		is_builtin(t_command *command);
int		lets_see_the_builtin(t_command *command);
int		count_commands(t_command **command);
int		execute_command(t_command *command, char **envp);
void	close_auxfd(int (*auxfd)[2]);
void	free_auxfd(int (*auxfd)[2]);

#endif
