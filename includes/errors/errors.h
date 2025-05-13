/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifluxa-c <ifluxa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:07:47 by nachofluxa        #+#    #+#             */
/*   Updated: 2025/04/15 19:43:48 by ifluxa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include "parser/parser.h"

void	command_error(t_command *command, int type);
void	args_error(char *command, char *args, int type);
int		checker_errors(int type);

#endif