/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freedom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachofluxa <nachofluxa@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:29:17 by nachofluxa        #+#    #+#             */
/*   Updated: 2025/04/15 10:29:42 by nachofluxa       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "freedom/freedom.h"
#include <stdlib.h>

void	freedom(void **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = (void *)0;
	}
}
