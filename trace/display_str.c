/*
** display_str.c for Ftrace in /home/lks/rendu/AUSP_ftrace
** 
** Made by Thibaud Auzou
** Login   <lks@epitech.net>
** 
** Started on  Sat Jul 11 15:03:20 2015 Thibaud Auzou
** Last update Sat Jul 11 15:12:07 2015 Thibaud Auzou
*/

#include "ftrace.h"

static int	display_char(pid_t pid, unsigned long long int val)
{
  int		i;
  char		c;

  for (i = 0; i < MAX_STR; ++i)
    {
      c = ptrace(PTRACE_PEEKTEXT, pid, val + i, NULL);
      if (c == -1 && errno)
	return (print_error("ERROR [ptrace peektext str] :", 1));
      else if (c == 0)
	break ;
      if (display_c(c) == ERROR)
	return (ERROR);
    }
  return (i);
}

int		display_str(unsigned long long int val)
{
  char		b[BUFF_SIZE * 2];
  pid_t		pid;
  int		i;

  pid = get_pid(GET, 0);
  if (val == 0x0 && buffer(SET, "NULL") == NULL)
    return (ERROR);
  else
    {
      if (buffer(SET, "\"") == NULL)
	return (ERROR);
      if ((i = display_char(pid, val)) == ERROR)
	return (ERROR);
      sprintf(b, "%s\"", (i == MAX_STR) ? (" ...") : (""));
      if (buffer(SET, b) == NULL)
	return (ERROR);
    }
  return (OK);
}
