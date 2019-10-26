/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 19:19:53 by slindgre          #+#    #+#             */
/*   Updated: 2019/01/17 15:55:35 by slindgre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strnequ(const char *s1, const char *s2, size_t n)
{
	unsigned char	c1;
	unsigned char	c2;

	if (n == 0)
		return (1);
	if (!s1 || !s2)
		return (0);
	c1 = *s1;
	c2 = *s2;
	while ((c1 == c2) && n--)
	{
		if ((c1 == '\0' && c2 == '\0') || n == 0)
			return (1);
		c1 = *s1++;
		c2 = *s2++;
	}
	return (0);
}
