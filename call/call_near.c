/*
** call_near.c for Ftrace in /home/lks/rendu/AUSP_ftrace
** 
** Made by Thibaud Auzou
** Login   <lks@epitech.net>
** 
** Started on  Sun Jul 12 09:38:59 2015 Thibaud Auzou
** Last update Mon Jul 13 00:29:29 2015 Thibaud Auzou
*/

#include "ftrace.h"

int		get_call_near(t_regs *regs, t_word *w)
{
  long long int	dest;
  int		offset;
  char		*sym;
  char		b[BUFF_SIZE];

  offset = w->_word >> 8;
  dest = regs->rip + 5 + offset;
  if ((sym = find_symbol(dest)))
    {
      last_call(SET, sym);
      add_addr(regs->rip + 5, dest);
      sprintf(b, "[NAME: %s] [ADDRESS: %#llx]", sym, dest);
      if (buffer(SET, b) == NULL)
	return (ERROR);
      free(sym);
      return (OK);
    }
  if (debug(GET))
    debug_call_near(w, offset, dest, regs);
  return (NOK);
}

void		debug_call_near(t_word *w,
				int offset,
				long long int dest,
				t_regs *regs)
{
  char		b[BUFF_SIZE];
  t_graph	*graph;

  add_addr(regs->rip + 5, dest);
  sprintf(b, "%#llx", dest);
  if ((graph = get_graph(GET)))
    graph->call(graph, b, T_CALL);
  printf("%s[%-19s] [WORD: %#20llx] [OFFSET: %#10x][ADDRESS: %#16llx]%s\n",
	 YELLOW, "UNDEFINED CALL NEAR", w->_word, offset, dest, C_RESET);
}
