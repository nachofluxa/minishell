/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachofluxa <nachofluxa@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 20:07:07 by nachofluxa        #+#    #+#             */
/*   Updated: 2025/04/29 12:50:38 by nachofluxa       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>

extern sig_atomic_t	g_received_signal;

void	setup_signals(void);
void	setup_signals2(void);
void	setup_heredoc_signals(void);

#endif
