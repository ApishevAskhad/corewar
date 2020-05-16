/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 20:56:19 by gloras-t          #+#    #+#             */
/*   Updated: 2020/05/16 05:10:40 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "libft.h"
# include "op.h"
# include <assert.h>

# define ANNOTATION_OPTION		'a'
# define ANNOTATION_OPTION_CODE	1

# define SOURCE_EXTENSION		".s"
# define BINARY_EXTENSION		".cor"

# define COMMENT_CHAR_2         ';'


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
	unsigned int				num;
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
	t_line						*op_line;
	struct s_label				*next;
}								t_label;

typedef struct					s_file
{
	int							fd;
	char						*filename;
	t_line						*first_line;
	t_line						*last_line;
	unsigned char				is_assembly;
	char						*champ_name;
	char						*champ_comment;
	unsigned char				*champ_code;
	t_label						*labels;
	int							code_size;
	unsigned char				is_read_successfully;
	unsigned char				is_correct;
	t_error_data				*error_data;
}								t_file;


int								ft_printf(const char *restrict format, ...);

t_line							*init_line();
t_file							*init_file(int fd, char *filename);

short int						read_options(char *line);

int								is_valid_file(int fd, char *filename);

unsigned char					is_not_blank_str(char *str);
unsigned char					is_not_comment(char *str);

t_file							*read_file(int fd, char *filename);

void							parse_file(t_file *file);

void							translate_file(t_file *file, short int options);

void							print_error(char *filename, char *message);
void							print_usage(char *program_path);
void							print_file_validation_error(t_file *file);

void							delete_file(t_file **file);

void							exit_with_allocation_error(char *filename);

#endif
