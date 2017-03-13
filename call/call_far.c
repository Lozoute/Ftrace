/*
** call_far.c for Ftrace in /home/lks/rendu/AUSP_ftrace
** 
** Made by Thibaud Auzou
** Login   <lks@epitech.net>
** 
** Started on  Sun Jul 12 09:45:13 2015 Thibaud Auzou
** Last update Sun Jul 12 17:03:24 2015 Thibaud Auzou
*/

#include "ftrace.h"

int			get_call_far(t_regs *regs, pid_t pid, t_word *w)
{
  char			rm;

  rm = w->_word >> 8;
  if ((rm & 0x18) == 0x10)
    return (get_far_call_2(regs, pid, rm, w));
  else if ((rm & 0x18) == 0x18)
    return (get_far_call_3());
  return (NOK);
}

unsigned long long	choose_reg_call(t_regs *regs, int i)
{
  if (i == 0)
    return (regs->rax);
  if (i == 1)
    return (regs->rcx);
  if (i == 2)
    return (regs->rdx);
  if (i == 3)
    return (regs->rbx);
  if (i == 4)
    return (regs->rsp);
  if (i == 5)
    return (regs->rbp);
  if (i == 6)
    return (regs->rsi);
  if (i == 7)
    return (regs->rdi);
  return (0);
}

int			get_far_call_3(void)
{
  print_error("Mod R/M 0xFF /3 Not Implemented Yet.", 0);
  return (NOK);
}
