CC = clang
LIBS = -lm
INCLUDES =
FLAGS = -Wall -Wextra -Werror
BIN = bin/ray_tracer
OBJS = obj/main.o obj/utils.o obj/sphere.o obj/scene.o obj/vector.o

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $^ -o $@ $(FLAGS) $(LIBS)

obj/main.o:   src/main.c   src/scene.h  src/sphere.h src/sphere.h src/utils.h
obj/utils.o:  src/utils.c  src/utils.h
obj/scene.o:  src/scene.c  src/scene.h  src/sphere.h src/utils.h
obj/sphere.o: src/sphere.c src/sphere.h
obj/vector.o: src/vector.c src/vector.h

$(OBJS):
	$(CC) $< -o $@ -c $(FLAGS) $(INCLUDES)

clean:
	rm bin/* obj/*
