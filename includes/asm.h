/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 20:56:19 by gloras-t          #+#    #+#             */
/*   Updated: 2019/11/20 18:42:20 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "libft.h"
# include <assert.h>

# define ANNOTATION_OPTION 'a'
# define ANNOTATION_OPTION_CODE 1

# define SOURCE_EXTENSION ".s"
# define BINARY_EXTENSION ".cor"

int			ft_printf(const char *restrict format, ...);

short int	read_options(char *line);

int			is_valid_file(int fd, char *filename);

void		print_error(char *filename, char *message);
void		print_usage(char *program_path);

#endif
