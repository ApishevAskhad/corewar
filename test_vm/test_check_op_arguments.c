/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_check_op_arguments.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 22:17:35 by slindgre          #+#    #+#             */
/*   Updated: 2020/05/15 01:23:02 by slindgre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int in_arr(UC *str, UC arr[58][2])
{
	int i = 0;

	while (i < 58)
	{
		if (str[0] == arr[i][0] && str[1] == arr[i][1])
			return TRUE;
		i++;
	}
	return FALSE;
}

int main()
{
	UC	valid[58][2] = {{1, 0},
				{2, 144}, {2, 208},
				{3, 80}, {3, 112},
				{4, 84},
				{5, 84},
				{6, 84}, {6, 100}, {6, 116}, {6, 148}, {6, 164}, {6, 180}, {6, 212}, {6, 228}, {6, 244},
				{7, 84}, {7, 100}, {7, 116}, {7, 148}, {7, 164}, {7, 180}, {7, 212}, {7, 228}, {7, 244},
				{8, 84}, {8, 100}, {8, 116}, {8, 148}, {8, 164}, {8, 180}, {8, 212}, {8, 228}, {8, 244},
				{9, 0},
				{10, 84}, {10, 100}, {10, 148}, {10, 164}, {10, 212}, {10, 228},
				{11, 84}, {11, 88}, {11, 100}, {11, 104}, {11, 116}, {11, 120},
				{12, 0},
				{13, 144}, {13, 208},
				{14, 84}, {14, 100}, {14, 148}, {14, 164}, {14, 212}, {14, 228},
				{15, 0},
				{16, 64}
				};
	int i = 0;
	int j = 0;
	UC 		*op_args;
	t_carry *carry;

	op_args = (UC*)ft_strnew(2);
	carry = new_carry(1, 0);
	while (i < 256) {
		j = 0;
		while (j < 256) {
			op_args[0] = i;
			op_args[1] = j;
			if (op_args[0] == 1 || op_args[0] == 9 || op_args[0] == 12 || op_args[0] == 15
			|| in_arr(op_args, valid)) {
				if (check_args_code(carry, op_args[0], op_args[1]) == FALSE) {
					ft_printf("{red}KO{eoc} op_code=%08b args_codes=%08b should be valid\n", op_args[0], op_args[1]);
				}
				assert(check_args_code(carry, op_args[0], op_args[1]) == TRUE);
			} else {
				if (check_args_code(carry, op_args[0], op_args[1]) == TRUE) {
					ft_printf("{red}KO{eoc} op_code=%08b args_codes=%08b should be invalid\n", op_args[0], op_args[1]);
				}
				assert(check_args_code(carry, op_args[0], op_args[1]) == FALSE);
			}
			j++;
		}
		i++;
	}
	ft_printf("{green}OK{eoc} {yellow}check_args_code(UC op_code, UC args_code);{eoc}\n", 1);
	return (0);
}