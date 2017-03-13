/*
** load_database.c for strace in /home/lks/rendu/AUSP_strace
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Wed May  6 20:44:01 2015 Thibaud Auzou
** Last update Fri May  8 14:54:35 2015 Thibaud Auzou
*/

#include "ftrace.h"

int			load_syscall_database(char *db_name, int db)
{
  FILE			*file;
  char			buff[BUFF_SIZE];
  int			err;
  int			i;

  if ((file = fopen(db_name, "r")) == NULL)
    return (print_error("Unable To Open Syscall Database :", 1));
  for (i = 1; fgets(buff, BUFF_SIZE - 1, file); ++i)
    {
      if (buff[strlen(buff) - 1] == '\n')
	buff[strlen(buff) - 1] = 0;
      if ((err = load_line(buff, db)) == ERROR)
	{
	  printf("%s  --> Line %d\n", db_name, i);
	  break ;
	}
    }
  fclose(file);
  return ((err == ERROR) ? (err) : (OK));
}

int			load_line(char *line, int db)
{
  t_syscall		*new;
  int			err;

  if ((new = malloc(sizeof(t_syscall))) == NULL)
    return (print_error("ERROR [malloc] :", 1));
  memset(new, 0, sizeof(t_syscall));
  err = load_name(line, new);
  if (err != ERROR && load_return_type(new) == ERROR)
    err = ERROR;
  if (err != ERROR && load_args(new) == ERROR)
    err = ERROR;
  if (err == ERROR)
    {
      free(new);
      return (ERROR);
    }
  if (add_syscall_to_database(new, db) == ERROR)
    {
      free(new);
      return (ERROR);
    }
  return (OK);
}

int			load_name(char *line, t_syscall *new)
{
  char			*name;

  if ((name = strtok(line, SYSFILE_SEP)) == NULL)
    return (print_error("Corrupted Syscall Database :: No Name", 0));
  else if (strlen(name) > 25)
    return (print_error("Corrupted Syscall Database :: Unvalid Name", 0));
  if ((new->_name = strdup(name)) == NULL)
    return (print_error("ERROR [strdup] :", 1));
  return (OK);
}

int			load_return_type(t_syscall *new)
{
  char			*type;

  if ((type = strtok(NULL, SYSFILE_SEP)) == NULL)
    return (print_error("Corrupted Syscall Database :: No Return Type", 0));
  if ((int)(new->_return_type = load_type(type)) == -1)
    return (print_error("Corrupted Syscall Db :: Unknown Return Type", 0));
  return (OK);
}

t_type			load_type(char *type)
{
  static char		*types[NB_TYPES] = {STR_TYPES};
  int			i;

  for (i = 0; i < NB_TYPES; ++i)
    if (!strcmp(type, types[i]))
      return ((t_type)(i));
  return ((t_type)(-1));
}
