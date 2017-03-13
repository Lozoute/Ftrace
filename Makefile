##
## Makefile for  in /home/vieira_q/official_clone/AUSP_strace
## 
## Made by quentin vieira
## Login   <vieira_q@epitech.net>
## 
## Started on  Sat May 16 16:54:02 2015 quentin vieira
## Last update Sun Jul 12 22:55:22 2015 Thibaud Auzou
##

CC		= gcc

RM		= rm -f

CFLAGS		+= -Wextra -Wall -Werror
CFLAGS		+=
CFLAGS		+= -I./include/ -I../include/

LDFLAGS		= -lelf

NAME		= ftrace

SRC		= main.c \
		  errors/print_error.c \
		  errors/print_warning.c \
		  check_pid/check_pid.c \
		  check_cmd/check_cmd.c \
		  check_32_64/check_32_64.c \
		  pid/pid.c \
		  cmd/cmd.c \
		  execute/execute.c \
		  trace/trace.c \
		  trace/print_details.c \
		  trace/print_arg.c \
		  trace/display_types.c \
		  trace/display_str.c \
		  trace/display_struct.c \
		  attach/attaching.c \
		  syscalls/syscall_databse.c \
		  syscalls/databases.c \
		  syscalls/load_database.c \
		  syscalls/load_args.c \
		  wait/wait_for_pid.c \
		  trace/first_param_save.c \
		  trace/first_syscall.c \
		  trace/get_enum.c \
		  buff/buff.c \
		  buff/buff_call.c \
		  opcode/opcode.c \
		  opcode/nb_calls.c \
		  call/call.c \
		  call/call_near.c \
		  call/call_far.c \
		  call/call_far_2.c \
		  call/call_rex.c \
		  return/return.c \
		  symbole_finder/symbol_finder.c \
		  debug/debug.c \
		  graph/graph.c \
		  graph/calls.c \
		  graph/graph_file.c \
		  graph/graph_generator.c \
		  graph/graph_wrap.c \
		  addr/addr.c \
		  signal/signal.c \
		  elf/elf.c

OBJS		= $(SRC:.c=.o)


all: $(NAME)

$(NAME): $(OBJS)
		$(CC) $(OBJS) -o $(NAME) $(CFLAGS) $(LDFLAGS)

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
