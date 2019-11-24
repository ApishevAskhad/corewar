/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_options_handling.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 23:12:42 by dtimeon           #+#    #+#             */
/*   Updated: 2019/11/20 00:14:04 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		main(void)
{
	assert(read_options("-aaaaa") == 1);
	assert(read_options("-a") == 1);
	assert(read_options("-") == 0);
	assert(read_options("-abc") == 1);
	assert(read_options("-bcd.23") == 0);
	assert(read_options("") == 0);
	assert(read_options("-babacde") == 1);
	assert(read_options("abcd") == 0);
	assert(read_options("a") == 0);
	assert(read_options("aaaaa") == 0);
	ft_printf("OK: options handling\n");
}