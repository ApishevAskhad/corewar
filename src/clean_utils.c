/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gloras-t <gloras-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 21:15:22 by slindgre          #+#    #+#             */
/*   Updated: 2019/11/05 18:41:43 by gloras-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void    destroy(void *ptr)
{
    free(ptr);
    ptr = NULL;   
}
