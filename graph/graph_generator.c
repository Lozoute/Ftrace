/*
** graph_generator.c for  in /home/sabbah_j/rendu/TEK2/B4-ADVANCED-PSU/AUSP_ftrace
** 
** Made by jordan sabbah
** Login   <sabbah_j@epitech.net>
** 
** Started on  Wed Jul  8 14:39:23 2015 jordan sabbah
** Last update Sun Jul 12 23:21:33 2015 Thibaud Auzou
*/

#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "graph_file.h"
#include "graph.h"

static bool	add_call(t_call *this, int child)
{
  t_call	*current;

  current = this;
  while (current)
    {
      if (current->id_child == child && ++(current->counter))
	return (true);
      if (!current->next)
	break ;
      current = current->next;
    }
  return ((current->next = new_call(child)));
}

t_call		*new_call(int child_id)
{
  t_call	*call;

  if (!(call = malloc(sizeof(t_call))))
    return (NULL);
  call->id_child = child_id;
  call->next = NULL;
  call->counter = 1;
  call->add_call = &add_call;
  return (call);
}

static bool	add_reference(t_node *list, int parent_id, int child_id)
{
  while (list)
    {
      if (parent_id == list->id)
	{
	  if (!list->call_list && !(list->call_list = new_call(child_id)))
	    return (false);
	  return (list->call_list->add_call(list->call_list, child_id));
	}
      list = list->next;
    }
  return (false);
}

t_node		*new_node(char *str, int id, t_call_type type)
{
  t_node	*ptr;

  if (!(ptr = malloc(sizeof(t_node))))
    {
      perror("error in t_node *new_node(char *str)");
      return (NULL);
    }
  if (!(ptr->name = strdup(str)))
    {
      perror("error in t_node *new_node(char *str)");
      free(ptr);
      return (NULL);
    }
  ptr->id = id;
  ptr->next = NULL;
  ptr->call_list = NULL;
  ptr->type = type;
  ptr->add_reference = &add_reference;
  return (ptr);
}
