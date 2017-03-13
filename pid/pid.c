/*
** pid.c for strace in /home/auzou_t/rendu/AUSP_strace
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Tue Apr 28 16:57:43 2015 Thibaud Auzou
** Last update Tue Apr 28 17:11:05 2015 Thibaud Auzou
*/

#include "ftrace.h"

pid_t			get_pid(int action, pid_t new_pid)
{
  static pid_t		pid = 0;

  if (action == SET && new_pid > 0)
    pid = new_pid;
  return (pid);
}
