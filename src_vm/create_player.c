/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gloras-t <gloras-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 22:15:59 by slindgre          #+#    #+#             */
/*   Updated: 2019/11/12 21:37:14 by gloras-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		read_file(char *file_name, UC *buf)
{
	int		fd;
	UI		ret;

	if ((fd = open(file_name, O_RDONLY)) > 2)
	{
		ret = read(fd, buf, MIN_FILE_SIZE + CHAMP_MAX_SIZE + 1);
		if (ret < MIN_FILE_SIZE)
			print_error("not enough data in file ", file_name);
		if (ret > (MIN_FILE_SIZE + CHAMP_MAX_SIZE))
			print_error("champion's execution code is too large ", file_name);
		if ((MIN_FILE_SIZE + convert_to_ui(buf + (4 + PROG_NAME_LENGTH + 4)))
		!= ret)
			print_error("code size doesn't fit with actual exec code size in ",
			file_name);
		close(fd);
	}
	else
		print_error("can't read source file ", file_name);
}

void		validate_player(char *file_name, t_player *player, UC *buf)
{
	player->magic = convert_to_ui(buf);
	if (player->magic == COREWAR_EXEC_MAGIC)
	{
		ft_memcpy(player->prog_name, buf += 4, PROG_NAME_LENGTH);
		if (!convert_to_ui(buf += PROG_NAME_LENGTH))
		{
			player->prog_size = convert_to_ui(buf += 4);
			ft_memcpy(player->comment, buf += 4, COMMENT_LENGTH);
			if (!convert_to_ui(buf += COMMENT_LENGTH))
				ft_memcpy(player->code, buf += 4, player->prog_size);
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
	UC			buf[MIN_FILE_SIZE + CHAMP_MAX_SIZE];

	ft_bzero(buf, MIN_FILE_SIZE + CHAMP_MAX_SIZE);
	read_file(file_name, buf);
	ft_bzero(&player, sizeof(player));
	validate_player(file_name, &player, buf);
	return (player);
}
