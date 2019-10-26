/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gloras-t <gloras-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 21:38:11 by gloras-t          #+#    #+#             */
/*   Updated: 2019/08/03 00:10:53 by gloras-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char		*ft_cut_line(const char *str, char a, char b)
{
	int		start;
	int		end;

	start = ft_strchrind((char*)str, a);
	end = ft_strchrind((char*)str, b);
	if (start <= end)
		return (ft_strsub(str, start, end - start + 1));
	else
		return (NULL);
}

void		ft_set_variables(t_format **data, va_list ap, t_line **line)
{
	*data = ft_init_data(ap);
	*line = ft_init_line();
}

const char	*ft_parse_procces(const char *fmt, t_format *data, va_list ap)
{
	int len;

	fmt++;
	ft_prepare_parse(fmt, data, &len);
	ft_parse(fmt, &len, data, ap);
	ft_transform_type(data);
	if (data->type != '\0')
	{
		ft_parse_format(data, ap);
		if (data->type != '%' && data->type != 'f')
			data->arg_index += 1;
	}
	fmt += len;
	return (fmt);
}

int			ft_parse_color(const char *fmt, t_line **line)
{
	char	*s;
	int		index;
	char	*colors[COLOR_NUMBER];

	if (*fmt == '{')
	{
		s = ft_cut_line(fmt, '{', '}');
		index = ft_get_color_index(s);
		if (index != -1)
		{
			colors[0] = COLOR_RED;
			colors[1] = COLOR_GREEN;
			colors[2] = COLOR_YELLOW;
			colors[3] = COLOR_BLUE;
			colors[4] = COLOR_MAGENTA;
			colors[5] = COLOR_CYAN;
			colors[6] = COLOR_EOC;
			ft_update_line_color(*line, colors[index]);
			free(s);
			return (ft_strlen(s));
		}
	}
	return (0);
}

int			ft_printf(const char *restrict format, ...)
{
	va_list		ap;
	t_format	*data;
	t_line		*line;
	int			n;

	va_start(ap, format);
	ft_set_variables(&data, ap, &line);
	while (*format)
	{
		while ((n = ft_parse_color(format, &line)))
			format += n;
		if (*format && *format != '%')
			ft_update_line_by_char(line, *format++);
		while (*format == '%')
		{
			format = ft_parse_procces(format, data, ap);
			ft_data_output(line, data);
		}
	}
	write(data->fd, line->line, line->length);
	va_end(ap);
	free(data);
	n = line->amount;
	ft_free_line(line);
	return (n);
}
