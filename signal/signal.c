/*
** signal.c for Ftrace in /home/lks/rendu/AUSP_ftrace
** 
** Made by Thibaud Auzou
** Login   <lks@epitech.net>
** 
** Started on  Sun Jul 12 21:48:43 2015 Thibaud Auzou
** Last update Sun Jul 12 22:23:38 2015 Thibaud Auzou
*/

#include "ftrace.h"

int		save_pid(int action, int pid)
{
  static int	_pid = 0;

  if (action == SET)
    _pid = pid;
  return (_pid);
}

char		*save_signal(int action, char *signal)
{
  static char	_signal[BUFF_SIZE] = {0};

  if (action == SET && signal)
    sprintf(_signal, "%s", signal);
  return (_signal);
}

char		*save_proc(int action, char *proc)
{
  static char	_proc[BUFF_SIZE] = {0};

  if (action == SET && proc)
    sprintf(_proc, "%s", proc);
  return (_proc);
}
