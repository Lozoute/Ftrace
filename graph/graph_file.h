/*
** graph_file.h for  in /home/sabbah_j/rendu/TEK2/B4-ADVANCED-PSU/AUSP_ftrace
** 
** Made by jordan sabbah
** Login   <sabbah_j@epitech.net>
** 
** Started on  Thu Jul  9 02:01:37 2015 jordan sabbah
** Last update Sun Jul 12 23:20:15 2015 Thibaud Auzou
*/

#ifndef GRAPH_FILE_H_
# define GRAPH_FILE_H_

# include <stdbool.h>
# include "enum.h"

typedef struct	s_file
{
  int		fd;
  bool		(*write_func)(struct s_file *, int, char *, t_call_type);
  bool		(*write_call)(struct s_file *, int, int, int);
  bool		(*close)(struct s_file *);
}		t_file;

t_file		*create_file();

#endif /* !GRAPH_FILE_H_ */
