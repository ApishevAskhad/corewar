/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gloras-t <gloras-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 21:44:41 by gloras-t          #+#    #+#             */
/*   Updated: 2019/11/14 22:49:16 by gloras-t         ###   ########.fr       */
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
# define DEBUG				1
# define OFF				-1
# define MIN_FILE_SIZE		4 * 4 + PROG_NAME_LENGTH + COMMENT_LENGTH

typedef struct				s_player
{
	UI						magic;
	UI						prog_size;
	UC						code[CHAMP_MAX_SIZE];
	char					prog_name[PROG_NAME_LENGTH + 1];
	char					comment[COMMENT_LENGTH + 1];
}							t_player;

typedef struct				s_game
{
	int						players_nbr;
	int						dump;
	int						visual;
	int						alive;
	int						cycles;
	int						lives;
	int						cycle_to_die;
	int						checkin_nbr;
	t_player				players[MAX_PLAYERS];
	UC						mem[MEM_SIZE];
}							t_game;

typedef struct				s_carry
{
	int						nbr;
	int						carry;
	int						op;
	int						live;
	int						timer;
	int						pos;
	int						jump;
	int						r[REG_NUMBER];
	struct s_carry			*next;
}							t_carry;

int							ft_printf(const char *restrict format, ...);

/*
** print_utils.c
*/
void						print_usage(void);
void						print_error(char *error_msg, char *name);
void						print_bits_ui(UI number);
void						print_bits_char(char number);
void						print_hexdump(UC *ptr, size_t size);
void						print_catty_list(t_carry *head);

/*
** check_utils_01.c
*/
int							is_cor_extension(char *file_name);
void    					check_players_nbrs(t_game game);

/*
** list_utils.c
*/
t_carry						*new_carry(int nbr);
int							push_carry(t_carry **head, int nbr);
t_carry 					*del_carry(t_carry *carry, int nbr);

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
** place_players.c
*/
void    					place_players_code(t_game *game);

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
void    					introduce_players(t_game game);

/*
** place_players.c
*/
void    					place_players_code(t_game *game);

void						parse_args(int argc, char *argv[], t_game *game);
int							get_free_player_number(t_player *players);
int							is_player_number_correct(int nbr, t_game game);

#endif
