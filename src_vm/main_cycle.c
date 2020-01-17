/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 19:52:39 by slindgre          #+#    #+#             */
/*   Updated: 2020/01/17 23:18:40 by slindgre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void    execute_carry(t_carry *carry)
{
    (void)carry;
        
}

void    execute_carries(t_carry *carry)
{
    while (carry)
    {
        execute_carry(carry);
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
        execute_carries(carry);
        if (game->cycles % game->cycle_to_die == 0)
        {
            check_lives(game, &carry);
            if (game->lives >= NBR_LIVE || game->checkin_nbr == MAX_CHECKS)
            {
                game->cycle_to_die -= CYCLE_DELTA;
                game->checkin_nbr = 0;
            }
            else 
                game->checkin_nbr += 1;
        }
        if (game->cycles == game->dump)
		    print_dump(game->mem, MEM_SIZE);   
    }
    
}
