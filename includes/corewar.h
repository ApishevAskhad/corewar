/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 21:44:41 by gloras-t          #+#    #+#             */
/*   Updated: 2020/05/16 01:53:27 by slindgre         ###   ########.fr       */
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
# define UI					uint32_t
# define UC					unsigned char
# define DEBUG				0
# define OFF				-1
# define MIN_FILE_SIZE		4 * 4 + PROG_NAME_LENGTH + COMMENT_LENGTH
# define TRUE				1
# define FALSE				0

# define ARGS_SIZE			3
# define OPS_SIZE			16

enum e_operations {
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

enum e_errors {
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
	UI						magic;
	UI						prog_size;
	UC						code[CHAMP_MAX_SIZE];
	char					prog_name[PROG_NAME_LENGTH + 1];
	char					comment[COMMENT_LENGTH + 1];
}							t_player;

typedef struct				s_carry
{
	int						carry;
	int						op;
	int						live;
	int						timer;
	int						pos;
	int						jump;
	int						args[ARGS_SIZE];
	int						arg_types[ARGS_SIZE];
	int						r[REG_NUMBER];
	struct s_carry			*next;
}							t_carry;

typedef struct				s_game
{
	int						players_nbr;
	int						dump;
	int						d;
	int						aff;
	int						visual;
	int						alive;
	int						cycles;
	int						lives;
	int						cycle_to_die;
	int						checkin_nbr;
	int						timers[OPS_SIZE];
	int						args_sizes[OPS_SIZE];
	int						dir_sizes[OPS_SIZE];
	void					*operations[OPS_SIZE];
	t_player				players[MAX_PLAYERS];
	UC						mem[MEM_SIZE];
	t_carry					*carries;
}							t_game;

typedef	void				(*t_handler)(t_game*, t_carry*);

int							ft_printf(const char *restrict format, ...);

/*
** print_utils.c
*/
void						print_usage(void);
void						print_error(int error, char *name);
void						print_bits_ui(UI number);
void						print_bits_char(char number);
void						print_dump(UC *ptr, size_t size);
void						print_hexdump(UC *ptr, size_t size);
void						print_carry_list(t_carry *head);
void						print_dump_canon(UC *ptr, size_t size);

/*
** check_utils_01.c
*/
int							is_cor_extension(char *file_name);
void						check_players_nbrs(t_game game);

/*
** list_utils.c
*/
t_carry						*new_carry(int nbr, int position);
int							push_carry(t_carry **head, int nbr, int position);
t_carry 					*del_carry(t_carry *carry, t_carry *needle);

/*
** clean_utils.c
*/
void						destroy(void *ptr);

/*
** create_player.c
*/
t_player					create_player(char *file_name);
int							check_file(char *file_name);

/*
** init_game.c
*/
void						init_game(t_game *game);


/*
** utils_01.c
*/
UI							convert_to_ui(UC byte[4]);

/*
** init_game.c
*/
void						init_game(t_game *game);

/*
** introduce_player.c
*/
void						introduce_players(t_game game);
void						introduce_winner(t_game game);

/*
** place_players.c
*/
void    					place_players_code(t_game *game, t_carry **carry);

/*
** parse_args.c
*/
void						parse_args(int argc, char *argv[], t_game *game);
int							get_free_player_number(t_player *players);
int							is_player_number_correct(int nbr, t_game game);

/*
** carry_utils.c
*/
int							check_args_code(t_carry *carry, UC op_code, UC args_code);
int							check_op_code(int code);
int							set_carry_args(t_game *game, t_carry *carry);

/*
** main_cycle.c
*/
void						main_cycle(t_game *game);

/*
** operations_utils.c
*/
void						write_4bytes_to_mem(t_game *game, int pos, int src);
int							read_n_bytes_from_mem(t_game *game, int pos, int n);
int							read_2_bytes_from_mem(t_game *game, int pos);

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

#endif
