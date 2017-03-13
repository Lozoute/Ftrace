/*
** print_struct.c for strace in /home/lks/rendu/AUSP_strace
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Fri May 15 17:39:57 2015 Thibaud Auzou
** Last update Sat Jul 11 15:09:39 2015 Thibaud Auzou
*/

#include "ftrace.h"

int             display_s_stat(unsigned long long int val)
{
  char		b[BUFF_SIZE];

  sprintf(b, "struct stat %#llx", val);
  if (buffer(SET, b) == NULL)
    return (ERROR);
  return (OK);
}

int             display_s_sig(unsigned long long int val)
{
  char		b[BUFF_SIZE];

  sprintf(b, "struct sigaction %#llx", val);
  if (buffer(SET, b) == NULL)
    return (ERROR);
  return (OK);
}

int             display_s_sock(unsigned long long int val)
{
  char		b[BUFF_SIZE];

  sprintf(b, "struct sockaddr %#llx", val);
  if (buffer(SET, b) == NULL)
    return (ERROR);
  return (OK);
}

int             display_s_limit(unsigned long long int val)
{
  char		b[BUFF_SIZE];

  sprintf(b, "struct rlimit %#llx", val);
  if (buffer(SET, b) == NULL)
    return (ERROR);
  return (OK);
}
