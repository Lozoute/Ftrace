/*
** call_far_2.c for Ftrace in /home/lks/rendu/AUSP_ftrace
** 
** Made by Thibaud Auzou
** Login   <lks@epitech.net>
** 
** Started on  Sun Jul 12 13:00:48 2015 Thibaud Auzou
** Last update Mon Jul 13 00:29:57 2015 Thibaud Auzou
*/

#include "ftrace.h"

int			get_far_call_2(t_regs *regs,
				       pid_t pid,
				       char rm,
				       t_word *w)
{
  unsigned long long	dest;
  char			*sym;
  char			b[BUFF_SIZE];

  if (((signed)(dest = get_far_call_2_dest(regs, pid, rm, w))) == ERROR)
    return (ERROR);
  else if ((signed)(dest) == -2)
    return (NOK);
  if ((sym = find_symbol(dest)))
    {
      last_call(SET, sym);
      add_addr(regs->rip + 2, dest);
      sprintf(b, "[NAME: %s] [ADDRESS: %#llx]", sym, dest);
      if (buffer(SET, b) == NULL)
	return (ERROR);
      free(sym);
      return (OK);
    }
  return (debug_call_far_2(w, regs, dest, rm));
}

unsigned long long	get_far_call_2_dest(t_regs *regs,
					    pid_t pid,
					    char rm,
					    t_word *w)
{
  unsigned long long	val;
  unsigned long long	dest;

  dest = 0;
  val = choose_reg_call(regs, (rm & 0x07));
  if ((rm & 0xC0) >> 6 == 3)
    dest = val;
  else if ((rm & 0xC0) >> 6 == 0 && (rm & 0x07) != 4 && (rm & 0x07) != 5 &&
	   ((long long)(dest = ptrace(PTRACE_PEEKTEXT, pid, val, NULL))) == -1
	   && errno)
    return (print_error("ERROR [ptrace peek_text callf]: ", 1));
  else if ((rm & 0xC0) >> 6 == 0 && (rm & 0x07) == 5)
    return (add_dest_32(regs->rip, w, pid));
  else if ((rm & 0xC0) >> 6 == 2 && (rm & 0x07) != 4)
    return ((add_dest_32(val, w, pid)));
  else if ((rm & 0xC0) >> 6 == 1 && (rm & 0x07) != 4)
    return (add_dest_8(val, w, pid));
  else
    return ((unsigned long long)(-2));
  return (dest);
}

unsigned long long	add_dest_32(unsigned long long dest,
				    t_word *w,
				    pid_t pid)
{
  int			offset;

  offset = w->_word >> 16;
  dest += offset;
  if ((long long)(dest = ptrace(PTRACE_PEEKTEXT, pid, dest, NULL)) == -1)
    return ((unsigned long long)(-2));
  return (dest);
}

unsigned long long	add_dest_8(unsigned long long dest,
				   t_word *w,
				   pid_t pid)
{
  char			offset;

  offset = w->_word >> 16;
  dest += offset;
  if ((long long)(dest = ptrace(PTRACE_PEEKTEXT, pid, dest, NULL)) == -1)
    return ((unsigned long long)(-2));
  return (dest);
}

int			debug_call_far_2(t_word *w,
				       t_regs *regs,
				       unsigned long long dest,
				       char rm)
{
  char			b[BUFF_SIZE];
  t_graph		*graph;

  if (!debug(GET) || !(graph = get_graph(GET)))
    return (NOK);
  add_addr(regs->rip + 2, dest);
  sprintf(b, "%#llx", dest);
  graph->call(graph, b, T_CALL);
  printf("%s[%-19s] [WORD: %#20llx] [RM: %s %#x][ADDRESS: %#16llx]%s\n",
	 YELLOW, "UNDEFINED CALL FAR", w->_word, "FF /2", (int)(rm) & 0xFF,
	 dest, C_RESET);
  return (NOK);
}
