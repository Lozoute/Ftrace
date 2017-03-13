/*
** databases.c for strace in /home/lks/rendu/AUSP_strace
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Fri May  8 14:34:09 2015 Thibaud Auzou
** Last update Fri May  8 14:35:16 2015 Thibaud Auzou
*/

#include "ftrace.h"

int		nb_syscall_64(int action)
{
  static int		_nb = 0;

  if (action == SET)
    ++_nb;
  return (_nb);
}

t_syscall	**get_database_64(int action)
{
  static t_syscall	*_database[MAX_SYSCALL] = {NULL};
  static int		first = 1;
  int			i;

  if (first)
    {
      memset(_database, 0, sizeof(t_syscall *) * MAX_SYSCALL);
      first ^= first;
    }
  if (action == DESTROY && _database[0] != NULL)
    for (i = 0; i < MAX_SYSCALL; ++i)
      if (_database[i] != NULL)
	{
	  free(_database[i]->_name);
	  _database[i]->_name = NULL;
	  free(_database[i]->_args_type);
	  _database[i]->_args_type = NULL;
	  free(_database[i]);
	  _database[i] = NULL;
	}
  return (_database);
}

int		nb_syscall_32(int action)
{
  static int		_nb = 0;

  if (action == SET)
    ++_nb;
  return (_nb);
}

t_syscall	**get_database_32(int action)
{
  static t_syscall	*_database[MAX_SYSCALL] = {NULL};
  static int		first = 1;
  int			i;

  if (first)
    {
      memset(_database, 0, sizeof(t_syscall *) * MAX_SYSCALL);
      first ^= first;
    }
  if (action == DESTROY && _database[0] != NULL)
    for (i = 0; i < MAX_SYSCALL; ++i)
      if (_database[i] != NULL)
	{
	  free(_database[i]->_name);
	  _database[i]->_name = NULL;
	  free(_database[i]->_args_type);
	  _database[i]->_args_type = NULL;
	  free(_database[i]);
	  _database[i] = NULL;
	}
  return (_database);
}
