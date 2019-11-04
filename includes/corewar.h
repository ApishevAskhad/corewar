/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 21:44:41 by gloras-t          #+#    #+#             */
/*   Updated: 2019/11/04 19:51:24 by slindgre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "libft.h"
# include "op.h"
# include <assert.h>

# define COR_EXTENSION		".cor"
# define UI					uint32_t
# define UC					unsigned char
# define DEBUG				1

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
void						print_dump(UC *ptr, size_t size);

/*
** check_utils_01.c
*/
int							is_cor_extension(char *file_name);
int							has_header(char *byte);
void    					check_players_nbrs(t_game game);

/*
** clean_utils.c
*/
void						_free(void *ptr);

/*
** create_player.c
*/
t_player					create_player(int fd, char *file_name);
int							check_file(char *file_name);

/*
** init_game.c
*/
void						init_game(t_game *game);

/*
** place_players.c
*/
void    					place_players_code(t_game *game);

#endif
