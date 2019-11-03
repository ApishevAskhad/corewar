/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 18:16:56 by slindgre          #+#    #+#             */
/*   Updated: 2019/11/03 22:28:00 by slindgre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		get_free_player_number(t_player *players)
{
	int i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (!players[i].magic)
			return (i + 1);
		i++;
	}
	return (i + 1);
}

void	check_player_number(int nbr, t_game game)
{
	char *str;

	str = ft_itoa(nbr);
	if (nbr > MAX_PLAYERS)
		print_error("Player number bigger than MAX_PLAYERS:", str);
	if (nbr < 1)
		print_error("Player number should be real, got:", str);
	if (game.players[nbr - 1].magic)
		print_error("Player with this number already exists, got:", str);
	free(str);
}

void	parse_args(int argc, char *argv[], t_game *game)
{
	int i;
	int nbr;

	i = 0;
	game->dump = -1;
	while (++i < argc)
	{
		if (!ft_strcmp(argv[i], '-v'))
			game->visual = 1;
		else if (!ft_strcmp(argv[i], '-dump') && i + 1 < argc)
			game->dump = ft_atoi(argv[++i]);
		else
		{
			nbr = get_free_player_number(game->players);
			if (!ft_strcmp(argv[i], '-n') && i + 2 < argc)
			{
				nbr = ft_atoi(argv[++i]);
				i++;
			}
			check_player_number(nbr, *game);
			game->players[nbr - 1] = create_player(argv[i]);
		}
	}
	if (i == 1)
		print_usage();
}
