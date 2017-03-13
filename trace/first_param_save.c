/*
** rax_save.c for strace in /home/lks/rendu/AUSP_strace
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Sat May  9 00:34:15 2015 Thibaud Auzou
** Last update Sat May  9 00:54:22 2015 Thibaud Auzou
*/

#include "ftrace.h"

long long int			first_param_save(int action, long long int new)
{
  static long long int		_p = 0;

  if (action == SET)
    _p = new;
  return (_p);
}
