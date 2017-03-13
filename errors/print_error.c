/*
** print_error.c for strace in /home/lks/rendu/AUSP_strace
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Tue Apr 28 09:36:02 2015 Thibaud Auzou
** Last update Tue Apr 28 09:36:15 2015 Thibaud Auzou
*/

#include "ftrace.h"

int				print_error(const char *error, int option)
{
  fprintf(stderr, "\x1b[1;31m");
  if (!option)
    fprintf(stderr, "%s\n", error);
  else
    perror(error);
  fprintf(stderr, "\x1b[0m");
  return (ERROR);
}
