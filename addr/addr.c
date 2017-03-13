/*
** addr.c for Ftrace in /home/lks/rendu/AUSP_ftrace
** 
** Made by Thibaud Auzou
** Login   <lks@epitech.net>
** 
** Started on  Sun Jul 12 16:32:58 2015 Thibaud Auzou
** Last update Sun Jul 12 16:44:49 2015 Thibaud Auzou
*/

#include "ftrace.h"

t_pile			*g_pile = NULL;

int			add_addr(unsigned long long val,
				 unsigned long long call)
{
  t_pile		*new;

  if ((new = malloc(sizeof(t_pile))) == NULL)
    return (print_error("ERROR [malloc]: ", 1));
  new->_val = val;
  new->_call = call;
  new->_next = g_pile;
  g_pile = new;
  return (OK);
}

t_pile			*head_addr(void)
{
  return (g_pile);
}

void			pop_addr(void)
{
  t_pile		*tmp;

  if (g_pile)
    {
      tmp = g_pile;
      g_pile = tmp->_next;
      free(tmp);
    }
}
