/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 18:16:56 by slindgre          #+#    #+#             */
/*   Updated: 2019/11/16 23:48:56 by slindgre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		get_free_player_number(t_player *players)
{
	assert(players != NULL);
	int i;

	i = 0;
	while (players[i++].magic && i <= MAX_PLAYERS)
		;
	return (i);
}

int		is_player_number_correct(int nbr, t_game game)
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

void	set_player(t_game *game, int argc, char *argv[], int *i)
{
	int	nbr;

	nbr = get_free_player_number(game->players);
	if (!ft_strcmp(argv[*i], "-n") && *i + 2 < argc)
	{
		nbr = ft_atoi(argv[++(*i)]);
		*i += 1;
	}
	if (is_player_number_correct(nbr, *game))
		game->players[nbr - 1] = create_player(argv[*i]);
	game->players_nbr += 1;
}

void	parse_args(int argc, char *argv[], t_game *game)
{
	assert(game != NULL);
	int i;

	i = 0;
	while (++i < argc)
	{
		if (!ft_strcmp(argv[i], "-v"))
			game->visual = 1;
		else if (!ft_strcmp(argv[i], "-dump") && i + 1 < argc)
			game->dump = ft_atoi(argv[++i]);
		else
			set_player(game, argc, argv, &i);
	}
	if (game->players_nbr == 0)
		print_usage();
}
