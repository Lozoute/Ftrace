/*
** get_enum.c for  in /home/vieira_q/official_clone/AUSP_strace
** 
** Made by quentin vieira
** Login   <vieira_q@epitech.net>
** 
** Started on  Fri May 15 17:58:13 2015 quentin vieira
** Last update Sun Jul 12 19:52:46 2015 jordan sabbah
*/

#include "enum.h"

static t_enum	*mmap_check()
{
  static int	i;

  if (i == 0)
    {
      i = 1;
      return (g_mmap_enum2);
    }
  else
    {
      i = 0;
      return (g_mmap_enum);
    }
}

t_enum		*wrap_enum(int action, char *str)
{
  static t_enum	*my_enum;
  int		i;

  i = 0;
  if (action == GET)
    {
      if (my_enum == g_mmap_enum)
	return (mmap_check());
      return (my_enum);
    }
  else if (action == SET)
    {
      my_enum = NULL;
      if (str == NULL)
	return (NULL);
      while (g_list_enum[i].syscall != NULL)
	{
	  if (strcmp(g_list_enum[i].syscall, str) == 0)
	    my_enum = g_list_enum[i].tab;
	  ++i;
	}
    }
  return (NULL);
}

static void	check_rd(unsigned long long int val, int *f)
{
  if (O_WRONLY & val)
    return ;
  else if (O_RDWR & val)
    return ;
  else
    {
      buffer(SET, "O_RDONLY");
      *f = 1;
      fflush(stdout);
    }
}

int		display_macro(unsigned long long int val)
{
  int		i;
  int		f;
  t_enum	*my_enum;

  my_enum = wrap_enum(GET, NULL);
  i = 0;
  f = 0;
  if (my_enum == NULL)
    return (0);
  while (my_enum[i].name != NULL)
    {
      if (strcmp(my_enum[i].name, "O_RDONLY") == 0)
	check_rd(val, &f);
      if (my_enum[i].value & val)
	{
	  if (f == 1)
	    buffer(SET, "|");
	  buffer(SET, my_enum[i].name);
	  f = 1;
	}
      ++i;
    }
  return (OK);
}
