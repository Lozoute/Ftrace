/*
** ftrace.h for Ftrace in /home/lks/rendu/AILF
** 
** Made by Thibaud Auzou
** Login   <lks@epitech.net>
** 
** Started on  Mon Jul 13 00:48:21 2015 Thibaud Auzou
** Last update Mon Jul 13 00:48:22 2015 Thibaud Auzou
*/

#ifndef STRACE_H_
# define STRACE_H_

# include <sys/user.h>
# include <sys/ptrace.h>
# include <sys/time.h>
# include <sys/reg.h>
# include <sys/resource.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/syscall.h>
# include <sys/mman.h>
# include <linux/futex.h>
# include <sys/time.h>
# include <sys/socket.h>

# include <fcntl.h>
# include <unistd.h>
# include <errno.h>
# include <stdbool.h>
# include <signal.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <strings.h>
# include <ctype.h>
# include <errno.h>
# include <elf.h>
# include <libelf.h>
# include <gelf.h>

/*
** Return Codes
*/
# define OK			0
# define NOK			1
# define ERROR			-1
# define SYSCALL		10
# define CALL			11

/*
** Wrappers Codes
*/
# define GET			0
# define SET			1
# define DESTROY		2
# define CLEAN			3

/*
** Opcodes
*/
# define OP_SYSCALL		0x050F
# define OP_SYSENTER		0x340F
# define OP_INT80		0x80CD
# define OP_CALLN		0xE8
# define OP_CALLF		0xFF
# define OP_REXMIN		0x40
# define OP_REXMAX		0x4F
# define OP_RETN		0xC3
# define OP_RETF		0xCB
# define OP_RETNF		0xC2
# define OP_RETFF		0xCA
# define OP_RETI		0xCF

/*
** Misc
*/
# define PID_OPTION		"-p"
# define BUFF_SIZE		1024
# define ENV_PATH		"PATH"
# define SYSFILE_64		"syscalls/.syscalls_x64"
# define SYSFILE_32		"syscalls/.syscalls_x32"
# define SYSFILE_SEP		";"
# define MAX_ARGS		6
# define MIN_ARGS		0
# define MAX_SYSCALL		360
# define MAX_STR		40

/*
** Colors
*/
# define BLUE			"\x1b[1;34m"
# define RED			"\x1b[1;31m"
# define GREEN			"\x1b[1;32m"
# define YELLOW			"\x1b[1;33m"
# define YOLO			"\x1b[1;36m"
# define C_RESET		"\x1b[0m"

/*
** Why Not
*/
typedef struct user_regs_struct	t_regs;
typedef struct stat		t_stat;
typedef int			(*t_type_func)(unsigned long long int);

/*
** Types
*/
# define STR_TYPES1		"int", "addr", "str", "void", "s_stat", "s_sig",
# define STR_TYPES2		"s_sock", "s_limit", "macro"
# define STR_TYPES		STR_TYPES1 STR_TYPES2
# define NB_TYPES		9

typedef enum			e_type
  {
    INT,
    ADDR,
    STR,
    VOID,
    MACRO,
  }				t_type;

typedef struct			s_enum
{
  int				value;
  char				*name;
}				t_enum;

/*
** Syscall Struct
*/
typedef struct			s_syscall
{
  char				*_name;
  int				_nb_arg;
  t_type			_return_type;
  t_type			*_args_type;
}				t_syscall;

/*
** Macros To String
*/
typedef struct			s_macros
{
  int				_err;
  char				*_str;
}				t_macros;

# define NB_ERRNO		133
extern t_macros			g_errno[NB_ERRNO];

/*
** Word Union
*/
typedef union			u_word
{
  long long int			_word;
  unsigned char			_buff[sizeof(long long unsigned)];
}				t_word;

/*
** Addr Pile
*/
typedef struct			s_pile
{
  unsigned long long		_val;
  unsigned long long		_call;
  struct s_pile			*_next;
}				t_pile;

/*
** Symble Finder Structure
*/
typedef struct			s_info
{
  void				*ehdr;
  size_t			size;
}				t_info;

typedef struct			s_sym
{
  unsigned long long		value;
  unsigned long long		addr;
}				t_sym;

/*
** Graph Datas
*/
typedef enum			e_call_type
  {
    T_CALL,
    T_SYSCALL,
    T_SIGNAL,
  }				t_call_type;

typedef struct			s_call
{
  int				id_child;
  int				counter;
  bool				(*add_call)(struct s_call *, int);
  struct s_call			*next;
}				t_call;

typedef struct			s_file
{
  int				fd;
  bool				(*write_func)(struct s_file *,
					      int,
					      char *,
					      t_call_type);
  bool				(*write_call)(struct s_file *, int, int, int);
  bool				(*close)(struct s_file *);
}				t_file;

typedef struct			s_node
{
  char				*name;
  int				id;
  t_call			*call_list;
  bool				(*add_reference)(struct s_node *, int, int);
  struct s_node			*next;
}				t_node;

typedef struct			s_listcall
{
  t_node			*node;
  struct s_listcall		*next;
  struct s_listcall		*prev;
  bool				(*add_call)(struct s_listcall *, t_node *);
  bool				(*ret_call)(struct s_listcall *);
  bool				(*add_reference)(struct s_listcall *, int);
}				t_listcall;

typedef struct			s_graph
{
  t_node			*func;
  t_file			*file;
  t_listcall			*stack;
  bool				close;
  int				id;
  bool				(*call)(struct s_graph *, char *, t_call_type);
  bool				(*ret)(struct s_graph *);
  bool				(*end)(struct s_graph *);
}				t_graph;

/*
** Elf List
*/
typedef struct			s_elf_list
{
  void				*_elf;
  size_t			_size;
  int				_lib;
  unsigned long long		_off;
  struct s_elf_list		*_next;
}				t_elf_list;

extern t_elf_list		*g_elf;

/*
** Main Functions (main.c)
*/
int				trace_pid(char *);
int				trace_cmd(char **);
int				destroy_ressources(void);
void				control_c(int);

/*
** Errors & Warnings (errors/print_*.c)
*/
int				print_error(const char *, int);
int				print_warning(const char *);

/*
** PID Wrappers (pid/pid.c)
*/
pid_t				get_pid(int, pid_t);

/*
** CMD Wrappers (cmd/cmd.c)
*/
char				*get_cmd(int, char *);
char				**get_argv(int, char **);

/*
** Check Pid (check_pid/check_pid.c)
*/
int				check_pid(char *);
int				check_binary(pid_t);

/*
** Check Cmd (check_cmd/check_cmd.c)
*/
int				check_cmd(char **);

/*
** Check 64 / 32 Bits Version (check_32_64/check_32_64.c)
*/
void				*elf(int, void *);
size_t				elf_size(int, size_t);
int				check_32_64(char *);
int				check_elf(Elf64_Ehdr *);
int				get_mode(int, int);

/*
** Executing CMD (execute/execute.c)
*/
int				execute(char **);

/*
** Tracing PID (trace/trace.c)
*/
int				trace(void);
int				wait_call(t_regs *);
int				is_call(t_regs *, pid_t);
int				print_infos_syscall(t_regs *);
int				get_last_op(int, int);

/*
** Print DetailsSyscall (trace/print_details.c)
**/
int				print_details_syscall(t_regs *,
						      t_syscall *,
						      pid_t);
unsigned long long int		choose_register(t_regs *, int);
void				check_signal(char *, t_regs *);

/*
** Signal Saving (signal/ *.c)
*/
int				save_pid(int, int);
char				*save_signal(int, char *);
char				*save_proc(int, char *);

/*
** Print Args (trace/print_arg.c)
*/
int				print_arg(t_type, unsigned long long int);
int				print_return(t_regs *, t_type, pid_t);

/*
** Display Functions By Type (trace/display_types.c)
*/
int				display_int(unsigned long long int);
int				display_addr(unsigned long long int);
int				display_str(unsigned long long int);
int				display_c(char);
int				display_void(unsigned long long int);
int				display_macro(unsigned long long int);

/*
** Display Struct Types (traces/print_struct.c)
*/
int				display_s_stat(unsigned long long int);
int				display_s_sig(unsigned long long int);
int				display_s_sock(unsigned long long int);
int				display_s_limit(unsigned long long int);

/*
** Attaching and Dettaching (attach/attaching.c)
*/
int				attach(pid_t);
int				dettach(pid_t);
int				dettach_c(pid_t);
int				wrap_attach(int);

/*
** Databases Data (syscalls/databases.c)
*/
int				nb_syscall_64(int);
int				nb_syscall_32(int);
t_syscall			**get_database_64(int);
t_syscall			**get_database_32(int);

/*
** Database Actions (syscalls/syscall_database.c)
*/
t_syscall			*get_syscall(int, int);
int				add_syscall_to_database(t_syscall *, int);
int				destroy_database(void);
int				choose_db(void);

/*
** Database Loading (syscalls/load_*.c)
*/
int				load_syscall_database(char *, int);
int				load_line(char *, int);
int				load_name(char *, t_syscall *);
int				load_return_type(t_syscall *);
t_type				load_type(char *);
int				load_args(t_syscall *);
int				load_nb_args(t_syscall *);
int				load_args_type(t_syscall *);

/*
** Wait Function (wait/wait_for_pid.c)
*/
int				wait_for_pid(pid_t);

/*
** First Param Wrap (trace/first_param_save.c)
*/
long long int			first_param_save(int, long long int);

/*
** First Syscall Display (trace/first_syscall.c)
*/
int				first_syscall(t_regs *);
int				first_syscall_attached(t_regs *);
int				first_syscall_exec(void);

/*
** Get ENUM (trace/get_enum.c)
*/
t_enum				*wrap_enum(int , char *);

/*
** Buffurisation (buff/ *.c)
*/
char				*buffer(int, char *);
int				buffer_init(char **, int *);
int				buffer_cat(char **, int *, char *);
int				buffer_flush(int);
char				*last_call(int, char *);
char				*last_syscall(int, char *);
void				flush_signal(t_graph *);

/*
** Opcodes (opcode/ *.c)
*/
int				decode_opcode(t_regs *, pid_t, t_word *);
int				decode_call(t_regs *,
					    pid_t,
					    t_word *,
					    long unsigned);
int				decode_rex(t_regs *, pid_t, t_word *);
int				decode_ret(void);
int				nb_call(int);
int				nb_undef(int);

/*
** Get Call Details (call/ *.c)
*/
int				get_call(t_regs *,
					 pid_t,
					 t_word *,
					 unsigned long);
int				get_call_near(t_regs *, t_word *);
void				debug_call_near(t_word *,
						int,
						long long int,
						t_regs *);
int				get_call_far(t_regs *, pid_t, t_word *);
int				get_call_rex(t_regs *, pid_t, t_word *);
unsigned long long		choose_reg_call(t_regs *, int);
int				debug_call_far_2(t_word *,
					       t_regs *,
					       unsigned long long,
					       char);
int				get_far_call_2(t_regs *, pid_t, char, t_word *);
unsigned long long		get_far_call_2_dest(t_regs *,
						    pid_t,
						    char,
						    t_word *);
int				get_far_call_3(void);
unsigned long long		add_dest_32(unsigned long long,
					    t_word *,
					    pid_t);
unsigned long long		add_dest_8(unsigned long long,
					   t_word *,
					   pid_t);

/*
** Get Returns Details (return/ *.c)
*/
int				get_return(void);

/*
** Symbole Finder (symbol_finder/ *.c)
*/
char				*symbol_finder(void *, size_t, long long,
					       unsigned long long);

/*
** Debug Mode (debug/ *.c)
*/
int				debug(int);

/*
** Graph Generation (graph/ *.c)
*/
t_graph				*get_graph(int);
t_node				*new_node(char *, int, t_call_type);
t_call				*new_call(int);
t_listcall			*new_listcall(t_node *);
t_graph				*create_graph();
t_file				*create_file();

/*
** Addr Pile (addr/ *.c)
*/
int				add_addr(unsigned long long,
					 unsigned long long);
t_pile				*head_addr(void);
void				pop_addr(void);

/*
** Elf List (elf/ *.c)
*/
int				init_elf_list(void);
int				open_elf_and_add(char *, long long unsigned);
int				add_elf(void *,
					size_t,
					int,
					long long unsigned);
void				destroy_elf(void);
char				*find_symbol(long long unsigned);

#endif /* !STRACE_H_ */
