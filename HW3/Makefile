CC=cc
CFLAGS=-Wall -Werror -Wextra

PROG=userinfo
SRCS=userinfo.c
OBJS=userinfo.o

all: ${PROG}

${PROG}: ${OBJS}
	${CC} ${CFLAGS} -o ${PROG} ${OBJS}

.c.o:
	${CC} ${CFLAGS} -c ${.IMPSRC}

clean:
	rm -f ${PROG} ${OBJS}