/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifluxa-c <ifluxa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:33:45 by nachofluxa        #+#    #+#             */
/*   Updated: 2025/04/15 19:44:35 by ifluxa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_command
{
	char	**args;
	char	*input;
	char	*output;
}	t_command;

void		free_command(t_command **command);
t_command	*parser(char **lexems);

#endif