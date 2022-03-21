CC = clang
LIBS = -lm
INCLUDES =
FLAGS = -Wall -Wextra -Werror -Wno-unused-parameter -Wno-unused-variable
BIN = bin/ray_tracer
OBJS = obj/main.o obj/hittable.o obj/scene.o obj/utils.o obj/vector.o

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $^ -o $@ $(FLAGS) $(LIBS)

obj/main.o:   	src/main.c                 			src/scene.h  src/hittable.h src/utils.h
obj/hittable.o: src/hittable.c 	src/hittable.h  src/colour.h src/vector.h
obj/scene.o:  	src/scene.c  		src/scene.h   	src/utils.h
obj/utils.o:  	src/utils.c  		src/utils.h   	src/colour.h src/scene.h
obj/vector.o: 	src/vector.c 		src/vector.h

$(OBJS):
	$(CC) $< -o $@ -c $(FLAGS) $(INCLUDES)

clean:
	rm -f bin/* obj/*
