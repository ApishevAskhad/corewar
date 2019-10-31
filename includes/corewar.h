/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 21:44:41 by gloras-t          #+#    #+#             */
/*   Updated: 2019/10/31 21:51:51 by slindgre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "libft.h"
# include "op.h"
# include <assert.h>

# define COR_EXTENSION		".cor"
# define UI					uint32_t
# define UC					unsigned char
# define DEBUG				1

typedef struct				s_player
{
	UI      			    magic;
	char					prog_name[PROG_NAME_LENGTH + 1];
	UI      			    prog_size;
	char					comment[COMMENT_LENGTH + 1];
	UC						code[CHAMP_MAX_SIZE];
}							t_player;

typedef union 				u_file_cor
{
	UC						file_cor[PROG_NAME_LENGTH + COMMENT_LENGTH + CHAMP_MAX_SIZE + 4 * 4];
	t_player				player;
}							t_file_cor;


int							ft_printf(const char *restrict format, ...);

/*
** print_utils.c
*/
void						print_usage(void);
void						print_error(char *error_msg, char *name);
void						print_bits_ui(UI     number);
void						print_bits_char(char number);
void						print_hexdump(UC *ptr, size_t size);

/*
** check_utils_01.c
*/
int							is_cor_extension(char *file_name);
int							has_header(char *byte);

/*
** clean_utils.c
*/
void    					_free(void *ptr);

/*
** create_player.c
*/
t_player					create_player(char *file_name);

#endif
