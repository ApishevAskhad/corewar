/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 20:56:19 by gloras-t          #+#    #+#             */
/*   Updated: 2020/05/07 20:35:19 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "libft.h"
# include <assert.h>

# define ANNOTATION_OPTION		'a'
# define ANNOTATION_OPTION_CODE	1

# define SOURCE_EXTENSION		".s"
# define BINARY_EXTENSION		".cor"


typedef struct					s_op
{
	char						*name;
	unsigned char				number_of_args;
	unsigned char				arg_types[3];
	unsigned char				op_code;
	char						*description;
	unsigned char				has_arg_type_code;
	unsigned char				has_short_dir_arg;
}								t_op;

typedef struct					s_arg
{
	unsigned char				type;
	unsigned char				code;
	int							value;
}								t_arg;

typedef struct					s_line
{
	char						*initial_str;
	t_op						*op_data;
	t_arg						args[3];
	int							pos;
	int							len;
	struct s_line				*next;
}								t_line;

typedef struct					s_error_data
{
	t_line						*line;
	int							error_pos;
	char						*message;
}								t_error_data;

typedef struct					s_label
{
	char						*name;
	int							pos;
	unsigned char				is_found;
	struct s_label				*next;
}								t_label;

typedef struct					s_file
{
	int							fd;
	char						*filename;
	t_line						*first_line;
	t_line						*code_start_line;
	unsigned char				is_assembly;
	char						*champ_name;
	char						*champ_comment;
	unsigned char				is_correct;
	t_label						*labels;
}								t_file;



int			ft_printf(const char *restrict format, ...);

short int	read_options(char *line);

int			is_valid_file(int fd, char *filename);

void		print_error(char *filename, char *message);
void		print_usage(char *program_path);

#endif
