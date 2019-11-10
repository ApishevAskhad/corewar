/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_convert_to_ui.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gloras-t <gloras-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 22:54:39 by gloras-t          #+#    #+#             */
/*   Updated: 2019/11/10 22:59:54 by gloras-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int main()
{
	UC	s[4];
	UI	n;

	ft_bzero(s, 4);
	n = convert_to_ui(s);
	assert(n == 0);

	s[3] = 15;
	n = convert_to_ui(s);	
	assert(n == 15);

	s[3] = 117;
	n = convert_to_ui(s);
	assert(n = 117);

	s[3] = 0;
	s[2] = 1;
	n = convert_to_ui(s);
	assert(n == 256);

	s[0] = 0;
	s[1] = 0xEA;
	s[2] = 0x83;
	s[3] = 0xF3;
	n = convert_to_ui(s);
	assert(n == COREWAR_EXEC_MAGIC);

	ft_printf("{green}OK{eoc} {yellow}convert_to_ui(char byte[4]);{eoc}\n");
	return (0);
}
