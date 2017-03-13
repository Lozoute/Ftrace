/*
** elf.c for Ftrace in /home/lks/rendu/AUSP_ftrace
** 
** Made by Thibaud Auzou
** Login   <lks@epitech.net>
** 
** Started on  Sun Jul 12 22:53:24 2015 Thibaud Auzou
** Last update Mon Jul 13 00:29:06 2015 Thibaud Auzou
*/

#include "ftrace.h"

t_elf_list		*g_elf = NULL;

int			init_elf_list(void)
{
  FILE			*file;
  char			b[BUFF_SIZE];
  char			*lib;
  long long unsigned	off;

  sprintf(b, "/proc/%d/maps", get_pid(GET, 0));
  if ((file = fopen(b, "r")) == NULL)
    return (print_error("ERROR [open]: ", 1));
  while (fgets(b,  BUFF_SIZE - 1, file))
    if (strstr(b, ".so"))
      {
	b[strlen(b) - 1] = 0;
	if ((lib = strtok(b, "-")) == NULL)
	  return (print_error("ERROR [strtok, init_elf]", 0));
	off = strtoll(lib, NULL, 16);
	while ((lib = strtok(NULL, " ")))
	  if (strstr(lib, ".so"))
	    {
	      if (open_elf_and_add(lib, off) == ERROR)
		return (ERROR);
	      break ;
	    }
      }
  return (OK);
}

int		open_elf_and_add(char *binary, long long unsigned off)
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
  return (add_elf(data, s.st_size, 1, off));
}

int		add_elf(void *data,
			size_t size,
			int lib,
			long long unsigned off)
{
  t_elf_list	*new;

  if ((new = malloc(sizeof(t_elf_list))) == NULL)
    return (print_error("ERROR [malloc]: ", 1));
  new->_elf = data;
  new->_size = size;
  new->_lib = lib;
  new->_next = g_elf;
  new->_off = off;
  g_elf = new;
  return (OK);
}

void		destroy_elf(void)
{
  t_elf_list	*tmp;
  t_elf_list	*it;

  for (tmp = g_elf; tmp; tmp = it)
    {
      it = tmp->_next;
      free(tmp);
    }
  g_elf = NULL;
}

char		*find_symbol(long long unsigned addr)
{
  t_elf_list	*it;
  char		*sym;

  for (it = g_elf; it; it = it->_next)
    if ((sym = symbol_finder(it->_elf, it->_size, addr, it->_off)) != NULL)
      return (sym);
  return (NULL);
}
