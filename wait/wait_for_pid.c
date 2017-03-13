/*
** wait_for_pid.c for strace in /home/lks/rendu/AUSP_strace
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Fri May  8 20:20:28 2015 Thibaud Auzou
** Last update Sun Jul 12 18:52:09 2015 Thibaud Auzou
*/

#include "ftrace.h"

static int		print_signal(int status)
{
  printf("+++ Killed By Signal %d +++\n", WTERMSIG(status));
  first_param_save(SET, 0x42424242);
  return (NOK);
}

static int		print_signal2(siginfo_t *sig, pid_t pid)
{
  fprintf(stderr, "+++ Killed By Signal %d :: ", sig->si_signo);
  psiginfo(sig, NULL);
  ptrace(PTRACE_DETACH, pid, 0, 0);
  kill(pid, sig->si_signo);
  first_param_save(SET, 0x42424242);
  return (NOK);
}

int			wait_for_pid(pid_t pid)
{
  int			status;
  siginfo_t		sig;

  if (kill(pid, 0) == -1)
    return (ERROR);
  if (waitpid(pid, &status, 0) == -1)
    return (print_error("ERROR [waitpid] :", 1));
  if (WIFEXITED(status))
    return (NOK);
  if (WIFSIGNALED(status))
    return (print_signal(status));
  if (ptrace(PTRACE_GETSIGINFO, pid, NULL, &sig) == -1)
    return (print_error("ERROR [ptrace getsiginfo] :", 1));
  if (sig.si_signo != SIGSTOP && sig.si_signo != SIGTRAP && sig.si_status)
    return (print_signal2(&sig, pid));
  if (WIFSTOPPED(status))
    return (OK);
  return (ERROR);
}
