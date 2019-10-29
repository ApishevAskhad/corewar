/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 21:44:41 by gloras-t          #+#    #+#             */
/*   Updated: 2019/10/29 16:18:55 by slindgre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "libft/libft.h"
# include "op.h"
# include <assert.h>

# define COR_EXTENSION		".cor"
# define UI					unsigned int

int							ft_printf(const char *restrict format, ...);

/*
** print_utils.c
*/
void						print_usage(void);
void						print_error(char *error_msg);
void						print_bits_ui(UI number);
void						print_bits_char(char number);

/*
** check_utils_01.c
*/
int							is_cor_extension(char *file_name);
int							has_header(char *byte);

#endif
