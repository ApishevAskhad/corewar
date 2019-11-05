/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gloras-t <gloras-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 22:15:59 by slindgre          #+#    #+#             */
/*   Updated: 2019/11/05 23:12:08 by gloras-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		read_file(char *file_name, char *buf)
{
	int		fd;
	int		ret;

	if ((fd = open(file_name, O_RDONLY)) > 2)
	{
		ret = read(fd, buf, MIN_FILE_SIZE + CHAMP_MAX_SIZE + 1);
		if (ret < MIN_FILE_SIZE)
			print_error("not enough data in file ", file_name);
		if (ret > (MIN_FILE_SIZE + CHAMP_MAX_SIZE))
			print_error("champion's execution code is too large ", file_name);
		close(fd);
	}
	else
		print_error("can't read source file ", file_name);
}

void		validate_player(char *file_name, t_player *player, char *buf)
{
	if (has_header(buf))
	{
		buf += 4;
		ft_memcpy(player->prog_name, buf, PROG_NAME_LENGTH);
		buf += PROG_NAME_LENGTH;
		if (has_gap(buf))
		{
			buf += 4;
			player->prog_size = convert_to_ui(buf);
			buf += 4;
			ft_memcpy(player->comment, buf, COMMENT_LENGTH);
			buf += COMMENT_LENGTH;
			if (has_gap(buf))
			{
				buf += 4;
				ft_memcpy(player->code, buf, player->prog_size);
			}
			else
				print_error("no second gap in ", file_name);
		}
		else
			print_error("no first gap in ", file_name);
	}
	else
		print_error("no magic header in ", file_name);
}

t_player	create_player(char *file_name)
{
	t_player	player;
	char		buf[MIN_FILE_SIZE + CHAMP_MAX_SIZE];

	ft_bzero(buf, MIN_FILE_SIZE + CHAMP_MAX_SIZE);
	read_file(file_name, buf);
	ft_bzero(&player, sizeof(player));
	validate_player(file_name, &player, buf);
	return (player);
}
