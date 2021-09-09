CC = gcc
CFLAGS  += -Wall -Werror -Wextra -g3
SANITIZE = -fsanitize=address
MAIN = my_blockchain
SRCS = $(wildcard my_blockchain_src/*.c)
OBJS = $(SRCS:.c=.o)

ALL: $(MAIN)

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) $(SANITIZE) -o $@ $(LINKERFLAG) $^


debugger: $(SRCS)
	$(CC) $(CFLAGS) $(SANITIZE) -g -o $@ $(LINKERFLAG) $(SRCS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(MAIN) $(DEBUG)

re: fclean all
