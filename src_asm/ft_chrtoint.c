/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chrtoint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 15:23:49 by dtimeon           #+#    #+#             */
/*   Updated: 2020/06/13 12:32:23 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_chrtoint(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	else if (c >= 'A' && c <= 'Z')
		return (c - 55);
	else if (c >= 'a' && c <= 'z')
		return (c - 87);
	else
		return (0);
}
