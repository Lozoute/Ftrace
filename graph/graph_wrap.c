/*
** graph_wrap.c for  in /home/sabbah_j/rendu/TEK2/B4-ADVANCED-PSU/AUSP_ftrace/graph
** 
** Made by jordan sabbah
** Login   <sabbah_j@epitech.net>
** 
** Started on  Sun Jul 12 19:23:34 2015 jordan sabbah
** Last update Sun Jul 12 21:00:30 2015 Thibaud Auzou
*/

#include "ftrace.h"

t_graph			*get_graph(int action)
{
  static t_graph	*graph = NULL;

  if (action == GET && graph == NULL)
    {
      if ((graph = create_graph()) == NULL)
	{
	  print_error("ERROR [create_graph]: ", 1);
	  return (NULL);
	}
      graph->call(graph, get_cmd(GET, 0), false);
    }
  else if (action == DESTROY && graph)
    {
      graph->ret(graph);
      graph->end(graph);
      free(graph);
      graph = NULL;
    }
  return (graph);
}
