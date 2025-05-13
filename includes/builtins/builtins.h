/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifluxa-c <ifluxa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:03:21 by nachofluxa        #+#    #+#             */
/*   Updated: 2025/04/15 19:44:00 by ifluxa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "parser/parser.h"

int		check_builtins(t_command *command, char **envp);
int		ft_echo(t_command *command);
int		ft_cd(t_command *command);
int		ft_pwd(t_command *command);
int		ft_export(t_command *command, char **envp);
int		ft_unset(t_command *command, char **envp);
int		ft_env(t_command *commands, char **envp);
int		ft_exit(t_command *command);
void	set_environ(char **environ, char **args, int size, int i);
char	**get_env(char **envp);

#endif