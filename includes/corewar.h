/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gloras-t <gloras-t@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 21:44:41 by gloras-t          #+#    #+#             */
/*   Updated: 2020/07/01 21:02:59 by gloras-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "libft.h"
# include "op.h"
# include <assert.h>
# include <limits.h>
# include <stdint.h>

# define COR_EXTENSION		".cor"
# define FALSE				0
# define TRUE				1
# define DEBUG				FALSE
# define OFF				-1

# define ARGS_SIZE			3
# define OPS_SIZE			16

# define LOG_LIVES			1
# define LOG_CYCLES			2
# define LOG_OPERATIONS		4
# define LOG_DEATHS			8
# define LOG_MOVEMENTS		16

# define STD_ERROR			2

enum	e_operations {
	OP_LV = 1,
	OP_LD,
	OP_ST,
	OP_ADD,
	OP_SUB,
	OP_AND,
	OP_OR,
	OP_XOR,
	OP_ZJMP,
	OP_LDI,
	OP_STI,
	OP_FORK,
	OP_LLD,
	OP_LLDI,
	OP_LFORK,
	OP_AFF
};

enum	e_errors {
	ERR_SUCCESS,
	ERR_USAGE,
	ERR_NO_COR,
	ERR_FILE_OPEN,
	ERR_SMALL_FILE,
	ERR_LARGE_EXEC_CODE,
	ERR_WRONG_EXEC_CODE,
	ERR_NO_MAGIC,
	ERR_NO_GAP_1,
	ERR_NO_GAP_2,
	ERR_BIG_PL_NBR,
	ERR_NEGATIVE_PL_NBR,
	ERR_TAKEN_PL_NBR,
	ERR_PL_NBRS_SEQUENCE,
	ERR_DUMP
};

typedef struct				s_player
{
	uint32_t				magic;
	uint32_t				prog_size;
	uint8_t					code[CHAMP_MAX_SIZE];
	char					prog_name[PROG_NAME_LENGTH + 1];
	char					comment[COMMENT_LENGTH + 1];
}							t_player;

typedef struct				s_carry
{
	int						id;
	int						carry;
	int						op;
	int						live;
	int						timer;
	int						pos;
	int						jump;
	int32_t					args[ARGS_SIZE];
	int						arg_types[ARGS_SIZE];
	int32_t					r[REG_NUMBER];
	struct s_carry			*next;
}							t_carry;

typedef struct				s_game
{
	int						players_nbr;
	int						dump;
	int						d;
	int						v;
	int						aff;
	int						alive;
	int						cycles;
	int						lives;
	int						cycles_to_die;
	int						cycles_since_last_check;
	int						checkin_nbr;
	int						timers[OPS_SIZE];
	int						args_sizes[OPS_SIZE];
	int						dir_sizes[OPS_SIZE];
	void					*operations[OPS_SIZE];
	t_player				players[MAX_PLAYERS];
	uint8_t					mem[MEM_SIZE];
	t_carry					*carries;
}							t_game;

typedef	void				(*t_handler)(t_game*, t_carry*);
int							ft_printf(const char *restrict format, ...);

/*
** carr_args.c
*/
int							set_carry_args(t_game *game, t_carry *carry);

/*
** carry_check.c
*/
int							check_op_code(int code);
int							check_args_code(t_carry *carry,
							uint8_t op_code, uint8_t args_code);

/*
** clean_utils.c
*/
void						destroy(void *ptr);
void						free_carry_list(t_carry *carry);

/*
** create_player.c
*/
uint32_t					convert_to_ui(uint8_t byte[4]);
int							is_cor_extension(char *file_name);
t_player					create_player(char *file_name);

/*
** init_game.c
*/
void						init_game(t_game *game);

/*
** list_utils.c
*/
t_carry						*new_carry(int nbr, int position);
int							push_carry(t_carry **head, int nbr, int position);
void						del_carry(t_carry **carry, t_carry *needle);

/*
** main_cycle.c
*/
void						main_cycle(t_game *game);

/*
** operations_1.c
*/
void						op_live(t_game *game, t_carry *carry);
void						op_ld(t_game *game, t_carry *carry);
void						op_st(t_game *game, t_carry *carry);
void						op_add(t_game *game, t_carry *carry);

/*
** operations_2.c
*/
void						op_sub(t_game *game, t_carry *carry);
void						op_and(t_game *game, t_carry *carry);
void						op_or(t_game *game, t_carry *carry);
void						op_xor(t_game *game, t_carry *carry);

/*
** operations_3.c
*/
void						op_zjmp(t_game *game, t_carry *carry);
void						op_ldi(t_game *game, t_carry *carry);
void						op_sti(t_game *game, t_carry *carry);
void						op_fork(t_game *game, t_carry *carry);

/*
** operations_4.c
*/
void						op_lld(t_game *game, t_carry *carry);
void						op_lldi(t_game *game, t_carry *carry);
void						op_lfork(t_game *game, t_carry *carry);
void						op_aff(t_game *game, t_carry *carry);

/*
** operations_utils.c
*/
void						write_4_bytes_to_mem(t_game *game,
							int pos, int src);
int32_t						read_4_bytes_from_mem(t_game *game, int pos);
int16_t						read_2_bytes_from_mem(t_game *game, int pos);

/*
** parse_args.c
*/
void						check_players_nbrs(t_game game);
int							is_player_number_correct(int nbr, t_game game);
void						place_players_code(t_game *game, t_carry **carry);
void						parse_args(int argc, char *argv[], t_game *game);

/*
** print_utils_2.c
*/
void						print_usage(char *prog_name);
void						print_error(int error, char *name);
void						print_hexdump(uint8_t *ptr, size_t size);
void						print_carry_list(t_game *game);

/*
** print_utils_1.c
*/
void						introduce_players(t_game game);
void						introduce_winner(t_game game);
void						print_dump_32(t_game *game, size_t size);
void						print_dump_64(t_game *game, size_t size);

/*
** verbose_printing.c
*/
void						print_verbose_movements(t_game *game,
							t_carry *carry);
void						print_verbose_cycle(t_game *game);
void						print_verbose_cycles_to_die(t_game *game);
void						print_verbose_death(t_game *game, t_carry *carry);

#endif
