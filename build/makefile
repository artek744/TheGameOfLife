CFLAGS = -Wall -g -I../headers -fopenmp
LDFLAGS = -lX11 -lgomp -pthread -std=c99


SOURCES = $(wildcard ../sources/*.c)

NAME = life-game

OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $(NAME)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS)
	rm -f $(NAME)
