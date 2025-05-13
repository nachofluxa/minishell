/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_main.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifluxa-c <ifluxa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 18:01:20 by nachofluxa        #+#    #+#             */
/*   Updated: 2025/04/15 19:42:56 by ifluxa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUX_MAIN_H
# define AUX_MAIN_H

char		**divide_input(char *input);
char		*initial_translation(char *input, char **envp, int exitno);
void		remove_quotes(char *input);
t_command	**process_input(char *input, char **envp, int exitno);

#endif
