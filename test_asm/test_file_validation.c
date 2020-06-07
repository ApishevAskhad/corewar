/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_file_validation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 21:01:32 by dtimeon           #+#    #+#             */
/*   Updated: 2020/05/09 23:43:16 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

typedef struct	test_file
{
	char		*filename;
	int			is_valid;
}				test_file;

int				main(void)
{
	test_file	files[16] = {{"./test_asm/assets/file_validation/ ", 0},
							{"./test_asm/assets/file_validation/-", 0},
							{"./test_asm/assets/file_validation/abc.co", 0},
							{"./test_asm/assets/file_validation/abc.ds", 0},
							{"./test_asm/assets/file_validation/abc.sd", 0},
							{"./test_asm/assets/file_validation/-a.cor", 1},
							{"./test_asm/assets/file_validation/a.cor", 1},
							{"./test_asm/assets/file_validation/-a.s", 1},
							{"./test_asm/assets/file_validation/b.s", 1},
							{"./test_asm/assets/file_validation/dir", 0},
							{"./test_asm/assets/file_validation/dir.cor", 0},
							{"./test_asm/assets/file_validation/no_permission", 0},
							{"./test_asm/assets/file_validation/no_permission.cor", 0},
							{"./test_asm/assets/file_validation/non_existent", 0},
							{"./test_asm/assets/file_validation/non_existent.cor", 0}};
	int			fd;

	for (int i = 0; i < 15; i++)
	{
		fd = open(files[i].filename, O_RDONLY);
		assert(is_valid_file(fd, files[i].filename) == files[i].is_valid);
	}
	ft_printf("OK: file validation\n");
}
