/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_file_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 08:52:51 by dtimeon           #+#    #+#             */
/*   Updated: 2020/05/28 08:56:51 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

#define FOL "./test_asm/assets/file_parsing/"
#define FOL_INC "./test_asm/assets/file_parsing/incorrect/"

typedef struct
{
	char				*filename;
	char				*bin_filename;
}						correct_asm_file;

unsigned int			convert_to_le(unsigned int src)
{
	unsigned int		dst;

	for (int i = 0; i < 4; i++)
	{
		((unsigned char *)&dst)[i] = ((unsigned char *)&src)[4 - 1 - i];
	}
	return (dst);
}

void					test_correct_asm_files(int do_print_details)
{
	correct_asm_file	files[19] =
	{{FOL "only_label.s", FOL "only_label.cor"},
	{FOL "negative_arg_values.s", FOL "negative_arg_values.cor"},
	{FOL "random_spaces.s", FOL "random_spaces.cor"},
	{FOL "minimum_spaces.s", FOL "minimum_spaces.cor"},
	{FOL "repeating_labels.s", FOL "repeating_labels.cor"},
	{FOL "empty_name_and_comment.s", FOL "empty_name_and_comment.cor"},
	{FOL "all_ops.s", FOL "all_ops.cor"},
	{FOL "multiline_name_and_comment.s", FOL "multiline_name_and_comment.cor"},
	{FOL "42.s", FOL "42.cor",},
	{FOL "barriere.s", FOL "barriere.cor"}, 
	{FOL "Car.s", FOL "Car.cor"},
	{FOL "ex.s", FOL "ex.cor"},
	{FOL "Gagnant.s", FOL "Gagnant.cor"},
	{FOL "jumper.s", FOL "jumper.cor"},
	{FOL "maxidef.s", FOL "maxidef.cor"},
	{FOL "mortel.s", FOL "mortel.cor"},
	{FOL "Octobre_Rouge_V4.2.s", FOL "Octobre_Rouge_V4.2.cor"},
	{FOL "slider2.s", FOL "slider2.cor"},
	{FOL "toto.s", FOL "toto.cor"}};

	t_file				*file;
	int					fd;
	int					bin_fd;
	unsigned int		bin_code_size;
	char				*bin_name;
	char				*bin_comment;

	for(int i = 0; i < 19; i++)
	{
		fd = open(files[i].filename, O_RDONLY);
		bin_fd = open(files[i].bin_filename, O_RDONLY);
		bin_name = ft_strnew(PROG_NAME_LENGTH);
		bin_comment = ft_strnew(COMMENT_LENGTH);
		lseek(bin_fd, 4, SEEK_SET);
		read(bin_fd, bin_name, PROG_NAME_LENGTH);
		lseek(bin_fd, 4, SEEK_CUR);
		read(bin_fd, (void *)&bin_code_size, 4);
		read(bin_fd, bin_comment, COMMENT_LENGTH);
		bin_code_size = convert_to_le(bin_code_size);

		file = read_file(fd, files[i].filename);
		parse_file(file);

		if (do_print_details)
		{
			ft_printf("name: '%s' '%s'\n", file->champ_name, bin_name);
			ft_printf("comm: '%s' '%s'\n", file->champ_comment, bin_comment);
			ft_printf("code: '%u' '%u'\n\n", (unsigned int)file->code_size, bin_code_size);
		}
		
		assert(file->is_correct);
		assert(ft_strequ(file->champ_name, bin_name));
		assert(ft_strequ(file->champ_comment, bin_comment));
		assert(file->code_size == bin_code_size);
		ft_strdel(&bin_name);
		ft_strdel(&bin_comment);
		delete_file(&file);
	}
}

void					test_incorrect_asm_files(int do_print_details)
{
	char				*files[32] = {FOL_INC "big_value_reg.s", 
									FOL_INC "incorrect_args_set_1_arg.s", 
									FOL_INC "incorrect_args_set_2_args.s", 
									FOL_INC "incorrect_args_set_3_args.s", 
									FOL_INC "incorrect_arg_value_dir.s", 
									FOL_INC "incorrect_arg_value_indirect.s", 
									FOL_INC "incorrect_label.s", 
									FOL_INC "incorrect_op_1.s", 
									FOL_INC "incorrect_op_2.s", 
									FOL_INC "incorrect_value_reg.s", 
									FOL_INC "label_as_reg_value.s", 
									FOL_INC "negative_value_reg.s", 
									FOL_INC "no_arg_label_name.s", 
									FOL_INC "no_comment.s", 
									FOL_INC "no_label_name_before_label_char.s", 
									FOL_INC "no_line_break_after_label.s", 
									FOL_INC "no_line_break_after_op.s", 
									FOL_INC "no_name.s",
									FOL_INC "no_name_cmd.s",
									FOL_INC "no_op.s", 
									FOL_INC "no_separator.s", 
									FOL_INC "not_enough_args_and_spaces.s", 
									FOL_INC "not_enough_args.s", 
									FOL_INC "no_value_dir.s", 
									FOL_INC "no_value_ind.s", 
									FOL_INC "no_value_reg.s", 
									FOL_INC "op_and_line_break.s", 
									FOL_INC "op_space_and_line_break.s", 
									FOL_INC "unexisting_label_arg_dir.s", 
									FOL_INC "unexisting_label_arg_ind.s", 
									FOL_INC "very_long_comment.s", 
									FOL_INC "very_long_name.s"};
	
	t_file				*file;
	int					fd;

	for (int i = 0; i < 32; i++)
	{
		fd = open(files[i], O_RDONLY);
		file = read_file(fd, files[i]);
		parse_file(file);
		if (do_print_details)
		{
			ft_printf("\nOpened file %i %s\n", i, files[i]);
			ft_putendl(file->error_data->message);
		}
		assert(file->is_correct == FALSE);
		if (file->error_data->is_needed_to_free_message)
			ft_strdel(&(file->error_data->message));
		delete_file(&file);
	}
}


int		main(int ac, char **av)
{
	int	do_print_details = 0;

	if (ac == 2 && ft_strequ(av[1], "-d"))
		do_print_details = 1;
	test_correct_asm_files(do_print_details);
	test_incorrect_asm_files(do_print_details);
	ft_printf("OK: asm parsing\n");
}
