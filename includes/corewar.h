/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 21:44:41 by gloras-t          #+#    #+#             */
/*   Updated: 2019/10/29 21:37:25 by slindgre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "libft.h"
# include "op.h"
# include <assert.h>

# define COR_EXTENSION		".cor"
# define UI					uint32_t

typedef struct				s_player
{
	UI      			    magic;
	char					prog_name[PROG_NAME_LENGTH + 1];
	UI      			    prog_size;
	char					comment[COMMENT_LENGTH + 1];
	unsigned char			code[CHAMP_MAX_SIZE + 1];
}							t_player;


int							ft_printf(const char *restrict format, ...);

/*
** print_utils.c
*/
void						print_usage(void);
void						print_error(char *error_msg, char *name);
void						print_bits_ui(UI     number);
void						print_bits_char(char number);

/*
** check_utils_01.c
*/
int							is_cor_extension(char *file_name);
int							has_header(char *byte);

/*
** clean_utils.c
*/
void						error_exit(char *error, t_player *layer);
void    					_free(void *ptr);
#endif
