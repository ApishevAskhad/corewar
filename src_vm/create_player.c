/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 22:15:59 by slindgre          #+#    #+#             */
/*   Updated: 2020/05/19 01:35:01 by slindgre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

UI				convert_to_ui(UC byte[4])
{
	UI	n;
	UI	*ptr;

	n = 0;
	ptr = (UI*)byte;
	n |= (*ptr & 0xFF000000) >> 24;
	n |= (*ptr & 0x00FF0000) >> 8;
	n |= (*ptr & 0x0000FF00) << 8;
	n |= (*ptr & 0x000000FF) << 24;
	return (n);
}

int				is_cor_extension(char *file_name)
{
	size_t	length;

	assert(file_name != NULL);
	length = ft_strlen(file_name);
	if (length >= 4 && !ft_strcmp(COR_EXTENSION, file_name + length - 4))
		return (TRUE);
	print_error(ERR_NO_COR, file_name);
	return (FALSE);
}

static void		read_file(char *file_name, UC *buf)
{
	int		fd;
	UI		ret;

	if ((fd = open(file_name, O_RDONLY)) > 2)
	{
		ret = read(fd, buf, MIN_FILE_SIZE + CHAMP_MAX_SIZE + 1);
		if (ret < MIN_FILE_SIZE)
			print_error(ERR_SMALL_FILE, file_name);
		if (ret > (MIN_FILE_SIZE + CHAMP_MAX_SIZE))
			print_error(ERR_LARGE_EXEC_CODE, file_name);
		if ((MIN_FILE_SIZE + convert_to_ui(buf + (4 + PROG_NAME_LENGTH + 4)))
		!= ret)
			print_error(ERR_WRONG_EXEC_CODE, file_name);
		close(fd);
	}
	else
		print_error(ERR_FILE_OPEN, file_name);
}

static void		validate_player(char *file_name, t_player *player, UC *buf)
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
				print_error(ERR_NO_GAP_2, file_name);
		}
		else
			print_error(ERR_NO_GAP_1, file_name);
	}
	else
		print_error(ERR_NO_MAGIC, file_name);
}

t_player		create_player(char *file_name)
{
	t_player	player;
	UC			buf[MIN_FILE_SIZE + CHAMP_MAX_SIZE];

	is_cor_extension(file_name);
	ft_bzero(buf, MIN_FILE_SIZE + CHAMP_MAX_SIZE);
	read_file(file_name, buf);
	ft_bzero(&player, sizeof(t_player));
	validate_player(file_name, &player, buf);
	return (player);
}
