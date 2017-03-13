/*
** opcode.c for Ftrace in /home/lks/rendu/AUSP_ftrace
** 
** Made by Thibaud Auzou
** Login   <lks@epitech.net>
** 
** Started on  Sat Jul 11 14:44:41 2015 Thibaud Auzou
** Last update Sun Jul 12 19:23:06 2015 Thibaud Auzou
*/

#include "ftrace.h"

int		decode_opcode(t_regs *regs, pid_t pid, t_word *w)
{
  long unsigned	mask;

  if (head_addr() && head_addr()->_val == regs->rip)
    return (decode_ret());
  mask = w->_word & 0xFFFF;
  if (mask == OP_INT80 || mask == OP_SYSCALL || mask == OP_SYSENTER)
    {
      get_last_op(SET, mask);
      first_param_save(SET, choose_register(regs, 0));
      return (SYSCALL);
    }
  else if ((mask = (w->_word & 0xFF)) == OP_CALLN || mask == OP_CALLF)
    return (decode_call(regs, pid, w, mask));
  else if (choose_db() == 64 && mask >= OP_REXMIN &&
	   mask <= OP_REXMAX && (mask >> 8) == OP_CALLF)
    return (decode_rex(regs, pid, w));
  return (OK);
}

int		decode_call(t_regs *regs,
			    pid_t pid,
			    t_word *w,
			    long unsigned mask)
{
  return (get_call(regs, pid, w, mask));
}

int		decode_rex(t_regs *regs, pid_t pid, t_word *w)
{
  return (get_call_rex(regs, pid, w));
}

int		decode_ret(void)
{
  pop_addr();
  return (get_return());
}
