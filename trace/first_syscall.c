/*
** first_syscall.c for strace in /home/lks/rendu/AUSP_strace
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Sat May  9 00:55:24 2015 Thibaud Auzou
** Last update Sun Jul 12 03:27:10 2015 Thibaud Auzou
*/

#include "ftrace.h"

int			first_syscall(t_regs *regs)
{
  if (wrap_attach(GET))
    return (first_syscall_attached(regs));
  return (first_syscall_exec());
}

int			first_syscall_attached(t_regs *regs)
{
  int			ret;
  pid_t			pid;
  t_syscall		*sys;

  pid = get_pid(GET, 0);
  if ((ret = wait_for_pid(pid)) != OK)
    return (ret);
  if (ptrace(PTRACE_GETREGS, pid, NULL, regs) == -1)
    return (print_error("ERROR [ptrace getregs] :", 1));
  get_last_op(SET, OP_SYSCALL);
  first_param_save(SET, choose_register(regs, 0));
  if ((sys = get_syscall(regs->orig_rax, choose_db())) == NULL)
    printf("Syscall Non Implemented\n");
  else if ((ret = print_details_syscall(regs, sys, pid)) == ERROR)
    return (ERROR);
  if (ret == OK && ptrace(PTRACE_SINGLESTEP, pid, NULL, NULL) == -1)
    return (print_error("ERROR [ptrace singlestep] :", 1));
  return (OK);
}

static int		count(char **env)
{
  int			i;

  for (i = 0; env && env[i]; ++i);
  return (i);
}

int			first_syscall_exec(void)
{
  char			*cmd;
  char			**argv;
  extern char		**environ;
  int			nb;
  int			i;

  cmd = get_cmd(GET, 0);
  argv = get_argv(GET, 0);
  nb = count(environ);
  printf("%s[SYSCALL] [execve(\"%s\", [", BLUE, cmd);
  for (i = 0; argv && argv[i] && i < 10; ++i)
    printf("%s\"%s\"", (i > 0) ? (" ,") : (""), argv[i]);
  if (i >= 10)
    printf(", ...");
  printf("], [/* %d vars */] = 0]%s\n", nb, C_RESET);
  return (OK);
}
