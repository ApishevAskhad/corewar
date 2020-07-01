/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 18:16:56 by slindgre          #+#    #+#             */
/*   Updated: 2020/05/19 01:40:20 by slindgre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		check_players_nbrs(t_game game)
{
	int i;

	i = 0;
	while (i < game.players_nbr)
	{
		if (!game.players[i].magic)
			print_error(ERR_PL_NBRS_SEQUENCE, ft_itoa(i + 1));
		i++;
	}
}

int			is_player_number_correct(int nbr, t_game game)
{
	char	*str;
	int		no_error;

	str = ft_itoa(nbr);
	no_error = 0;
	if (nbr > MAX_PLAYERS)
		print_error(ERR_BIG_PL_NBR, str);
	else if (nbr < 1)
		print_error(ERR_NEGATIVE_PL_NBR, str);
	else if (game.players[nbr - 1].magic)
		print_error(ERR_TAKEN_PL_NBR, str);
	else
		no_error = 1;
	free(str);
	return (no_error);
}

static void	set_player(t_game *game, int argc, char *argv[], int *i)
{
	int	nbr;

	assert(game->players != NULL);
	nbr = 1;
	while (game->players[nbr - 1].magic && nbr <= MAX_PLAYERS)
	{
		nbr++;
	}
	if (!ft_strcmp(argv[*i], "-n") && *i + 2 < argc)
	{
		nbr = ft_atoi(argv[++(*i)]);
		*i += 1;
	}
	if (is_player_number_correct(nbr, *game))
		game->players[nbr - 1] = create_player(argv[*i]);
	game->players_nbr += 1;
}

void		place_players_code(t_game *game, t_carry **carry)
{
	int				i;
	int				n;
	unsigned char	*start;

	assert(game != NULL);
	i = 0;
	n = game->players_nbr;
	while (i < n)
	{
		start = game->mem + i * MEM_SIZE / n;
		ft_memcpy(start, game->players[i].code, CHAMP_MAX_SIZE);
		push_carry(carry, -i - 1, i * MEM_SIZE / n);
		i++;
	}
}

void		parse_args(int argc, char *argv[], t_game *game)
{
	int i;

	assert(game != NULL);
	i = 0;
	while (++i < argc)
	{
		if (!ft_strcmp(argv[i], "-dump") && i + 1 < argc)
			game->dump = ft_atoi(argv[++i]);
		else if (!ft_strcmp(argv[i], "-d") && i + 1 < argc)
			game->d = ft_atoi(argv[++i]);
		else if (!ft_strcmp(argv[i], "-a"))
			game->aff = TRUE;
		else if (!ft_strcmp(argv[i], "-v") && i + 1 < argc)
			game->v = ft_atoi(argv[++i]);
		else
			set_player(game, argc, argv, &i);
	}
	if (game->players_nbr == 0)
		print_usage(argv[0]);
	check_players_nbrs(*game);
}
