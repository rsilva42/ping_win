NAME = ping_win

CC = /usr/bin/gcc
CCFLAGS = -Wall -Wextra -Werror -I $(INCL)

INCL =	includes
SRCS =	sources/main.c\
		sources/parser.c\
		sources/ping.c\
		sources/print.c\
		sources/errors.c

# substitute "sources/filename.c" to "objects/filename.o"
# where filename is '%'
OBJS =	$(SRCS:sources/%.c=objects/%.o)

.PHONY: all clean fclean re

# default rule, calls $(NAME)
all: $(NAME)

# compile binary
# sets setgid and setuid permissions if user is root
$(NAME): $(OBJS)
	$(CC) $(CCFLAGS) $(OBJS) -o $(NAME)
	@if [ "$(shell /usr/bin/id -u)" -eq "0" ]; \
	then \
		make clean > /dev/null; \
		chmod gu+s $(NAME); \
	fi

# compile object
objects/%.o: sources/%.c
	@/bin/mkdir -p objects
	$(CC) $(CCFLAGS) -c $< -o $@

# delete objects and remove directory if empty
clean:
	/bin/rm -f $(OBJS)
	@if [ -d "objects" ]; \
	then \
		/bin/rmdir --ignore-fail-on-non-empty objects;\
	fi

# delete objects and binary
fclean: clean
	/bin/rm -f $(NAME)

# recompile binary
re: fclean all