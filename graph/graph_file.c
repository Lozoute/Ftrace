/*
** graph_file.c for  in /home/sabbah_j/rendu/TEK2/B4-ADVANCED-PSU/AUSP_ftrace/graph
** 
** Made by jordan sabbah
** Login   <sabbah_j@epitech.net>
** 
** Started on  Sun Jul 12 23:24:13 2015 jordan sabbah
** Last update Sun Jul 12 23:24:13 2015 jordan sabbah
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "graph_file.h"

static bool	write_file_call(t_file *this,
				int id_parent,
				int id_child,
				int counter)
{
  char		buffer[1024];
  int		len;

  bzero(buffer, 1024);
  sprintf(buffer, "%d->%d[label=\"%d\"];\n", id_parent, id_child, counter);
  len = write(this->fd, buffer, strlen(buffer));
  return ((len <= 0) ? false : true);
}

static bool	write_file_node(t_file *this,
				int id,
				char *name,
				t_call_type type)
{
  char		buffer[1024];
  int		len;
  char const	*colortab[] = {"grey", "orange", "green"};
  char const	*shapetab[] = {"oval", "rectangle", "Mdiamond"};
  char const	*str = "%d[style=filled, color=%s, shape=%s, label=\"%s\"];\n";

  bzero(buffer, 1024);
  sprintf(buffer, str, id, colortab[type], shapetab[type], name);
  len = write(this->fd, buffer, strlen(buffer));
  return ((len <= 0) ? false : true);
}

static bool	close_file(t_file *this)
{
  int		ret;
  char const	*str = "}";

  if (write(this->fd, str, strlen(str)) <= 0)
    {
      perror("error in function t_file *create_file()");
      return (NULL);
    }
  ret = close(this->fd);
  return ((ret == -1) ? false : true);
}

t_file		*create_file()
{
  t_file	*ptr;
  char const	*str = "digraph G {\n";

  if (!(ptr = malloc(sizeof(t_file))))
    return (NULL);
  if ((ptr->fd = creat("graph.dot", S_IRWXU | S_IRUSR | S_IWUSR)) == -1)
    {
      perror("error in function t_file *create_file()");
      free(ptr);
      return (NULL);
    }
  ptr->write_call = &write_file_call;
  ptr->write_func = &write_file_node;
  ptr->close = &close_file;
  if (write(ptr->fd, str, strlen(str)) <= 0)
    {
      perror("error in function t_file *create_file()");
      free(ptr);
      return (NULL);
    }
  return (ptr);
}
