/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_is_cor_extension.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gloras-t <gloras-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 00:45:44 by gloras-t          #+#    #+#             */
/*   Updated: 2019/11/03 17:48:14 by gloras-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int	main()
{
	assert(!is_cor_extension("cor"));
	assert(is_cor_extension("42.cor"));
	assert(is_cor_extension("a.cor"));
	assert(!is_cor_extension(""));
	assert(is_cor_extension(".cor"));
	assert(is_cor_extension("file.cor"));
	assert(!is_cor_extension(".co"));
	assert(!is_cor_extension(".c"));
	assert(!is_cor_extension("a.cor "));
	assert(!is_cor_extension("a.core"));
	assert(!is_cor_extension("cor."));
	assert(!is_cor_extension("roc."));
	assert(is_cor_extension(" .cor"));
	ft_printf("{green}OK{eoc} {yellow}is_cor_extension(char *file_name);{eoc}\n");
	return (0);
}
