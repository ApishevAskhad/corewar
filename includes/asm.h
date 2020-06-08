/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 20:56:19 by gloras-t          #+#    #+#             */
/*   Updated: 2020/06/08 13:46:10 by dtimeon          ###   ########.fr       */
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

# define STRING_START			"\""
# define STRING_END				"\""

# define TRUE 					1
# define FALSE 					0

# define NAME					1
# define COMMENT				2

# define OP_NUM					16

# define REG_CHAR				'r'

# define REG_CODE_SIZE			1
# define IND_CODE_SIZE			2
# define DIR_AS_IND_CODE_SIZE	2
# define DIR_AS_DATA_CODE_SIZE	4

# define REG_STR				"registry"
# define DIR_STR				"direct"
# define IND_STR				"indirect"

# define REG_SYM				"r"
# define DIR_SYM				"%"
# define IND_SYM				""

# define TYPES_STRINGS			{ REG_STR, DIR_STR, IND_STR }

# define TAB_LEN				4


typedef unsigned int			t_magic;
typedef unsigned int			t_sep;
typedef unsigned int			t_prog_size;

typedef struct					s_op
{
	char						*name;
	unsigned int				name_len;
	unsigned char				number_of_args;
	unsigned char				arg_types[3];
	unsigned char				op_code;
	char						*description;
	unsigned char				has_arg_type_code;
	unsigned char				has_dir_as_ind;
}								t_op;

typedef struct					s_arg
{
	unsigned char				type;
	unsigned char				code;
	int							value;
	int							value_len;
	char						*str_value;
	unsigned char				size;
	unsigned char				has_value_from_label;
	char						*label_name;
	size_t						label_name_len;
	size_t						pos;
	char						*sym;
}								t_arg;

typedef struct					s_label
{
	char						*name;
	size_t						name_len;
	struct s_line				*op_line;
	struct s_label				*next;
	size_t						pos;
}								t_label;

typedef struct					s_line
{
	char						*initial_str;
	size_t						num;
	t_op						*op_data;
	t_arg						args[3];
	size_t						pos;
	unsigned short int			len;
	unsigned char				has_label_in;
	t_label						*label;
	unsigned char				has_label_to_find;
	size_t						op_pos;
	unsigned char				arg_types_code;
	struct s_line				*next;
}								t_line;

typedef struct					s_error_data
{
	t_line						*line;
	size_t						error_pos;
	char						*message;
	unsigned char				is_needed_to_free_message;
}								t_error_data;

typedef struct					s_file
{
	int							fd;
	char						*filename;
	t_line						*first_line;
	t_line						*last_line;
	t_line						*first_code_line;
	unsigned char				is_assembly;
	char						*champ_name;
	char						*champ_comment;
	unsigned char				*binary_header;
	unsigned char				*champ_code;
	t_label						*labels;
	size_t						code_size;
	unsigned char				is_read_successfully;
	unsigned char				is_correct;
	t_error_data				*error_data;
}								t_file;


int								ft_printf(const char *restrict format, ...);

t_line							*init_line();
t_label							*init_label(char *label_name, char *filename);
t_error_data					*init_error_data(char *filename);
t_file							*init_file(int fd, char *filename);

short int						read_options(char *line);

int								is_valid_file(int fd, char *filename);

char							*find_first_non_space_char(char *str);
unsigned char					is_blank_str(char *str);
unsigned char					is_comment(char *str);
char							*join_with_line_break(char *first_str,
														char *second_str);
int								count_tabs(char *str);

t_file							*read_file(int fd, char *filename);

void							read_binary_champ_code(t_file *file,
														ssize_t header_size);

void							parse_file(t_file *file);

void							parse_binary_header(t_file *file);

void							parse_binary_code(t_file *file);

size_t							parse_bin_args(unsigned char *bin_data,
										t_line *line, size_t pos, t_file *file);

void							parse_asm_header(t_file *file);

void							check_start_of_string(t_file *file,
									t_line **c_line, char *s, unsigned char d);

void							parse_asm_code(t_file *file);

void							parse_labels(t_file *file, t_line **cur_line,
											char **start_pos, char *label_name);

unsigned short int				calc_op_size(t_line *line);
void							parse_asm_op(t_file *file, t_line *cur_line,
												char **start_pos);

void							save_op_data(char **str, t_line *line);
t_op							*get_op(char **str);

void							assign_arg_as(unsigned char type, t_arg *arg,
										  		unsigned char is_dir_ind);
void							parse_asm_arg(char **str, t_line *line, int i,
												t_file *file);

void							replace_label_args(t_file *file);

char							*find_label(char **code_str, t_file *file,
											t_line *line);
void							skip_non_useful_lines(t_line **line);
unsigned char					is_name_cmd(char *start_pos);
unsigned char					is_comment_cmd(char *start_pos);

void							translate_file(t_file *file, short int options);

void							fill_arg_types_codes(t_line *line);
char							*ft_strndup(const char *src, size_t n);
size_t							to_big_endian(size_t le_num, unsigned int size);

void							print_annotated_file(t_file *file);
void							print_error(char *filename, char *message);
void							print_usage(char *program_path);
void							print_file_parsing_error(t_file *file);

void							delete_labels(t_label **labels);
void							delete_file(t_file **file);

char							*make_type_error_message(t_line *line, int i,
														char *filename);
void							fill_error(t_file *file, t_line *line,
											ssize_t pos, char *message);

void							exit_with_allocation_error(char *filename);

#endif
