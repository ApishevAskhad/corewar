/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   players_maker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 21:58:04 by slindgre          #+#    #+#             */
/*   Updated: 2020/06/22 02:00:19 by slindgre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int	main()
{
    uint8_t	s[4];
    int     fd;
    
    s[0] = 0;
	s[1] = 0xEA;
	s[2] = 0x83;
	s[3] = 0xF3;
    fd = open("Player_valid.cor", O_WRONLY|O_TRUNC|O_CREAT, 0777);
    ft_printf("%c%c%c%c%_", s[0], s[1], s[2], s[3], fd);
    ft_printf("%-128s%_", "name", fd);
    ft_printf("%c%c%c%c%_", 0, 0, 0, 0, fd);
    ft_printf("%c%c%c%c%_", 0, 0, 0, 4, fd);
    ft_printf("%-2048s%_", "comment", fd);
    ft_printf("%c%c%c%c%_", 0, 0, 0, 0, fd);
    ft_printf("%s%_", "code", fd);
    close(fd);

    fd = open("Player_small_file.cor", O_WRONLY|O_TRUNC|O_CREAT, 0777);
    ft_printf("%c%c%c%c%_", s[0], 0, s[2], s[3], fd);
    ft_printf("%-128s%_", "name", fd);
    ft_printf("%c%c%c%c%_", 0, 0, 0, 0, fd);
    ft_printf("%c%c%c%c%_", 0, 0, 0, 4, fd);
    ft_printf("%-2048s%_", "comment", fd);
    close(fd);
    
    fd = open("Player_prog_size_more_then_MAX.cor", O_WRONLY|O_TRUNC|O_CREAT, 0777);
    ft_printf("%c%c%c%c%_", s[0], s[1], s[2], s[3], fd);
    ft_printf("%-128s%_", "name", fd);
    ft_printf("%c%c%c%c%_", 0, 0, 0, 0, fd);
    ft_printf("%c%c%c%c%_", 0, 0, 0, 0, fd);
    ft_printf("%-2048s%_", "comment", fd);
    ft_printf("%c%c%c%c%_", 0, 0, 0, 0, fd);
    ft_printf("%*s%_", CHAMP_MAX_SIZE + 1, "code", fd);
    close(fd);
    
    fd = open("Player_wrong_prog_size_1.cor", O_WRONLY|O_TRUNC|O_CREAT, 0777);
    ft_printf("%c%c%c%c%_", s[0], s[1], s[2], s[3], fd);
    ft_printf("%-128s%_", "name", fd);
    ft_printf("%c%c%c%c%_", 0, 0, 0, 0, fd);
    ft_printf("%c%c%c%c%_", 0, 0, 0, 100, fd);
    ft_printf("%-2048s%_", "comment", fd);
    ft_printf("%c%c%c%c%_", 0, 0, 0, 0, fd);
    ft_printf("%*s%_", 101, "code", fd);
    close(fd);
    
    fd = open("Player_wrong_prog_size_2.cor", O_WRONLY|O_TRUNC|O_CREAT, 0777);
    ft_printf("%c%c%c%c%_", s[0], s[1], s[2], s[3], fd);
    ft_printf("%-128s%_", "name", fd);
    ft_printf("%c%c%c%c%_", 0, 0, 0, 0, fd);
    ft_printf("%c%c%c%c%_", 0, 0, 0, 100, fd);
    ft_printf("%-2048s%_", "comment", fd);
    ft_printf("%c%c%c%c%_", 0, 0, 0, 0, fd);
    ft_printf("%*s%_", 99, "code", fd);
    close(fd);
    
    fd = open("Player_no_magic.cor", O_WRONLY|O_TRUNC|O_CREAT, 0777);
    ft_printf("%c%c%c%c%_", s[0], 0, s[2], s[3], fd);
    ft_printf("%-128s%_", "name", fd);
    ft_printf("%c%c%c%c%_", 0, 0, 0, 0, fd);
    ft_printf("%c%c%c%c%_", 0, 0, 0, 4, fd);
    ft_printf("%-2048s%_", "comment", fd);
    ft_printf("%c%c%c%c%_", 0, 0, 0, 0, fd);
    ft_printf("%s%_", "code", fd);
    close(fd);
    
    fd = open("Player_no_gap_1.cor", O_WRONLY|O_TRUNC|O_CREAT, 0777);
    ft_printf("%c%c%c%c%_", s[0], s[1], s[2], s[3], fd);
    ft_printf("%-128s%_", "name", fd);
    ft_printf("%c%c%c%c%_", 0, 0, 0, 1, fd);
    ft_printf("%c%c%c%c%_", 0, 0, 0, 4, fd);
    ft_printf("%-2048s%_", "comment", fd);
    ft_printf("%c%c%c%c%_", 0, 0, 0, 0, fd);
    ft_printf("%s%_", "code", fd);
    close(fd);

    fd = open("Player_no_gap_2.cor", O_WRONLY|O_TRUNC|O_CREAT, 0777);
    ft_printf("%c%c%c%c%_", s[0], s[1], s[2], s[3], fd);
    ft_printf("%-128s%_", "name", fd);
    ft_printf("%c%c%c%c%_", 0, 0, 0, 0, fd);
    ft_printf("%c%c%c%c%_", 0, 0, 0, 4, fd);
    ft_printf("%-2048s%_", "comment", fd);
    ft_printf("%c%c%c%c%_", 0, 0, 0, 1, fd);
    ft_printf("%s%_", "code", fd);
    close(fd);

    return (0);
}