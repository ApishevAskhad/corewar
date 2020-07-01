/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_data.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 14:46:30 by dtimeon           #+#    #+#             */
/*   Updated: 2020/05/29 14:47:05 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_op	g_op_tab[OP_NUM] =
{
	{"live", 4, 1, {T_DIR}, 1, "alive", 0, 0},
	{"ld", 2, 2, {T_DIR | T_IND, T_REG}, 2, "load", 1, 0},
	{"st", 2, 2, {T_REG, T_IND | T_REG}, 3, "store", 1, 0},
	{"add", 3, 3, {T_REG, T_REG, T_REG}, 4, "addition", 1, 0},
	{"sub", 3, 3, {T_REG, T_REG, T_REG}, 5, "substruction", 1, 0},
	{"and", 3, 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6,
		"and", 1, 0},
	{"or", 2, 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7,
		"or", 1, 0},
	{"xor", 3, 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8,
		"xor", 1, 0},
	{"zjmp", 4, 1, {T_DIR}, 9, "jump if zero", 0, 1},
	{"ldi", 3, 3, {T_REG | T_IND | T_DIR, T_REG | T_DIR, T_REG}, 10,
		"load index", 1, 1},
	{"sti", 3, 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11,
		"store index", 1, 1},
	{"fork", 4, 1, {T_DIR}, 12, "fork", 0, 1},
	{"lld", 3, 2, {T_DIR | T_IND, T_REG}, 13, "long load", 1, 0},
	{"lldi", 4, 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14,
		"long load index", 1, 1},
	{"lfork", 5, 1, {T_DIR}, 15, "long fork", 0, 1},
	{"aff", 3, 1, {T_REG}, 16, "aff", 1, 0}
};
