CC = gcc
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
FLAGS = -Wall -Wextra 

all: ${OBJS}
	gcc $^ -o vm

%.o: %.c
	${CC} ${FLAGS} -c $^ -o $@

clean:
	rm *.o vm


