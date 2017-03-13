/*
** call.c for Ftrace in /home/lks/rendu/AUSP_ftrace
** 
** Made by Thibaud Auzou
** Login   <lks@epitech.net>
** 
** Started on  Sat Jul 11 20:42:02 2015 Thibaud Auzou
** Last update Sun Jul 12 14:13:12 2015 Thibaud Auzou
*/

#include "ftrace.h"

int		get_call(t_regs *regs, pid_t pid, t_word *w, unsigned long m)
{
  int		ret;

  if (m == OP_CALLN && (ret = get_call_near(regs, w)) == ERROR)
    return (ERROR);
  else if (m == OP_CALLF && (ret = get_call_far(regs, pid, w)) == ERROR)
    return (ERROR);
  if (ret == OK && ptrace(PTRACE_SINGLESTEP, pid, NULL, NULL) == -1)
    return (print_error("ERROR [ptrace singlestep 7] :", 1));
  if (ret == OK)
    return (CALL);
  return (OK);
}
