/*
** graph_gen.h for  in /home/sabbah_j/rendu/TEK2/B4-ADVANCED-PSU/AUSP_ftrace
** 
** Made by jordan sabbah
** Login   <sabbah_j@epitech.net>
** 
** Started on  Thu Jul  9 15:35:29 2015 jordan sabbah
** Last update Sun Jul 12 23:18:49 2015 Thibaud Auzou
*/

#ifndef GRAPH_H_
# define GRAPH_H_

# include "graph_generator.h"
# include "graph_file.h"
# include "calls.h"
# include "enum.h"

typedef struct	s_graph
{
  t_node	*func;
  t_file	*file;
  t_listcall	*stack;
  bool		close;
  int		id;
  bool		(*call)(struct s_graph *, char *, t_call_type);
  bool		(*ret)(struct s_graph *);
  bool		(*end)(struct s_graph *);
}		t_graph;

t_graph		*create_graph();

#endif /* !GRAPH_H_ */
