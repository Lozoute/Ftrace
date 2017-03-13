/*
** buff_call.c for Ftrace in /home/lks/rendu/AUSP_ftrace
** 
** Made by Thibaud Auzou
** Login   <lks@epitech.net>
** 
** Started on  Sun Jul 12 13:46:04 2015 Thibaud Auzou
** Last update Sun Jul 12 14:00:18 2015 Thibaud Auzou
*/

#include "ftrace.h"

char		*last_call(int action, char *val)
{
  static char	b[BUFF_SIZE] = {0};

  if (action == SET && val && strlen(val) < BUFF_SIZE)
    sprintf(b, "%s", val);
  return (b);
}

char		*last_syscall(int action, char *val)
{
  static char	b[BUFF_SIZE] = {0};

  if (action == SET && val && strlen(val) < BUFF_SIZE)
    sprintf(b, "%s", val);
  return (b);
}
