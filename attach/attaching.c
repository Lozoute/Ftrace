/*
** attaching.c for  in /home/vieira_q/Unix_programming/AUSP_strace/attach
** 
** Made by quentin vieira
** Login   <vieira_q@epitech.net>
** 
** Started on  Tue May  5 13:39:19 2015 quentin vieira
** Last update Sun Jul 12 18:31:42 2015 Thibaud Auzou
*/

#include "ftrace.h"

int		attach(pid_t pid)
{
  if (ptrace(PTRACE_ATTACH, pid, 0, 0) == -1)
    return (print_error("ERROR [ptrace attach] :", 1));
  wrap_attach(SET);
  return (OK);
}

int		dettach(pid_t pid)
{
  if (ptrace(PTRACE_DETACH, pid, 0, 0) == ERROR)
    return (print_error("ERROR [ptrace detach] :", 1));
  return (OK);
}

int		dettach_c(pid_t pid)
{
  if (ptrace(PTRACE_DETACH, pid, 0, 0) == -1)
    {
      if (kill(pid, SIGSTOP) == ERROR)
	return (print_error("ERROR [kill sigstop] :", 1));
      if (wait_for_pid(pid) != OK)
	return (print_error("ERROR [wifstopped]", 0));
      if (ptrace(PTRACE_DETACH, pid, 0, 0) == ERROR)
	return (print_error("ERROR [ptrace detach] :", 1));
      if (kill(pid, SIGCONT) == ERROR)
	return (print_error("ERROR [kill sigcont] :", 1));
    }
  return (OK);
}

int		wrap_attach(int action)
{
  static int	attach = 0;

  if (action == SET)
    attach = 1;
  else if (action == GET)
    return (attach);
  return (2);
}
