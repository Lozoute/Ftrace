/*
** calls.h for  in /home/sabbah_j/rendu/TEK2/B4-ADVANCED-PSU/AUSP_ftrace/graph
** 
** Made by jordan sabbah
** Login   <sabbah_j@epitech.net>
** 
** Started on  Sun Jul 12 01:17:52 2015 jordan sabbah
** Last update Sun Jul 12 03:03:40 2015 jordan sabbah
*/

#ifndef CALLS_H_
# define CALLS_H_

# include "graph_generator.h"

typedef struct		s_listcall
{
  t_node		*node;
  struct s_listcall	*next;
  struct s_listcall	*prev;
  bool			(*add_call)(struct s_listcall *, t_node *);
  bool			(*ret_call)(struct s_listcall *);
  bool			(*add_reference)(struct s_listcall *, int);
}			t_listcall;

t_listcall		*new_listcall(t_node *);

#endif /* !CALLS_H_ */
