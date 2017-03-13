/*
** syscall_database.c for strace in /home/lks/rendu/AUSP_strace
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Wed May  6 21:17:40 2015 Thibaud Auzou
** Last update Fri May  8 14:51:02 2015 Thibaud Auzou
*/

#include "ftrace.h"

t_syscall		*get_syscall(int nb, int db)
{
  t_syscall		**database;
  int			(*nb_f)(int);

  nb_f = &nb_syscall_64;
  database = get_database_64(GET);
  if (db == 32)
    {
      nb_f = &nb_syscall_32;
      database = get_database_32(GET);
    }
  if (nb < 0 || nb > (*nb_f)(GET) || nb > MAX_SYSCALL)
    return (NULL);
  return (database[nb]);
}

int			add_syscall_to_database(t_syscall *new, int db)
{
  t_syscall		**database;
  int			(*nb_f)(int);

  nb_f = &nb_syscall_64;
  database = get_database_64(GET);
  if (db == 32)
    {
      nb_f = &nb_syscall_32;
      database = get_database_32(GET);
    }
  if ((*nb_f)(GET) >= MAX_SYSCALL)
    return (print_error("Corrupted Syscall Database :: Overflow", 0));
  if (database[(*nb_f)(GET)] != NULL)
    return (print_error("Corrupted Syscall Database :: Overlap", 0));
  database[(*nb_f)(GET)] = new;
  (*nb_f)(SET);
  return (OK);
}

int			destroy_database(void)
{
  get_database_64(DESTROY);
  get_database_32(DESTROY);
  return (OK);
}

int			choose_db(void)
{
  int			mode;
  int			op;

  mode = get_mode(GET, 0);
  op = get_last_op(GET, 0);
  if (mode == 64 && op == OP_SYSCALL)
    return (64);
  return (32);
}
