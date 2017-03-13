/*
** test.c for  in /home/sabbah_j/rendu/TEK2/B4-ADVANCED-PSU/AUSP_ftrace/symbole_finder
** 
** Made by jordan sabbah
** Login   <sabbah_j@epitech.net>
** 
** Started on  Sat Jul 11 19:58:51 2015 jordan sabbah
** Last update Sun Jul 12 19:57:41 2015 jordan sabbah
*/

#include <unistd.h>
#include <string.h>
#include <strings.h>

int		main(int ac, char **av)
{
  char const	*str = "toto";

  write(1, strdup(str), strlen(str));
  return (1);
}
