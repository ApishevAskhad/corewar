/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 21:15:22 by slindgre          #+#    #+#             */
/*   Updated: 2019/10/29 21:18:34 by slindgre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void    _free(void *ptr)
{
    free(ptr);
    ptr = NULL;   
}

void	error_exit(char *error, t_player *layer)
{
	if (error)
		ft_putendl_fd(error, 1);
	exit(1);
}