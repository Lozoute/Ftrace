/*
** cmd.c for strace in /home/lks/rendu/AUSP_strace
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Wed Apr 29 21:09:21 2015 Thibaud Auzou
** Last update Sat May  9 01:28:12 2015 Thibaud Auzou
*/

#include "ftrace.h"

char			*get_cmd(int action, char *new_cmd)
{
  static char		*cmd = NULL;

  if (action == SET && new_cmd != NULL)
    cmd = strdup(new_cmd);
  else if (action == DESTROY && cmd != NULL)
    {
      free(cmd);
      cmd = NULL;
    }
  return (cmd);
}

char			**get_argv(int action, char **new)
{
  static char		**_argv = NULL;

  if (action == SET && new != NULL)
    _argv = new;
  return (_argv);
}
