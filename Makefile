CC = gcc
CFLAGS = -Wall -Werror -std=c99
SRCS = main.c mem_i.c
OBJS = $(SRCS:.c=.o)
EXEC = memory

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)
