/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parse_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 23:39:17 by slindgre          #+#    #+#             */
/*   Updated: 2019/11/13 02:50:45 by slindgre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
* DEBUG	constant should be 1 to run tests
*/

int main()
{
	t_game	game;
	int		ac;
	char 	**av;
	char 	*str;
	char	c = ' ';

	ft_printf("%s:\n", "No arguments");
	str = "./corewar";
	ft_bzero(&game, sizeof(t_game));
	game.dump = -1;
	ac = ft_count_words(str, c);
	av = ft_strsplit(str, c);
	parse_args(ac, av, &game);
	assert(game.players_nbr == 0);
	assert(game.players[0].magic == 0);
	assert(game.players[1].magic == 0);
	assert(game.players[2].magic == 0);
	assert(game.players[3].magic == 0);
	ft_printf("{green}OK{eoc}\n\n");

	ft_printf("%s:\n", "Invalid champ file");
	str = "./corewar invalid_file";
	ft_bzero(&game, sizeof(t_game));
	game.dump = -1;
	ac = ft_count_words(str, c);
	av = ft_strsplit(str, c);
	parse_args(ac, av, &game);
	assert(game.players[0].magic == 0);
	assert(game.players[1].magic == 0);
	assert(game.players[2].magic == 0);
	assert(game.players[3].magic == 0);
	ft_printf("{green}OK{eoc}\n\n");

	str = "./corewar -dump";
	ft_printf("%s:\n", str);
	ft_bzero(&game, sizeof(t_game));
	game.dump = -1;
	ac = ft_count_words(str, c);
	av = ft_strsplit(str, c);
	parse_args(ac, av, &game);
	ft_printf("{green}OK{eoc}\n\n");

	str = "./corewar -v";
	ft_printf("%s:\n", str);
	ac = ft_count_words(str, c);
	av = ft_strsplit(str, c);
	parse_args(ac, av, &game);
	assert(game.visual == 1);
	ft_printf("{green}OK{eoc}\n\n");

	str = "./corewar -dump 10";
	ft_printf("%s:\n", str);
	ac = ft_count_words(str, c);
	av = ft_strsplit(str, c);
	parse_args(ac, av, &game);
	assert(game.dump == 10);
	ft_printf("{green}OK{eoc}\n\n");

	str = "./corewar -dump 0";
	ft_printf("%s:\n", str);
	ac = ft_count_words(str, c);
	game.dump = -1;
	av = ft_strsplit(str, c);
	parse_args(ac, av, &game);
	assert(game.dump == 0);
	ft_printf("{green}OK{eoc}\n\n");

	str = "./corewar -dump -10";
	ft_printf("%s:\n", str);
	ac = ft_count_words(str, c);
	game.dump = -1;
	av = ft_strsplit(str, c);
	parse_args(ac, av, &game);
	assert(game.dump == -10);
	ft_printf("{green}OK{eoc}\n\n");

	str = "./corewar -v -dump 10";
	ft_printf("%s:\n", str);
	ac = ft_count_words(str, c);
	game.dump = -1;
	av = ft_strsplit(str, c);
	parse_args(ac, av, &game);
	assert(game.visual == 1);
	assert(game.dump == 10);
	ft_printf("{green}OK{eoc}\n\n");

	str = "./corewar -v -dump 20 invalid_file";
	ft_printf("%s:\n", str);
	ac = ft_count_words(str, c);
	game.dump = -1;
	av = ft_strsplit(str, c);
	parse_args(ac, av, &game);
	assert(game.visual == 1);
	assert(game.dump == 20);
	ft_printf("{green}OK{eoc}\n\n");

	str = "./corewar resources/champs/Gagnant.cor";
	ft_printf("%s:\n", str);
	ac = ft_count_words(str, c);
	ft_bzero(&game, sizeof(t_game));
	av = ft_strsplit(str, c);
	parse_args(ac, av, &game);
	assert(game.players_nbr == 1);
	assert(game.players[0].magic == COREWAR_EXEC_MAGIC);
	assert(game.players[1].magic == 0);
	assert(game.players[2].magic == 0);
	assert(game.players[3].magic == 0);
	ft_printf("{green}OK{eoc}\n\n");

	str = "./corewar resources/champs/Gagnant.cor resources/champs/Gagnant.cor";
	ft_printf("%s:\n", str);
	ac = ft_count_words(str, c);
	ft_bzero(&game, sizeof(t_game));
	av = ft_strsplit(str, c);
	parse_args(ac, av, &game);
	assert(game.players_nbr == 2);
	assert(game.players[0].magic == COREWAR_EXEC_MAGIC);
	assert(game.players[1].magic == COREWAR_EXEC_MAGIC);
	assert(game.players[2].magic == 0);
	assert(game.players[3].magic == 0);
	ft_printf("{green}OK{eoc}\n\n");

	str = "./corewar -n 2 resources/champs/Gagnant.cor";
	ft_printf("%s:\n", str);
	ac = ft_count_words(str, c);
	ft_bzero(&game, sizeof(t_game));
	av = ft_strsplit(str, c);
	parse_args(ac, av, &game);
	assert(game.players_nbr == 1);
	assert(game.players[0].magic == 0);
	assert(game.players[1].magic == COREWAR_EXEC_MAGIC);
	assert(game.players[2].magic == 0);
	assert(game.players[3].magic == 0);
	ft_printf("{green}OK{eoc}\n\n");

	str = "./corewar -n 3 resources/champs/Gagnant.cor resources/champs/Gagnant.cor";
	ft_printf("%s:\n", str);
	ac = ft_count_words(str, c);
	ft_bzero(&game, sizeof(t_game));
	av = ft_strsplit(str, c);
	parse_args(ac, av, &game);
	assert(game.players_nbr == 2);
	assert(game.players[0].magic == COREWAR_EXEC_MAGIC);
	assert(game.players[1].magic == 0);
	assert(game.players[2].magic == COREWAR_EXEC_MAGIC);
	assert(game.players[3].magic == 0);
	ft_printf("{green}OK{eoc}\n\n");

	str = "./corewar resources/champs/Gagnant.cor -n 3 resources/champs/Gagnant.cor";
	ft_printf("%s:\n", str);
	ac = ft_count_words(str, c);
	ft_bzero(&game, sizeof(t_game));
	av = ft_strsplit(str, c);
	parse_args(ac, av, &game);
	assert(game.players_nbr == 2);
	assert(game.players[0].magic == COREWAR_EXEC_MAGIC);
	assert(game.players[1].magic == 0);
	assert(game.players[2].magic == COREWAR_EXEC_MAGIC);
	assert(game.players[3].magic == 0);
	ft_printf("{green}OK{eoc}\n\n");

	str = "./corewar -n 2 resources/champs/Gagnant.cor -n 3 resources/champs/Gagnant.cor";
	ft_printf("%s:\n", str);
	ac = ft_count_words(str, c);
	ft_bzero(&game, sizeof(t_game));
	av = ft_strsplit(str, c);
	parse_args(ac, av, &game);
	assert(game.players_nbr == 2);
	assert(game.players[0].magic == 0);
	assert(game.players[1].magic == COREWAR_EXEC_MAGIC);
	assert(game.players[2].magic == COREWAR_EXEC_MAGIC);
	assert(game.players[3].magic == 0);
	ft_printf("{green}OK{eoc}\n\n");

	str = "./corewar -n 200 resources/champs/Gagnant.cor";
	ft_printf("%s:\n", str);
	ac = ft_count_words(str, c);
	ft_bzero(&game, sizeof(t_game));
	av = ft_strsplit(str, c);
	parse_args(ac, av, &game);
	assert(game.players[0].magic == 0);
	assert(game.players[1].magic == 0);
	assert(game.players[2].magic == 0);
	assert(game.players[3].magic == 0);
	ft_printf("{green}OK{eoc}\n\n");

	str = "./corewar -n string resources/champs/Gagnant.cor";
	ft_printf("%s:\n", str);
	ac = ft_count_words(str, c);
	ft_bzero(&game, sizeof(t_game));
	av = ft_strsplit(str, c);
	parse_args(ac, av, &game);
	assert(game.players[0].magic == 0);
	assert(game.players[1].magic == 0);
	assert(game.players[2].magic == 0);
	assert(game.players[3].magic == 0);
	ft_printf("{green}OK{eoc}\n\n");

	str = "./corewar -n -1 resources/champs/Gagnant.cor";
	ft_printf("%s:\n", str);
	ac = ft_count_words(str, c);
	ft_bzero(&game, sizeof(t_game));
	av = ft_strsplit(str, c);
	parse_args(ac, av, &game);
	assert(game.players[0].magic == 0);
	assert(game.players[1].magic == 0);
	assert(game.players[2].magic == 0);
	assert(game.players[3].magic == 0);
	ft_printf("{green}OK{eoc}\n\n");

	str = "./corewar -n 2 resources/champs/Gagnant.cor -n 2 resources/champs/Gagnant.cor";
	ft_printf("%s:\n", str);
	ac = ft_count_words(str, c);
	ft_bzero(&game, sizeof(t_game));
	av = ft_strsplit(str, c);
	parse_args(ac, av, &game);
	ft_printf("{green}OK{eoc}\n\n");

	str = "./corewar resources/champs/Gagnant.cor -n 1 resources/champs/Gagnant.cor";
	ft_printf("%s:\n", str);
	ac = ft_count_words(str, c);
	ft_bzero(&game, sizeof(t_game));
	av = ft_strsplit(str, c);
	parse_args(ac, av, &game);
	ft_printf("{green}OK{eoc}\n\n");

	str = "./corewar resources/champs/Gagnant.cor -v -dump 10 -n 2 resources/champs/Gagnant.cor";
	ft_printf("%s:\n", str);
	ac = ft_count_words(str, c);
	ft_bzero(&game, sizeof(t_game));
	av = ft_strsplit(str, c);
	parse_args(ac, av, &game);
	assert(game.visual == 1);
	assert(game.dump == 10);
	assert(game.players[0].magic == COREWAR_EXEC_MAGIC);
	assert(game.players[1].magic == COREWAR_EXEC_MAGIC);
	assert(game.players[2].magic == 0);
	assert(game.players[3].magic == 0);
	ft_printf("{green}OK{eoc}\n\n");

	str = "./corewar resources/champs/Gagnant.cor -v -dump 10 -n 2 resources/champs/Gagnant.cor";
	ft_printf("%s:\n", str);
	ac = ft_count_words(str, c);
	ft_bzero(&game, sizeof(t_game));
	av = ft_strsplit(str, c);
	parse_args(ac, av, &game);
	assert(game.visual == 1);
	assert(game.dump == 10);
	assert(game.players[0].magic == COREWAR_EXEC_MAGIC);
	assert(game.players[1].magic == COREWAR_EXEC_MAGIC);
	assert(game.players[2].magic == 0);
	assert(game.players[3].magic == 0);
	ft_printf("{green}OK{eoc}\n\n");

	str = "./corewar resources/champs/Gagnant.cor -n 2 resources/champs/Gagnant.cor -dump 10 -v";
	ft_printf("%s:\n", str);
	ac = ft_count_words(str, c);
	ft_bzero(&game, sizeof(t_game));
	av = ft_strsplit(str, c);
	parse_args(ac, av, &game);
	assert(game.visual == 1);
	assert(game.dump == 10);
	assert(game.players[0].magic == COREWAR_EXEC_MAGIC);
	assert(game.players[1].magic == COREWAR_EXEC_MAGIC);
	assert(game.players[2].magic == 0);
	assert(game.players[3].magic == 0);
	ft_printf("{green}OK{eoc}\n\n");

	return (0);
}
