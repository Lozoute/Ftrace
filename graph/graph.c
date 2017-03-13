/*
** graph.c for  in /home/sabbah_j/rendu/TEK2/B4-ADVANCED-PSU/AUSP_ftrace/graph
** 
** Made by jordan sabbah
** Login   <sabbah_j@epitech.net>
** 
** Started on  Thu Jul  9 18:35:27 2015 jordan sabbah
** Last update Sun Jul 12 23:21:20 2015 Thibaud Auzou
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "graph.h"

static t_node	*find_node(t_graph *graph, char *s1, t_call_type type)
{
  t_node	*list;

  if (!(list = graph->func))
    return ((graph->func = new_node(s1, graph->id++, type)));
  while (list)
    {
      if (!strcmp(list->name, s1))
	return list;
      if (!list->next)
	break ;
      list = list->next;
    }
  return ((list->next = new_node(s1, graph->id++, type)));
}

static bool	call(t_graph *graph, char *name, t_call_type type)
{
  t_node	*child;

  if (!(child = find_node(graph, name, type)))
    return (false);
  if (!graph->stack)
    {
      if (!(graph->stack = new_listcall(graph->func)))
	return (false);
      return (graph->stack->add_call(graph->stack, child));
    }
  if (!(graph->stack->add_reference(graph->stack, child->id)))
    return (false);
  return (graph->stack->add_call(graph->stack, child));
}

static bool	ret(t_graph *graph)
{
  if (!graph->stack)
    return (true);
  return ((graph->stack->ret_call(graph->stack)));
}

static bool	close(t_graph *graph)
{
  t_file	*file;
  t_node	*list;
  t_call	*call;

  if (graph->close || !(file = graph->file))
    return (false);
  for (list = graph->func; list; graph->func = list)
    {
      if (!file->write_func(file, list->id, list->name, list->type))
	return (false);
      for (call = list->call_list; call; graph->func->call_list = call)
	{
	  if (!file->write_call(file, list->id, call->id_child, call->counter))
	    return (false);
	  call = call->next;
	  free(graph->func->call_list);
	}
      list = list->next;
      free(graph->func->name);
      free(graph->func);
    }
  file->close(file);
  free(file);
  graph->file = NULL;
  return ((graph->close = true));
}

t_graph		*create_graph()
{
  t_graph	*graph;

  if (!(graph = malloc(sizeof (t_graph))))
    return (NULL);
  graph->id = 0;
  graph->call = &call;
  graph->ret = &ret;
  graph->func = NULL;
  graph->stack = NULL;
  graph->close = false;
  graph->end = &close;
  if (!(graph->file = create_file()))
    return (NULL);
  return (graph);
}
