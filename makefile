CC    = gcc
FLAGS = -Wall -pthread

all: tcpchat

tcpchat: main.c net/net.c chat/chat.c db/db.c ui/ui.c
	$(CC) $(FLAGS) -o tcpchat \
		main.c net/net.c chat/chat.c db/db.c ui/ui.c \
		-lsqlite3

clean:
	rm -f tcpchat chat.db