/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gloras-t <gloras-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 21:44:41 by gloras-t          #+#    #+#             */
/*   Updated: 2019/11/12 21:46:01 by gloras-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "libft.h"
# include "op.h"
# include <assert.h>
# include <limits.h>

# define COR_EXTENSION		".cor"
# define UI					uint32_t
# define UC					unsigned char
# define DEBUG				0
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
	t_player				players[MAX_PLAYERS];
	int						players_nbr;
	UC						mem[MEM_SIZE];
	int						dump;
	int						visual;
}							t_game;

int							ft_printf(const char *restrict format, ...);

/*
** print_utils.c
*/
void						print_usage(void);
void						print_error(char *error_msg, char *name);
void						print_bits_ui(UI number);
void						print_bits_char(char number);
void						print_hexdump(UC *ptr, size_t size);

/*
** check_utils_01.c
*/
int							is_cor_extension(char *file_name);

/*
** clean_utils.c
*/
void						destroy(void *ptr);

/*
** create_player.c
*/
t_player					create_player(char *file_name);

/*
**	utils_01.c
*/
UI							convert_to_ui(UC byte[4]);

/*
** init_game.c
*/
void						init_game(t_game *game);

/*
** place_players.c
*/
void    					place_players_code(t_game *game);
#endif
