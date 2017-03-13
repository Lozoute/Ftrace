/*
** display_types.c for strace in /home/lks/rendu/AUSP_strace
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Sun May 17 18:06:40 2015 Thibaud Auzou
** Last update Sun Jul 12 18:38:20 2015 Thibaud Auzou
*/

#include "ftrace.h"

int		display_int(unsigned long long int val)
{
  char		b[BUFF_SIZE];

  sprintf(b, "%d", (signed int)(val));
  if (buffer(SET, b) == NULL)
    return (ERROR);
  return (OK);
}

int		display_addr(unsigned long long int val)
{
  char		b[BUFF_SIZE];

  if (val == 0x0)
    sprintf(b, "NULL");
  else
    sprintf(b, "%#llx", val);
  if (buffer(SET, b) == NULL)
    return (ERROR);
  return (OK);
}

int		display_c(char c)
{
  char		b[BUFF_SIZE];

  if (c == '\n')
    sprintf(b, "\\n");
  else if (isprint(c))
    sprintf(b, "%c", c);
  else
    sprintf(b, "\\%o", (int)(c));
  if (buffer(SET, b) == NULL)
    return (ERROR);
  return (OK);
}

int		display_void(unsigned long long int val)
{
  char		b[BUFF_SIZE];

  (void)(val);
  sprintf(b, "VOID");
  if (buffer(SET, b) == NULL)
    return (ERROR);
  return (OK);
}
