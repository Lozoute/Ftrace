/*
** graph_generator.h for  in /home/sabbah_j/rendu/TEK2/B4-ADVANCED-PSU/AUSP_ftrace/graph
** 
** Made by jordan sabbah
** Login   <sabbah_j@epitech.net>
** 
** Started on  Sun Jul 12 19:25:41 2015 jordan sabbah
** Last update Sun Jul 12 23:21:56 2015 Thibaud Auzou
*/

#ifndef GRAPH_GENERATOR_H_
# define GRAPH_GENERATOR_H_

# include <stdbool.h>
# include "enum.h"

typedef struct	s_call
{
  int		id_child;
  int		counter;
  bool		(*add_call)(struct s_call *, int);
  struct s_call	*next;
}		t_call;

typedef struct	s_node
{
  char		*name;
  int		id;
  t_call	*call_list;
  t_call_type	type;
  bool		(*add_reference)(struct s_node *, int, int);
  struct s_node	*next;
}		t_node;

t_node		*new_node(char *, int, t_call_type);
t_call		*new_call(int);

#endif /* !GRAPH_GENERATOR_H_ */
