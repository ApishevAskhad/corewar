/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_file_reading.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 23:39:53 by dtimeon           #+#    #+#             */
/*   Updated: 2020/05/11 19:30:03 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

#define FOL "./test_asm/assets/file_reading/"


typedef struct	test_file
{
	char		*filename;
	char		*first_line;
	char		*last_line;
	int			total_lines_saved;
}				test_file;


int				count_saved_lines(t_file *file)
{
	int			lines_num = 0;
	t_line		*current_line;

	if (file->first_line->initial_str)
		lines_num++;
	current_line = file->first_line->next;
	while (current_line)
	{
		lines_num++;
		current_line = current_line->next;
	}
	return (lines_num);
}

int				main(void)
{
	test_file	files[7] = {{FOL "empty.s", NULL, NULL, 0},
							{FOL "single_comment.s", " \t# hi!", " \t# hi!", 1},
							{FOL "no_new_line.s", ".name \"ABCDE\"", NULL, 4},
							{FOL "one_new_line.s", ".name \"ABCDE\"", NULL, 4},
							{FOL "ends_with_comment.s", ".name \"ABCDE\"", " ; hi!", 4},
							{FOL "only_blank_and_comments.s", "# hi!", "# hi!", 1},
							{FOL "ends_with_blank_and_comments.s", ".name \"ABCDE\"", "	  ", 4}};
	int			fd;
	t_file		*file;

	for (int i = 0; i < 7; i++)
	{
		fd = open(files[i].filename, O_RDONLY);
		file = read_file(fd, files[i].filename);

		if (files[i].first_line)
			assert(ft_strcmp(file->first_line->initial_str, files[i].first_line) == 0);
		else
			assert(!(file->first_line->initial_str));
		
		if (files[i].last_line)
			assert(ft_strcmp(file->last_line->initial_str, files[i].last_line) == 0);
		else
			assert(!(file->last_line->initial_str));

		assert(count_saved_lines(file) == files[i].total_lines_saved);
	}
	ft_printf("OK: asm-file reading\n");
	// TODO: test binary reading
}
