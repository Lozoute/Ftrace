/*
** calls.c for  in /home/sabbah_j/rendu/TEK2/B4-ADVANCED-PSU/AUSP_ftrace/graph
** 
** Made by jordan sabbah
** Login   <sabbah_j@epitech.net>
** 
** Started on  Sun Jul 12 01:21:44 2015 jordan sabbah
** Last update Sun Jul 12 10:27:20 2015 jordan sabbah
*/

#include <stdlib.h>
#include <stdio.h>
#include "calls.h"

static bool		add_call(t_listcall *list, t_node *node)
{
  t_listcall		*next;
  t_listcall		*prev;

  prev = list;
  next = list->next;
  if (!list->node && (list->node = node))
    return (true);
  while (next)
    {
      prev = next;
      next = next->next;
    }
  if (!(prev->next = new_listcall(node)))
    return (false);
  prev->next->prev = prev;
  return (true);
}

static bool		ret_call(t_listcall *list)
{
  t_listcall		*next;
  t_listcall		*prev;

  prev = list;
  next = list->next;
  if (!list || !list->node)
    return (true);
  if (!list->next && !(list->node = NULL))
    return (true);
  while (next->next)
    {
      prev = next;
      next = next->next;
    }
  free(next);
  prev->next = NULL;
  return (true);
}

static bool		add_reference(t_listcall *list, int child_id)
{
  t_call		*call;

  if (!list->node)
    return (false);
  while (list->next)
    list = list->next;
  call = list->node->call_list;
  if (!call)
    return ((list->node->call_list = new_call(child_id)));
  return (call->add_call(call, child_id));
}

t_listcall		*new_listcall(t_node *node)
{
  t_listcall		*list;

  if (!(list = malloc(sizeof (t_listcall))))
    return (NULL);
  list->node = node;
  list->next = NULL;
  list->prev = NULL;
  list->add_call = &add_call;
  list->ret_call = &ret_call;
  list->add_reference = &add_reference;
  return (list);
}
