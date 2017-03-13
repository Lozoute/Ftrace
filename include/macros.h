/*
** macros.h for  in /home/sabbah_j/rendu/TEK2/B4-ADVANCED-PSU/AUSP_ftrace
** 
** Made by jordan sabbah
** Login   <sabbah_j@epitech.net>
** 
** Started on  Sun Jul 12 19:43:45 2015 jordan sabbah
** Last update Sun Jul 12 19:43:45 2015 jordan sabbah
*/

#ifndef MACROS_H_
# define MACROS_H_

/*
** Errno
*/
t_macros		g_errno[NB_ERRNO] =
{
  {EPERM, "EPERM"},
  {ENOENT, "ENOENT"},
  {ESRCH, "ESRCH"},
  {EINTR, "EINTR"},
  {EIO, "EIO"},
  {ENXIO, "ENXIO"},
  {E2BIG, "E2BIG"},
  {ENOEXEC, "ENOEXEC"},
  {EBADF, "EBADF"},
  {ECHILD, "ECHILD"},
  {EAGAIN, "EAGAIN"},
  {ENOMEM, "ENOMEN"},
  {EACCES, "EACCESS"},
  {EFAULT, "EFAULT"},
  {ENOTBLK, "ENOTBLK"},
  {EBUSY, "EBUSY"},
  {EEXIST, "EEXIST"},
  {EXDEV, "EXDEV"},
  {ENODEV, "ENODEV"},
  {ENOTDIR, "ENOTDIR"},
  {EISDIR, "EISDIR"},
  {EINVAL, "EINVAL"},
  {ENFILE, "ENFILE"},
  {EMFILE, "EMFILE"},
  {ENOTTY, "ENOTTY"},
  {ETXTBSY, "ETXTBSY"},
  {EFBIG, "EFBIG"},
  {ENOSPC, "ENOSPC"},
  {ESPIPE, "ESPIPE"},
  {EROFS, "EROFS"},
  {EMLINK, "EMLINK"},
  {EPIPE, "EPIPE"},
  {EDOM, "EDOM"},
  {ERANGE, "ERANGE"},
  {EDEADLK, "EDEADLK"},
  {ENAMETOOLONG, "ENAMETOOLONG"},
  {ENOLCK, "ENOLCK"},
  {ENOSYS, "ENOSYS"},
  {ENOTEMPTY, "ENOTEMPTY"},
  {ELOOP, "ELOOP"},
  {EWOULDBLOCK, "EWOULDBLOCK"},
  {ENOMSG, "ENOMSG"},
  {EIDRM, "EIDRM"},
  {ECHRNG, "ECHRNG"},
  {EL2NSYNC, "EL2NSYNC"},
  {EL3HLT, "EL3HLT"},
  {EL3RST, "EL3RST"},
  {ELNRNG, "ELNRNG"},
  {EUNATCH, "EUNATCH"},
  {ENOCSI, "ENOCSI"},
  {EL2HLT, "EL2HLT"},
  {EBADE, "EBADE"},
  {EBADR, "EBADR"},
  {EXFULL, "EXFULL"},
  {ENOANO, "ENOANO"},
  {EBADRQC, "EBADRQC"},
  {EBADSLT, "EBADSLT"},
  {EDEADLOCK, "EDEADLOCK"},
  {EBFONT, "EBFONT"},
  {ENOSTR, "ENOSTR"},
  {ENODATA, "ENODATA"},
  {ETIME, "ETIME"},
  {ENOSR, "ENOSR"},
  {ENONET, "ENONET"},
  {ENOPKG, "ENOPKG"},
  {EREMOTE, "EREMOTE"},
  {ENOLINK, "ENOLINK"},
  {EADV, "EADV"},
  {ESRMNT, "ESRMNT"},
  {ECOMM, "ECOMM"},
  {EPROTO, "EPROTO"},
  {EMULTIHOP, "EMULTIHOP"},
  {EDOTDOT, "EDOTDOT"},
  {EBADMSG, "EBADMSG"},
  {EOVERFLOW, "EOVERFLOW"},
  {ENOTUNIQ, "ENOTUNIQ"},
  {EBADFD, "EBADFD"},
  {EREMCHG, "EREMCHG"},
  {ELIBACC, "ELIBACC"},
  {ELIBBAD, "ELIBBAD"},
  {ELIBSCN, "ELIBSCN"},
  {ELIBMAX, "ELIBMAX"},
  {ELIBEXEC, "ELIBEXEC"},
  {EILSEQ, "EILSEQ"},
  {ERESTART, "ERESTART"},
  {ESTRPIPE, "ESTRPIPE"},
  {EUSERS, "EUSERS"},
  {ENOTSOCK, "ENOTSOCK"},
  {EDESTADDRREQ, "EDESTADDRREQ"},
  {EMSGSIZE, "EMSGSIZE"},
  {EPROTOTYPE, "EPROTOTYPE"},
  {ENOPROTOOPT, "ENOPROTOOPT"},
  {EPROTONOSUPPORT, "EPROTONOSUPPORT"},
  {ESOCKTNOSUPPORT, "ESOCKTNOSUPPORT"},
  {EOPNOTSUPP, "EOPNOTSUPP"},
  {EPFNOSUPPORT, "EPFNOSUPPORT"},
  {EAFNOSUPPORT, "EAFNOSUPPORT"},
  {EADDRINUSE, "EADDRINUSE"},
  {EADDRNOTAVAIL, "EADDRNOTAVAIL"},
  {ENETDOWN, "ENETDOWN"},
  {ENETUNREACH, "ENETUNREACH"},
  {ENETRESET, "ENETRESET"},
  {ECONNABORTED, "ECONNABORTED"},
  {ECONNRESET, "ECONNRESET"},
  {ENOBUFS, "ENOBUFS"},
  {EISCONN, "EISCONN"},
  {ENOTCONN, "ENOTCONN"},
  {ESHUTDOWN, "ESHUTDOWN"},
  {ETOOMANYREFS, "ETOOMANYREFS"},
  {ETIMEDOUT, "ETIMEDOUT"},
  {ECONNREFUSED, "ECONNREFUSED"},
  {EHOSTDOWN, "EHOSTDOWN"},
  {EHOSTUNREACH, "EHOSTUNREACH"},
  {EALREADY, "EALREADY"},
  {EINPROGRESS, "EINPROGRESS"},
  {ESTALE, "ESTALE"},
  {EUCLEAN, "EUCLEAN"},
  {ENOTNAM, "ENOTNAM"},
  {ENAVAIL, "ENAVAIL"},
  {EISNAM, "EISNAM"},
  {EREMOTEIO, "EREMOTEIO"},
  {EDQUOT, "EDQUOT"},
  {ENOMEDIUM, "ENOMEDIUM"},
  {EMEDIUMTYPE, "EMEDIUMTYPE"},
  {ECANCELED, "ECANCELED"},
  {ENOKEY, "ENOKEY"},
  {EKEYEXPIRED, "EKEYEXPIRED"},
  {EKEYREVOKED, "EKEYREVOKED"},
  {EKEYREJECTED, "EKEYREJECTED"},
  {EOWNERDEAD, "EOWNERDEAD"},
  {ENOTRECOVERABLE, "ENOTRECOVERABLE"},
  {ERFKILL, "ERFKILL"},
  {EHWPOISON, "EHWPOISON"}
};

#endif /* !MACROS_H_ */