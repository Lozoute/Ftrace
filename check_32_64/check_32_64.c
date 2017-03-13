/*
** check_32_64.c for strace in /home/lks/rendu/AUSP_strace
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Thu May  7 20:03:29 2015 Thibaud Auzou
** Last update Mon Jul 13 00:15:34 2015 Thibaud Auzou
*/

#include "ftrace.h"

void		*elf(int action, void *val)
{
  static void	*_elf = NULL;

  if (action == SET && val)
    _elf = val;
  return (_elf);
}

size_t		elf_size(int action, size_t val)
{
  static size_t	_size = 0;

  if (action == SET)
    _size = val;
  return (_size);
}

int		check_32_64(char *binary)
{
  int		fd;
  void		*data;
  t_stat	s;

  if ((fd = open(binary, O_RDONLY)) == -1)
    return (print_error("ERROR [open] :", 1));
  if (fstat(fd, &s) == -1)
    return (print_error("ERROR [fstat] :", 1));
  if (s.st_size < (int)sizeof(Elf64_Ehdr) &&
      s.st_size < (int)sizeof(Elf32_Ehdr))
    return (print_error("ERROR :: bad elf file", 0));
  if ((data = mmap(NULL, s.st_size, PROT_READ, MAP_SHARED, fd, 0)) == NULL)
    return (print_error("ERROR [mmap] :", 1));
  else if (data == (void *)(0xffffffffffffffff))
    return (print_error("ERROR [mmap] :: bad elf", 0));
  elf(SET, data);
  elf_size(SET, s.st_size);
  if (add_elf(data, s.st_size, 0, 0) == ERROR)
    return (ERROR);
  return (check_elf((Elf64_Ehdr *)(data)));
}

int		check_elf(Elf64_Ehdr *data)
{
  if (data->e_ident[4] == ELFCLASS32)
    get_mode(SET, 32);
  else
    get_mode(SET, 64);
  return (OK);
}

int		get_mode(int action, int new_mode)
{
  static int	_mode = 0;

  if (action == SET && new_mode != 0)
    _mode = new_mode;
  return (_mode);
}
