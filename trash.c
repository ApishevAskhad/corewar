/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trash.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gloras-t <gloras-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 22:55:43 by gloras-t          #+#    #+#             */
/*   Updated: 2019/10/29 22:57:09 by gloras-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		check_octet(char c, UI octet)
{
	UI		a;
	UI		b;
	UI		i;
	size_t	char_size;
	size_t	ui_size;

	i = 0;
	char_size = 8 * sizeof(char);
	ui_size = 8 * sizeof(UI);
	while (char_size--)
	{
		a = c & (1 << i);
		b = COREWAR_EXEC_MAGIC & (1 << (i + ui_size - octet));
		if ((a > 0 && b == 0) || (a == 0 && b > 0))
			return (0);
		i++;
	}
	return (1);
}

enum octet
{
	FIRST = 0,
	SECOND = 8,
	THIRD = 16,
	FORTH = 24
};

char	convert_ui_to_char(UI number, UI octet)
{
	char	c;
	size_t	size;
	UI		tmp;
	UI		offset;

	c = 0;
	tmp = 0;
	offset = octet;
	size = 8 * sizeof(char);
	while (size--)
	{
		tmp = number & (1 << octet);
		tmp >>= offset;
		c |= tmp;
		octet++;
	}
	return c;
}
