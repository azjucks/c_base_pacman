
CFLAGS=-Wall -Wextra -g
CPPFLAGS=-MMD -Iinclude
LDFLAGS=
LDLIBS= -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

SRCS=$(wildcard src/*.c)
FILES=$(subst src/,,$(SRCS))
OBJS=$(addprefix obj/,$(FILES:.c=.o))

DEPS=$(OBJS:.o=.d)

.PHONY: all clean

all: bin/pacman

-include $(DEPS)

obj/%.o: src/%.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

bin/pacman: $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $@

clean:
	rm -f $(OBJS) $(DEPS) bin/pacman
