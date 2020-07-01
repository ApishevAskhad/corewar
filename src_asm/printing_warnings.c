/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_warnings.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 17:31:10 by dtimeon           #+#    #+#             */
/*   Updated: 2020/06/14 20:06:54 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void			print_asm_warning(t_warning *warning, t_file *file)
{
	size_t		offset;
	size_t		line_num;
	char		*pos;
	size_t		tabs_num;
	size_t		i;

	(void)file;
	if (warning->line && warning->line->initial_str)
	{
		line_num = warning->line->num;
		offset = ft_printf("     line {green}%u{eoc}: ", line_num);
		pos = warning->asm_pos;
		if (pos)
			offset += pos - warning->line->initial_str;
		else
			offset += ft_strlen(warning->line->initial_str);
		ft_printf("{blue}%s{eoc}\n", warning->line->initial_str);
		tabs_num = count_tabs(warning->line->initial_str, pos);
		offset -= (tabs_num ? (int)(tabs_num + 4) : (int)-1);
		i = 0;
		while (i++ < tabs_num)
			ft_printf("%c", '\t');
		ft_printf("{green}% *s{eoc}\n", offset, "^");
	}
	ft_printf("\t{green}%s{eoc}\n\n", warning->message);
}

void			print_bin_warning(t_warning *warning, t_file *file)
{
	ssize_t	pos;

	pos = warning->bin_pos;
	if (pos >= 0)
		ft_printf("     Byte %lli: | {green}%08hhB{eoc} | <-- ", pos,
					*(file->champ_code + pos));
	ft_printf("{green}%s{eoc}\n\n", warning->message);
}

void			print_warnings(t_file *file)
{
	void		(*print_func)(t_warning *, t_file *);
	t_warning	*cur_warning;

	print_func = (file->is_assembly ? print_asm_warning : print_bin_warning);
	cur_warning = file->first_warning;
	if (file->first_warning)
		ft_printf("Warnings for file {blue}%s{eoc}:\n", file->filename);
	else
		ft_printf("No warnings for file {blue}%s{eoc}\n", file->filename);
	while (cur_warning)
	{
		print_func(cur_warning, file);
		if (cur_warning->is_needed_to_free_message)
		{
			ft_strdel(&cur_warning->message);
			cur_warning->is_needed_to_free_message = FALSE;
		}
		cur_warning = cur_warning->next;
	}
}
