/*
** execute.c for strace in /home/lks/rendu/AUSP_strace
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Wed Apr 29 21:23:56 2015 Thibaud Auzou
** Last update Fri May  8 19:41:58 2015 Thibaud Auzou
*/

#include "ftrace.h"

int			execute(char **argv)
{
  extern char		**environ;

  if (ptrace(PTRACE_TRACEME, 0, NULL, NULL) == -1)
    return (print_error("ERROR [ptrace traceme] :", 1));
  if (execve(get_cmd(GET, 0), argv, environ) == -1)
    return (print_error("ERROR [execve] :", 1));
  return (OK);
}
