/*
** print_details.c for strace in /home/lks/rendu/AUSP_strace
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Thu May  7 13:39:16 2015 Thibaud Auzou
** Last update Sun Jul 12 22:25:20 2015 Thibaud Auzou
*/

#include "ftrace.h"

int				print_details_syscall(t_regs *regs,
						      t_syscall *syscall,
						      pid_t pid)
{
  char				b[BUFF_SIZE];
  int				i;

  wrap_enum(SET, syscall->_name);
  last_syscall(SET, syscall->_name);
  sprintf(b, "%s(", syscall->_name);
  buffer(SET, b);
  check_signal(syscall->_name, regs);
  for (i = 0; i < syscall->_nb_arg; ++i)
    {
      if (i > 0)
	buffer(SET, ", ");
      if (print_arg(syscall->_args_type[i], choose_register(regs, i)) == -1)
	return (ERROR);
    }
  return (print_return(regs, syscall->_return_type, pid));
}

static void		init_register_tabs(unsigned long long int **_64,
					   unsigned long long int **_32,
					   t_regs *regs)
{
  _64[0] = &(regs->rdi);
  _64[1] = &(regs->rsi);
  _64[2] = &(regs->rdx);
  _64[3] = &(regs->r10);
  _64[4] = &(regs->r8);
  _64[5] = &(regs->r9);
  _32[0] = &(regs->rbx);
  _32[1] = &(regs->rcx);
  _32[2] = &(regs->rdx);
  _32[3] = &(regs->rsi);
  _32[4] = &(regs->rdi);
  _32[5] = &(regs->rbp);
}

unsigned long long int		choose_register(t_regs *regs, int i)
{
  static unsigned long long int	*_64[MAX_ARGS] = {NULL};
  static unsigned long long int *_32[MAX_ARGS] = {NULL};

  if (_64[0] == NULL)
    init_register_tabs(_64, _32, regs);
  return ((choose_db() == 64) ? (*(_64[i])) : (*(_32[i])));
}

void				check_signal(char *name, t_regs *regs)
{
  int				pid;
  int				signal;
  char				b[BUFF_SIZE];
  char				p[BUFF_SIZE];

  if (name && !strcmp(name, "kill"))
    {
      memset(b, 0, BUFF_SIZE);
      pid = choose_register(regs, 0);
      signal = choose_register(regs, 1);
      save_pid(SET, pid);
      sprintf(p, "/proc/%d/exe", pid);
      if (readlink(p, b, BUFF_SIZE) == -1)
	sprintf(b, "Unknown");
      save_proc(SET, b);
      save_signal(SET, strsignal(signal));
    }
}
