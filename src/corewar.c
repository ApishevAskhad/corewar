/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 21:43:42 by gloras-t          #+#    #+#             */
/*   Updated: 2019/10/29 21:12:05 by slindgre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_player	read_file(char *file_name)
{
	int			fd;
	size_t		size;
	t_player	player;

	size = 4 + PROG_NAME_LENGTH + 8 + COMMENT_LENGTH + CHAMP_MAX_SIZE;
	fd = open(file_name, O_RDONLY);
	ft_bzero(&player, sizeof(player));
	if (fd > -1)
	{
		if (sizeof(player.magic) == read(fd, &player.magic, sizeof(player.magic)))
			read(fd, player.prog_name, sizeof(player.prog_name));
	}
	else
		print_error("file not open");
	return (player);
}

int		main(int argc, char *argv[])
{	
	if (argc > 1)
	{
		if (is_cor_extension(argv[1]))
		{
			read_file(argv[1]);
		}
		else
			print_error("file extension is not .cor");
	}
	else
		print_usage();
	return (0);
}
