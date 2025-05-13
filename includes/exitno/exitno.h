/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exitno.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachofluxa <nachofluxa@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:22:39 by ifluxa-c          #+#    #+#             */
/*   Updated: 2025/04/29 12:50:49 by nachofluxa       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXITNO_H
# define EXITNO_H

# include "parser/parser.h"

int	ft_wifexited(int status);
int	ft_wexitstatus(int status);
int	ft_wifsignaled(int status);
int	ft_wtermsig(int status);
int	get_exitno(int status, int pos, t_command *cmd, int *exitno);

#endif
