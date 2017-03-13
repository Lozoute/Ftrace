/*
** main.c for strace in /home/lks/rendu/AUSP_strace
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Sun May 17 18:03:01 2015 Thibaud Auzou
** Last update Mon Jul 13 00:22:22 2015 Thibaud Auzou
*/

#include "ftrace.h"
#include "macros.h"

int				main(int argc, char **argv)
{
  int				ret;

  if (argc < 2 || (argv && argv[1] && !strcmp(argv[1], "-debug") && argc < 3))
    return (print_error("Usage : ./ftrace <cmd> [./strace -p <pid>]", 0));
  if (argv && argv[1] && !strcmp(argv[1], "-debug"))
    debug(SET);
  if (signal(SIGINT, control_c) == SIG_ERR)
    return (print_error("signal()", 0));
  wrap_enum(SET, NULL);
  if (load_syscall_database(SYSFILE_64, 64) == ERROR ||
      load_syscall_database(SYSFILE_32, 32) == ERROR)
    return (ERROR);
  get_argv(SET, &(argv[(debug(GET) ? 2 : 1)]));
  if (!strcmp(argv[(debug(GET) ? 2 : 1)], PID_OPTION))
    ret = trace_pid(argv[(debug(GET) ? 3 : 2)]);
  else
    ret = trace_cmd(&(argv[(debug(GET) ? 2 : 1)]));
  destroy_ressources();
  return (ret);
}

int				trace_pid(char *str_pid)
{
  if (check_pid(str_pid) == ERROR)
    return (ERROR);
  if (attach(get_pid(GET, 0)) == ERROR)
    return (ERROR);
  if (trace() == ERROR)
    return (ERROR);
  return (OK);
}

int				trace_cmd(char **argv)
{
  pid_t				pid;

  if (check_cmd(argv) == ERROR)
    return (ERROR);
  if ((pid = fork()) == -1)
    return (print_error("ERROR [fork] :", 1));
  else if (pid == 0)
    return (execute(argv));
  get_pid(SET, pid);
  if (trace() == ERROR)
    return (ERROR);
  return (OK);
}

int				destroy_ressources(void)
{
  get_pid(DESTROY, 0);
  get_cmd(DESTROY, 0);
  destroy_database();
  buffer(DESTROY, 0);
  get_graph(DESTROY);
  destroy_elf();
  return (OK);
}

void				control_c(int sig)
{
  (void)(sig);
  if (wrap_attach(GET) == 1)
    dettach_c(get_pid(GET, 0));
  destroy_ressources();
  exit(0);
}
