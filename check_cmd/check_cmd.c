/*
** check_cmd.c for strace in /home/auzou_t/rendu/AUSP_strace
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Tue Apr 28 17:24:04 2015 Thibaud Auzou
** Last update Sun Jul 12 17:09:13 2015 Thibaud Auzou
*/

#include "ftrace.h"

static void		check_with_all_paths(char *buff,
					     char *path,
					     char *paths,
					     char **argv)
{
  char			*tmp;

  if (paths == NULL)
    sprintf(buff, "ERROR :: %s Is Not A Valid CMD", argv[0]);
  else if (access(strcat(strcat(path, "./"), argv[0]), F_OK | X_OK) == -1)
    for (tmp = strtok(paths, ":"); tmp != NULL; tmp = strtok(NULL, ":"))
      {
	strcpy(path, tmp);
	strcat(path, "/");
	strcat(path, argv[0]);
	if (access(path, F_OK) == -1)
	  sprintf(buff, "ERROR :: %s Is Not A Valid CMD", argv[0]);
	else
	  {
	    memset(buff, 0, BUFF_SIZE);
	    break ;
	  }
      }
}

static int		is_reg_file(char *buff, char *path, char **argv)
{
  t_stat		s;

  if (stat(path, &s) == -1)
    {
      sprintf(buff, "ERROR :: %s Is Not A Valid CMD", argv[0]);
      return (0);
    }
  else if (!S_ISREG(s.st_mode) || S_ISDIR(s.st_mode))
    {
      sprintf(buff, "ERROR :: %s Is Not A Valid CMD", argv[0]);
      return (0);
    }
  return (1);
}

int			check_cmd(char **argv)
{
  char			buff[BUFF_SIZE];
  char			path[BUFF_SIZE];
  char			*paths;

  memset(buff, 0, BUFF_SIZE);
  memset(path, 0, BUFF_SIZE);
  paths = getenv(ENV_PATH);
  if (argv == NULL || argv[0] == NULL)
    sprintf(buff, "ERROR :: No CMD Specified");
  else if (strlen(argv[0]) > 100)
    sprintf(buff, "ERROR :: %s Is Not A Valid CMD", argv[0]);
  else if (access(strcpy(path, argv[0]), F_OK | X_OK) == -1)
    check_with_all_paths(buff, path, paths, argv);
  if (strlen(buff) > 0)
    return (print_error(buff, 0));
  else if (!is_reg_file(buff, path, argv))
    return (print_error(buff, 0));
  if (check_32_64(path) == ERROR)
    return (ERROR);
  get_cmd(SET, path);
  return (OK);
}
