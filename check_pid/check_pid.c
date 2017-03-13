/*
** check_pid.c for strace in /home/auzou_t/rendu/AUSP_strace
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Tue Apr 28 16:55:08 2015 Thibaud Auzou
** Last update Sun Jul 12 17:13:27 2015 Thibaud Auzou
*/

#include "ftrace.h"

int			check_pid(char *str_pid)
{
  char			buff[BUFF_SIZE];
  pid_t			pid;

  memset(buff, 0, BUFF_SIZE);
  if (str_pid == NULL)
    sprintf(buff, "ERROR :: No PID Specified");
  else if (strlen(str_pid) > 30 || (pid = atoi(str_pid)) <= 0)
    sprintf(buff, "ERROR :: %s Is Not A Valid PID", str_pid);
  else if (kill(pid, 0) == -1)
    sprintf(buff, "ERROR :: %s No Process With This PID", str_pid);
  if (strlen(buff) > 0)
    return (print_error(buff, 0));
  if (check_binary(pid) == ERROR)
    return (ERROR);
  get_pid(SET, pid);
  return (OK);
}

int			check_binary(pid_t pid)
{
  char			buff[BUFF_SIZE];
  char			path[BUFF_SIZE];

  memset(buff, 0, BUFF_SIZE);
  memset(path, 0, BUFF_SIZE);
  sprintf(path, "/proc/%d/exe", pid);
  if (readlink(path, buff, BUFF_SIZE) == -1)
    return (print_error("ERROR [readlink] :", 1));
  get_cmd(SET, buff);
  return (check_32_64(buff));
}
