/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_validate_player.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gloras-t <gloras-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 23:15:22 by gloras-t          #+#    #+#             */
/*   Updated: 2019/11/05 23:40:18 by gloras-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int main()
{
    int fd;

    char    *line;
    
    fd = open("file1", O_CREAT | O_RDWR);
    ft_printf("%_abc", fd);
    while (get_next_line(fd, &line))
    {
        ft_printf("%s\n", line);
        free(line);
    }
    free(line);
    return (0);
}
