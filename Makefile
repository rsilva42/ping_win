NAME = ping_win

CC = /usr/bin/gcc
CCFLAGS = -Wall -Wextra -Werror -I $(INCL)

INCL =	includes
SRCS =	sources/main.c\
		sources/parser.c\
		sources/ping.c\
		sources/print.c\
		sources/errors.c

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

# delete objects
clean:
	/bin/rm -f $(OBJS)

# delete objeects and binary
fclean: clean
	/bin/rm -f $(NAME)

# recompile binary
re: fclean all