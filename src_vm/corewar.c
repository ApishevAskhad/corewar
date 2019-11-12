/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 21:43:42 by gloras-t          #+#    #+#             */
/*   Updated: 2019/11/12 22:40:31 by slindgre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		main(int argc, char *argv[])
{
	if (argc > 1)
	{
		if (is_cor_extension(argv[1]))
			create_player(argv[1]);
		else
			print_error("file extension is not .cor: ", argv[1]);
	}
	else
		print_usage();
	return (0);
}
