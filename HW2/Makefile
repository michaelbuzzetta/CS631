CC=cc
CFLAGS=-Wall -Werror -Wextra

PROG=bbcp
SRCS=bbcp.c
OBJS=bbcp.o

all: ${PROG}

${PROG}: ${OBJS}
	${CC} ${CFLAGS} -o ${PROG} ${OBJS}

.c.o:
	${CC} ${CFLAGS} -c ${.IMPSRC}

clean:
	rm -f ${PROG} ${OBJS}