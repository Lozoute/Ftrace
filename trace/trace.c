/*
** trace.c for strace in /home/lks/rendu/AUSP_strace
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Wed Apr 29 21:27:25 2015 Thibaud Auzou
** Last update Mon Jul 13 00:22:39 2015 Thibaud Auzou
*/

#include "ftrace.h"

int			trace(void)
{
  t_regs		regs;
  int			ret;

  ret = OK;
  if ((ret = first_syscall(&regs)) != OK)
    return (ret);
  if (get_graph(GET) == NULL)
    return (ERROR);
  if (init_elf_list() == ERROR)
    return (ERROR);
  while (1)
    {
      if ((ret = wait_call(&regs)) == NOK || ret == ERROR)
	break ;
      if (ret == SYSCALL && print_infos_syscall(&regs) != OK)
	break ;
      if (buffer_flush(ret) == ERROR)
	break ;
    }
  if (first_param_save(GET, 0) != 0x42424242)
    printf("+++ Exited With %lld +++\n", first_param_save(GET, 0));
  return (OK);
}

int			wait_call(t_regs *regs)
{
  pid_t			pid;
  int			ret;

  pid = get_pid(GET, 0);
  while (1)
    {
      if ((ret = wait_for_pid(pid)) != OK)
	return (ret);
      if ((ret = is_call(regs, pid)) == ERROR)
	return (ERROR);
      else if (ret == SYSCALL || ret == CALL)
	break ;
      if (ptrace(PTRACE_SINGLESTEP, pid, NULL, NULL) == -1)
	return (print_error("ERROR [ptrace singlestep] :", 1));
    }
  return (ret);
}

int			is_call(t_regs *regs, pid_t pid)
{
  t_word		w;

  if (ptrace(PTRACE_GETREGS, pid, NULL, regs) == -1)
    return (print_error("ERROR [ptrace getregs] :", 1));
  w._word = ptrace(PTRACE_PEEKTEXT, pid, regs->rip, NULL);
  if (errno)
    return (print_error("ERROR [ptrace peektext] :", 1));
  return (decode_opcode(regs, pid, &w));
}

int			print_infos_syscall(t_regs *regs)
{
  pid_t			pid;
  t_syscall		*syscall;
  int			ret;

  pid = get_pid(GET, 0);
  ret = OK;
  if ((syscall = get_syscall(regs->rax, choose_db())) == NULL)
    printf("Syscall Non Implemented\n");
  else if ((ret = print_details_syscall(regs, syscall, pid)) == ERROR)
    return (ERROR);
  if (ret == OK && ptrace(PTRACE_SINGLESTEP, pid, NULL, NULL) == -1)
    return (print_error("ERROR [ptrace singlestep] :", 1));
  return (OK);
}

int			get_last_op(int action, int new_op)
{
  static int		_op = 0;

  if (action == SET && new_op != 0)
    _op = new_op;
  return (_op);
}
