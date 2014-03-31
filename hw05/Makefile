CFLAGS = $(shell pkg-config --cflags glib-2.0)
LIBS = $(shell pkg-config --libs glib-2.0)

all: hello_glib.c
	gcc -o hello_glib hello_glib.c $(CFLAGS) $(LIBS)