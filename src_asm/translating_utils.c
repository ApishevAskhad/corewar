/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translating_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 14:13:56 by dtimeon           #+#    #+#             */
/*   Updated: 2020/06/04 14:14:15 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

size_t			to_big_endian(size_t le_num, unsigned int size)
{
	int			len;
	int			i;
	size_t		be_num;

	len = size - 1;
	i = 0;
	be_num = 0;
	while (i <= len)
	{
		((unsigned char *)&be_num)[i] = ((unsigned char *)&le_num)[len - i];
		i++;
	}
	return (be_num);
}
