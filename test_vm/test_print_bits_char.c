/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_print_bits_char.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gloras-t <gloras-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 21:32:37 by gloras-t          #+#    #+#             */
/*   Updated: 2019/11/10 21:40:55 by gloras-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int	main()
{
	char	c;
	int		out;
	int		p[2];
	char	*line;

	out = dup(1);
	pipe(p);
	dup2(p[1], 1);

	c = 1;
	print_bits_char(c);

	close(p[1]);
	dup2(out, 1);
	get_next_line(p[0], &line);
	assert(!ft_strcmp(line, "00000001"));
	free(line);

	return (0);
}
