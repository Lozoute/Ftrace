/*
** print_arg.c for strace in /home/lks/rendu/AUSP_strace
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Sun May 17 18:21:29 2015 Thibaud Auzou
** Last update Sun Jul 12 18:37:53 2015 Thibaud Auzou
*/

#include "ftrace.h"

static void		init_type_func(t_type_func *_func)
{
  _func[0] = &display_int;
  _func[1] = &display_addr;
  _func[2] = &display_str;
  _func[3] = &display_void;
  _func[4] = &display_s_stat;
  _func[5] = &display_s_sig;
  _func[6] = &display_s_sock;
  _func[7] = &display_s_limit;
  _func[8] = &display_macro;
}

int			print_arg(t_type type, unsigned long long int val)
{
  static t_type_func	_func[NB_TYPES] = {NULL};

  if (_func[0] == NULL)
    init_type_func(_func);
  return ((*(_func[type]))(val));
}

static char		*p_errno(int err)
{
  --err;
  if (err < 0 || err >= NB_ERRNO)
    return ("");
  return (g_errno[err]._str);
}

int			print_return(t_regs *regs, t_type type, pid_t pid)
{
  char			b[BUFF_SIZE];
  int			ret;

  fflush(stdout);
  if (ptrace(PTRACE_SINGLESTEP, pid, NULL, NULL) == -1)
    return (print_error("ERROR [ptrace singlestep] :", 1));
  if ((ret = wait_for_pid(pid)) != OK)
    {
      buffer(SET, ")\t\t= ?");
      return (ret);
    }
  if (ptrace(PTRACE_GETREGS, pid, NULL, regs) == -1)
    return (print_error("ERROR [ptrace getregs] :", 1));
  buffer(SET, ")\t\t= ");
  if ((int)(regs->rax) < 0 && type == INT)
    {
      sprintf(b, "-1 %s (%s)", p_errno(regs->rax * -1),
	      strerror(regs->rax * -1));
      buffer(SET, b);
    }
  else if (print_arg(type, regs->rax) == ERROR)
    return (ERROR);
  return (OK);
}
