/*
** print_warning.c for strace in /home/lks/rendu/AUSP_strace
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Tue Apr 28 09:35:53 2015 Thibaud Auzou
** Last update Tue Apr 28 09:36:32 2015 Thibaud Auzou
*/

#include "ftrace.h"

int			print_warning(const char *warning)
{
  fprintf(stderr, "\x1b[1;33m%s\x1b[0m\n", warning);
  return (NOK);
}
