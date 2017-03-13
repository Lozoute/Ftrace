/*
** symbol_finder.h for  in /home/sabbah_j/rendu/TEK2/B4-ADVANCED-PSU/AUSP_ftrace/symbole_finder
** 
** Made by jordan sabbah
** Login   <sabbah_j@epitech.net>
** 
** Started on  Thu Jul  9 23:47:55 2015 jordan sabbah
** Last update Mon Jul 13 00:46:07 2015 jordan sabbah
*/

#ifndef SYMBOL_FINDER_H_
# define SYMBOL_FINDER_H_

# include <stdlib.h>

typedef struct		s_sym
{
  unsigned long long	value;
  unsigned long long	addr;
}			t_sym;

char		*symbol_finder(void *, size_t, long long, unsigned long long);

#endif /* !SYMBOL_FINDER_H_ */
