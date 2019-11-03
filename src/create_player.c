/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 22:15:59 by slindgre          #+#    #+#             */
/*   Updated: 2019/11/03 17:48:29 by slindgre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

UI			swipe_bytes(UI n) 
{
	UI	res;

	res = 0;
	res = (n & 0x000000ff) << 24;
	res += (n & 0x0000ff00) << 8;
	res += (n & 0x00ff0000) >> 8;
	res += (n & 0xff000000) >> 24;
	return (res);
}

int			check_file(char *file_name)
{
	int	fd;

	if ((fd = open(file_name, O_RDONLY)) < 0)
		print_error("Couldn't open file", file_name);
	return (fd);
}

t_player	create_player(int fd, char *file_name)
{
	int			fd;
	t_player	player;
	UI			gap_1;
	UI			gap_2;

	ft_bzero(&player, sizeof(player));
	if (sizeof(UI) != read(fd, &player.magic, sizeof(UI)) ||
		PROG_NAME_LENGTH != read(fd, &player.prog_name, PROG_NAME_LENGTH) ||
		sizeof(UI) != read(fd, &gap_1, sizeof(UI)) ||
		sizeof(UI) != read(fd, &player.prog_size, sizeof(UI)) ||
		COMMENT_LENGTH != read(fd, &player.comment, COMMENT_LENGTH) ||
		sizeof(UI) != read(fd, &gap_2, sizeof(UI)))
		print_error("Not enough data in ", file_name);
	player.magic = swipe_bytes(player.magic);
	player.prog_size = swipe_bytes(player.prog_size);
	if (player.prog_size > CHAMP_MAX_SIZE)
		print_error("Champ code is bigger than CHAMP_MAX_SIZE: ", file_name);
	else if (player.prog_size != read(fd, &player.code, player.prog_size + 1))
		print_error("Size of champ code isn't correctly specified in ", file_name);
	if (gap_1 != 0)
		print_error("There is no space after champ name in: ", file_name);
	if (gap_2 != 0)
		print_error("There is no space after champ comment in: ", file_name);
	close(fd);
	return (player);
}
