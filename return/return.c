/*
** return.c for Ftrace in /home/lks/rendu/AUSP_ftrace
** 
** Made by Thibaud Auzou
** Login   <lks@epitech.net>
** 
** Started on  Sun Jul 12 09:27:17 2015 Thibaud Auzou
** Last update Sun Jul 12 16:55:47 2015 Thibaud Auzou
*/

#include "ftrace.h"

int		get_return(void)
{
  t_graph	*graph;

  if ((graph = get_graph(GET)) == NULL)
    return (ERROR);
  graph->ret(graph);
  return (OK);
}
