/*
** load_args.c for strace in /home/lks/rendu/AUSP_strace
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Wed May  6 20:44:12 2015 Thibaud Auzou
** Last update Wed May  6 22:16:15 2015 Thibaud Auzou
*/

#include "ftrace.h"

int			load_args(t_syscall *new)
{
  if (load_nb_args(new) == ERROR)
    return (ERROR);
  if (new->_nb_arg > 0)
    if ((new->_args_type = malloc(sizeof(t_type) * new->_nb_arg)) == NULL)
      return (print_error("ERROR [malloc] :", 1));
  if (load_args_type(new) == ERROR)
    {
      free(new->_args_type);
      return (ERROR);
    }
  return (OK);
}

int			load_nb_args(t_syscall *new)
{
  char			*nb;

  if ((nb = strtok(NULL, SYSFILE_SEP)) == NULL)
    return (print_error("Corrupted Syscall Databse :: No Nb Args", 0));
  if ((new->_nb_arg = atoi(nb)) > MAX_ARGS || new->_nb_arg < MIN_ARGS)
    return (print_error("Corrupted Syscall Databse :: Unvalid Nb Args", 0));
  return (OK);
}

int			load_args_type(t_syscall *new)
{
  int			i;
  char			*type;

  for (i = 0; i < new->_nb_arg; ++i)
    {
      if ((type = strtok(NULL, SYSFILE_SEP)) == NULL)
	return (print_error("Corrupted Syscall Db :: Missing Arg Type", 0));
      if ((int)(new->_args_type[i] = load_type(type)) == -1)
	{
	  printf("%s\n", type);
	  return (print_error("Corrupted Syscall Db :: Unkown Arg Type", 0));
	}
    }
  if (strtok(NULL, SYSFILE_SEP) != NULL)
    return (print_error("Corrupted Syscall Db :: Too Many Args", 0));
  return (OK);
}
