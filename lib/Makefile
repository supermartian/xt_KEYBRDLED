GS = -O2 -Wall

all: libipt_KEYBRDLED.so
lib%.so: lib%.o
	gcc -shared -fPIC -o $@ $^;
lib%.o: lib%.c
	gcc ${CFLAGS} -D_INIT=lib$*_init -fPIC -c -o $@ $<;
clean:
	rm -rf *.so
