/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifluxa-c <ifluxa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:48:56 by nachofluxa        #+#    #+#             */
/*   Updated: 2025/04/15 19:27:35 by ifluxa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

# define MAX_HISTORY 500

# include <stdlib.h>

typedef enum e_state
{
	SAVE,
	LOAD,
	CLEAN,
	INSERT
}	t_state;

void	save_history(char *commands[MAX_HISTORY], const int last);
void	load_history(char *(*commands)[MAX_HISTORY], size_t *position);
void	my_clean_history(char *(*commands)[MAX_HISTORY]);
void	manage_history(char *str, t_state state);

#endif
