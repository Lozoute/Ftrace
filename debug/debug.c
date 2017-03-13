/*
** debug.c for Ftrace in /home/lks/rendu/AUSP_ftrace
** 
** Made by Thibaud Auzou
** Login   <lks@epitech.net>
** 
** Started on  Sun Jul 12 01:51:06 2015 Thibaud Auzou
** Last update Sun Jul 12 01:51:42 2015 Thibaud Auzou
*/

#include "ftrace.h"

int		debug(int action)
{
  static int	_debug = 0;

  if (action == SET)
    _debug = 1;
  return (_debug);
}
