/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gloras-t <gloras-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 21:43:42 by gloras-t          #+#    #+#             */
/*   Updated: 2019/10/28 23:18:45 by gloras-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void	read_file(char *file_name)
{
	int		fd;
	int		ret;
	char	buf[BUFF_SIZE];

	fd = open(file_name, O_RDONLY);
	if (fd > -1)
	{
		ft_bzero(buf, BUFF_SIZE);
		ret = read(fd, buf, BUFF_SIZE);
		if (has_header(&buf[0]))
			ft_printf("header is here\n");
	}
	else
		print_error("file not open");
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
