/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gloras-t <gloras-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 18:16:56 by slindgre          #+#    #+#             */
/*   Updated: 2019/11/13 22:38:49 by gloras-t         ###   ########.fr       */
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
		print_error("Player number bigger than MAX_PLAYERS:", str);
	else if (nbr < 1)
		print_error("Player number should be real, got:", str);
	else if (game.players[nbr - 1].magic)
		print_error("Player with this number already exists, got:", str);
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
