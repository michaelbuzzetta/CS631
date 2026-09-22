CC       = cc
C_FILE   = $(wildcard *.c)
TARGET   = $(patsubst %.c,%,$(C_FILE))
CFLAGS   = -O3 -std=c17 -Wall -Werror -pedantic-errors -fmessage-length=0

all:
	$(CC) $(CFLAGS) $(C_FILE) -o $(TARGET)

clean:
	rm -f $(TARGET)