/*
** main.c for  in /home/sabbah_j/rendu/TEK2/B4-ADVANCED-PSU/AUSP_ftrace/symbole_finder
** 
** Made by jordan sabbah
** Login   <sabbah_j@epitech.net>
** 
** Started on  Sat Jul 11 13:28:24 2015 jordan sabbah
** Last update Sun Jul 12 19:58:35 2015 jordan sabbah
*/

#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>
#include <unistd.h>
#include "symbol_finder.h"
#include "test.h"

static size_t	filesize(int fd)
{
  size_t	size;

  if ((size = lseek(fd, 0, SEEK_END)) == (size_t)-1)
    return (-1);
  if (lseek(fd, 0, SEEK_SET) == (off_t)-1)
    return (-1);
  return (size);
}

static int	file_init(t_info *info, char *file)
{
  int		fd;
  size_t	size;
  void		*data;

  if ((fd = open(file, O_RDONLY)) == -1)
    return (dprintf(2, "error open in file_init\n"));
  if ((size = filesize(fd)) <= (size_t)0)
    {
      close(fd);
      return (dprintf(2, "error filesize in file_init\n"));
    }
  if ((data = mmap(NULL, size, PROT_READ, MAP_SHARED, fd, 0)) == MAP_FAILED)
    {
      close(fd);
      return (dprintf(2, "error mmap failed in file_init\n"));
    }
  info->ehdr = data;
  info->size = size;
  close(fd);
  return (0);
}

int		main(int ac, char **av)
{
  long		value;
  char		*str;
  t_info	info;

  if (ac < 3)
    return (dprintf(2, "./a.out file address\n"));
  if (!(value = strtol(av[2], NULL, 16)))
    return (dprintf(2, "./a.out file 0xaddress\n"));
  if (file_init(&info, av[1]) && dprintf(2, "error file_init\n"))
    return (EXIT_FAILURE);
  if (!(str = symbol_finder(info.ehdr, info.size, value)))
    return (EXIT_FAILURE);
  printf("symbol = '%s'\n", str);
  free(str);
  munmap(info.ehdr, info.size);
  return (EXIT_SUCCESS);
}
