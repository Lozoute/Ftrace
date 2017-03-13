/*
** enum.h for  in /home/vieira_q/official_clone/AUSP_strace/include
** 
** Made by quentin vieira
** Login   <vieira_q@epitech.net>
** 
** Started on  Fri May 15 17:37:22 2015 quentin vieira
** Last update Sat Jul 11 14:43:17 2015 Thibaud Auzou
*/

#ifndef ENUM_H_
# define ENUM_H_

# include "ftrace.h"

t_enum		g_open_enum[] =
  {
    {O_WRONLY, "O_WRONLY"},
    {O_RDWR, "O_RDWR"},
    {O_RDONLY, "O_RDONLY"},
    {O_ACCMODE, "O_ACCMODE"},
    {O_CREAT, "O_CREAT"},
    {O_APPEND, "O_APPEND"},
    {O_ASYNC, "O_ASYNC"},
    {O_CLOEXEC, "O_CLOEXEC"},
    {O_DIRECTORY, "O_DIRECTORY"},
    {O_EXCL, "O_EXCL"},
    {O_NOCTTY, "O_NOCTTY"},
    {O_NOFOLLOW, "O_NOFOLLOW"},
    {O_NONBLOCK, "O_NONBLOCK"},
    {O_SYNC, "O_SYNC"},
    {O_TRUNC, "O_TRUNC"},
    {0, NULL}
  };

t_enum		g_futex_enum[] =
  {
    {FUTEX_WAKE, "FUTEX_WAKE"},
    {FUTEX_FD, "FUTEX_FD"},
    {FUTEX_WAIT, "FUTEX_WAIT"},
    {FUTEX_CMP_REQUEUE, "FUTEX_CMP_REQUEUE"},
    {FUTEX_REQUEUE, "FUTEX_REQUEUE"},
    {0, NULL},
  };

t_enum		g_mmap_enum[] =
  {
    {MAP_SHARED, "MAP_SHARED"},
    {MAP_PRIVATE, "MAP_PRIVATE"},
    {MAP_32BIT, "MAP_32BIT"},
    {MAP_ANONYMOUS, "MAP_ANONYMOUS"},
    {MAP_DENYWRITE, "MAP_DENYWRITE"},
    {MAP_FIXED, "MAP_FIXED"},
    {MAP_GROWSDOWN, "MAP_GROWSDOWN"},
    {MAP_HUGETLB, "MAP_HUGETLB"},
    {MAP_LOCKED, "MAP_LOCKED"},
    {MAP_NONBLOCK, "MAP_NONBLOCK"},
    {MAP_NORESERVE, "MAP_NORESERVE"},
    {MAP_POPULATE, "MAP_POPULATE"},
    {MAP_STACK, "MAP_STACK"},
    {0, NULL}
  };

t_enum		g_mmap_enum2[] =
  {
    {PROT_EXEC, "PROT_EXEC"},
    {PROT_READ, "PROT_READ"},
    {PROT_WRITE, "PROT_WRITE"},
    {0, NULL}
  };

t_enum		g_access_enum[] =
  {
    {R_OK, "R_OK"},
    {W_OK, "W_OK"},
    {X_OK, "X_OK"},
    {0, NULL}
  };

t_enum		g_socket_enum[] =
  {
    {SOCK_STREAM, "SOCK_STREAM"},
    {SOCK_DGRAM, "SOCK_DGRAM"},
    {SOCK_SEQPACKET, "SOCK_SEQPACKET"},
    {SOCK_RAW, "SOCK_RAW"},
    {SOCK_RDM, "SOCK_RDM"},
    {SOCK_PACKET, "SOCK_PACKET"},
    {SOCK_NONBLOCK, "SOCK_NONBLOCK"},
    {SOCK_CLOEXEC, "SOCK_CLOEXEC"},
    {0, NULL}
  };

typedef struct	s_list
{
  char		*syscall;
  t_enum	*tab;
}		t_list;

t_list		g_list_enum[] =
  {
    {"open", g_open_enum},
    {"mmap", g_mmap_enum},
    {"mmap2", g_mmap_enum},
    {"access", g_access_enum},
    {"futex", g_futex_enum},
    {"socket", g_socket_enum},
    {NULL, NULL}
  };

#endif /* !ENUM_H_ */
