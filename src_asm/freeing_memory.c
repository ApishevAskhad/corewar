/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing_memory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 01:44:01 by dtimeon           #+#    #+#             */
/*   Updated: 2020/05/11 02:06:05 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void			delete_file(t_file **file)
{
	// TODO: frees memory, allocated for lines, and other nested structs
	ft_memdel((void **)file);
}
