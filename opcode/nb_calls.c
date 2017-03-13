/*
** nb_calls.c for Ftrace in /home/lks/rendu/AUSP_ftrace
** 
** Made by Thibaud Auzou
** Login   <lks@epitech.net>
** 
** Started on  Sun Jul 12 14:42:33 2015 Thibaud Auzou
** Last update Sun Jul 12 14:48:13 2015 Thibaud Auzou
*/

#include "ftrace.h"

int		nb_call(int action)
{
  static int	nb = 0;

  if (action == SET)
    nb++;
  else if (action == CLEAN)
    nb--;
  else if (action == DESTROY)
    nb = 0;
  return (nb);
}

int		nb_undef(int action)
{
  static int	nb = 0;

  if (action == SET)
    nb++;
  else if (action == CLEAN)
    nb--;
  else if (action == DESTROY)
    nb = 0;
  return (nb);
}
