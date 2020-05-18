/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_file_reading.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 23:39:53 by dtimeon           #+#    #+#             */
/*   Updated: 2020/05/18 22:22:45 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

#define FOL "./test_asm/assets/file_reading/"


typedef struct
{
	char			*filename;
	char			*first_line;
	char			*last_line;
	unsigned int	last_line_num;
	int				total_lines_saved;
	unsigned char	should_be_read_successfully;
}					asm_file;

typedef struct
{
	char			*filename;
	ssize_t			code_size;
	unsigned char	should_be_read_successfully;
}					bin_file;


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

void			test_asm_files()
{
	asm_file	files[7] = {{FOL "empty.s", NULL, NULL, 0, 0, FALSE},
							{FOL "single_comment.s", " \t# hi!", " \t# hi!", 1, 1, FALSE},
							{FOL "no_new_line.s", ".name \"ABCDE\"", NULL, 0, 4, TRUE},
							{FOL "one_new_line.s", ".name \"ABCDE\"", NULL, 0, 4, TRUE},
							{FOL "ends_with_comment.s", ".name \"ABCDE\"", " ; hi!", 4, 4, TRUE},
							{FOL "only_blank_and_comments.s", "# hi!", "# hi!", 10, 1, FALSE},
							{FOL "ends_with_blank_and_comments.s", ".name \"ABCDE\"", "	  ", 12, 4, TRUE}};
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

		assert(file->last_line->num == files[i].last_line_num);
		assert(count_saved_lines(file) == files[i].total_lines_saved);
		assert(file->is_read_successfully == files[i].should_be_read_successfully);
	}
	ft_printf("OK: asm-file reading\n");
}

void				test_binary_files()
{
	bin_file	files[7] = {{FOL "empty.cor", 0, FALSE},
							{FOL "10_002_bytes_of_champ_code.cor", 10002, TRUE},
							{FOL "100_bytes_of_champ_code.cor", 100, TRUE},
							{FOL "1_byte_header.cor", 0, FALSE},
							{FOL "3_bytes_of_champ_code.cor", 3, TRUE},
							{FOL "incomplete_header.cor", 0, FALSE},
							{FOL "no_champ_code.cor", 0, TRUE}};
	int				fd;
	t_file			*file;

	for (int i = 0; i < 7; i++)
	{
		fd = open(files[i].filename, O_RDONLY);
		file = read_file(fd, files[i].filename);

		assert(file->code_size == files[i].code_size);
		assert(file->is_read_successfully == files[i].should_be_read_successfully);
	}
	ft_printf("OK: binary file reading\n");
}

int				main(void)
{
	test_asm_files();
	test_binary_files();
}
