/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 04:05:53 by dtimeon           #+#    #+#             */
/*   Updated: 2020/05/11 01:39:22 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		exit_with_allocation_error(char *filename)
{
	print_error(filename, "couldn't allocate enough memory");
	exit(EXIT_FAILURE);
}
