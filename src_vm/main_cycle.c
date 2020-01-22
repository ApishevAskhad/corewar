/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 19:52:39 by slindgre          #+#    #+#             */
/*   Updated: 2020/01/22 22:15:34 by slindgre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void    execute_carry(t_game *game, t_carry *carry)
{
    (void)carry;
    (void)game;
        
}

void    execute_carries(t_game *game, t_carry *carry)
{
    while (carry)
    {
        execute_carry(game, carry);
        carry = carry->next;
    }
}

void check_lives(t_game *game, t_carry **carry)
{
    t_carry *head;
    t_carry *temp;

    head = *carry;
    while (head)
    {
        temp = head;
        head = head->next;
        if (temp->live)
        {
            game->lives += temp->live;
            temp->live = 0;
        }
        else
            *carry = del_carry(*carry, temp);
    }
}

void main_cycle(t_game *game, t_carry *carry)
{
    assert(game != NULL);
    assert(carry != NULL);
    while (carry)
    {
        game->cycles += 1;
        execute_carries(game, carry);
        if (game->cycle_to_die <= 0 || game->cycles % game->cycle_to_die == 0)
        {
            game->checkin_nbr += 1;
            check_lives(game, &carry);
            if (game->lives >= NBR_LIVE || game->checkin_nbr == MAX_CHECKS)
            {
                game->cycle_to_die -= CYCLE_DELTA;
                game->checkin_nbr = 0;
            } 
            game->lives = 0;
        }
        if (game->cycles == game->dump)
		    print_dump(game->mem, MEM_SIZE);   
    }
    
}
