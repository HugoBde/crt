CC = clang
LIBS =
INCLUDES =
FLAGS = -Wall -Wextra -Werror -ansi
BIN = bin/ray_tracer
OBJS = obj/main.o

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $^ -o $@ $(FLAGS) $(LIBS)

obj/main.o: src/main.c

$(OBJS):
	$(CC) $< -o $@ -c $(FLAGS) $(INCLUDES)

clean:
	rm bin/* obj/*