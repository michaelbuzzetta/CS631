CC = cc
CFLAGS = -Wall -Werror

SRCS = $(wildcard *.c)
PROG = $(SRCS:.c=)
OBJS = $(SRCS:.c=.o)

all: $(PROG)

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) -o $(PROG) $(OBJS)

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJS) $(PROG)