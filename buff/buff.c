/*
** buff.c for Ftrace in /home/lks/rendu/AUSP_ftrace
** 
** Made by Thibaud Auzou
** Login   <lks@epitech.net>
** 
** Started on  Sat Jul 11 14:12:01 2015 Thibaud Auzou
** Last update Sun Jul 12 22:59:23 2015 Thibaud Auzou
*/

#include "ftrace.h"

char		*buffer(int action, char *val)
{
  static char	*buff = NULL;
  static int	size = 0;

  if (buff == NULL && buffer_init(&buff, &size) == ERROR)
    return (NULL);
  if (action == SET && val && buffer_cat(&buff, &size, val) == ERROR)
    return (NULL);
  else if (action == DESTROY)
    {
      if (buff)
	free(buff);
      buff = NULL;
      size = 0;
    }
  return (buff);
}

int		buffer_init(char **buff, int *size)
{
  if (!buff || !size)
    return (print_error("ERROR [null ptr buff_intt]", 0));
  if ((*buff = malloc(sizeof(char) * BUFF_SIZE * 2)) == NULL)
    return (print_error("ERROR [malloc]: ", 1));
  memset(*buff, 0, BUFF_SIZE * 2);
  *size = BUFF_SIZE * 2 - 1;
  return (OK);
}

int		buffer_cat(char **buff, int *size, char *val)
{
  char		*new;

  if (!buff || !(*buff) || !size || !val)
    return (print_error("ERROR [NullPtr buffer_cat]", 0));
  if (*size < (int)(strlen(val) + 1))
    {
      *size = strlen(*buff) + BUFF_SIZE;
      if ((new = malloc(sizeof(char) * (*size))) == NULL)
	return (print_error("ERROR [malloc cmd_ia_voir_strcat]: ", 1));
      memset(new, 0, *size);
      *size -= (strlen(*buff) + 1);
      strcpy(new, *buff);
      free(*buff);
      *buff = new;
    }
  strcat(*buff, val);
  *size -= strlen(val);
  return (OK);
}

int		buffer_flush(int type)
{
  t_graph	*graph;
  char		b[BUFF_SIZE];

  if ((graph = get_graph(GET)) == NULL)
    return (ERROR);
  if (type == SYSCALL && buffer(GET, 0))
    {
      printf("%s[SYSCALL] [%s]%s\n", BLUE, buffer(GET, 0), C_RESET);
      graph->call(graph, last_syscall(GET, 0), T_SYSCALL);
      if (last_syscall(GET, 0) && !strcmp(last_syscall(GET, 0), "kill"))
	flush_signal(graph);
      graph->ret(graph);
    }
  else if (type == CALL)
    {
      sprintf(b, "%s %#llx", last_call(GET, 0),
	      (head_addr() ? head_addr()->_call : 0));
      graph->call(graph, b, T_CALL);
      printf("%s[%-7s] %s%s\n", GREEN, "CALL", buffer(GET, 0), C_RESET);
    }
  buffer(DESTROY, 0);
  return (OK);
}

void		flush_signal(t_graph *graph)
{
  char		b[BUFF_SIZE];

  printf("%s[SIGNAL ] [DEST: %s] [PID: %d] [SIG: %s]%s\n",
	 YOLO, save_proc(GET, 0) ? save_proc(GET, 0) : "?", save_pid(GET, 0),
	 save_signal(GET, 0) ? save_signal(GET, 0) : "0", C_RESET);
  sprintf(b, "[Dest: %s (%d)][Sig: %s]",
	  save_proc(GET, 0) ? save_proc(GET, 0) : "?", save_pid(GET, 0),
	  save_signal(GET, 0) ? save_signal(GET, 0) : "0");
  graph->call(graph, b, T_SIGNAL);
  graph->ret(graph);
}
