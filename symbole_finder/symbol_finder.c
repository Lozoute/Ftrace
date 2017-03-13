/*
** symbol_finder.c for  in /home/sabbah_j/rendu/TEK2/B4-ADVANCED-PSU/AUSP_ftrace
** 
** Made by jordan sabbah
** Login   <sabbah_j@epitech.net>
** 
** Started on  Sat Jul 11 21:50:15 2015 jordan sabbah
** Last update Mon Jul 13 00:46:31 2015 jordan sabbah
*/

#include "ftrace.h"

static char	*find_sym(Elf_Data *edata,
			  GElf_Shdr *shdr,
			  t_sym const *info,
			  Elf *elf)
{
  int		i;
  int		symbol_count;
  char		*str;
  GElf_Sym	sym;

  symbol_count = shdr->sh_size / shdr->sh_entsize;
  bzero(&sym, sizeof(GElf_Sym));
  for (i = 0; i < symbol_count; i++)
    {
      if (!gelf_getsym(edata, i, &sym))
	return (NULL);
      str = elf_strptr(elf, shdr->sh_link, sym.st_name);
      if (info->value == (sym.st_value + info->addr) && str[0])
	return (strdup(str));
    }
  return (NULL);
}

static char	*find_section_sym(Elf *elf, t_sym const *info)
{
  Elf_Scn	*scn;
  Elf_Data	*edata;
  GElf_Shdr	shdr;

  scn = NULL;
  edata = NULL;
  bzero(&shdr, sizeof(GElf_Shdr));
  while ((scn = elf_nextscn(elf, scn)))
    {
      if (!gelf_getshdr(scn, &shdr))
	return (NULL);
      if (shdr.sh_type == SHT_SYMTAB)
	{
	  if (!(edata = elf_getdata(scn, edata)) && dprintf(2, "error\n"))
	    return (NULL);
	  return (find_sym(edata, &shdr, info, elf));
	}
    }
  return (NULL);
}

char		*symbol_finder(void *data,
			       size_t size,
			       long long value,
			       unsigned long long addr)
{
  Elf		*elf;
  t_sym const	info = {value, addr};

  if (elf_version(EV_CURRENT) == EV_NONE && dprintf(2, "Elf Library\n"))
    return (NULL);
  if (!(elf = elf_memory(data, size)) && dprintf(2, "error in elf_memory\n"))
    return (NULL);
  return (find_section_sym(elf, &info));
}
