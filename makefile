CC = gcc
LD = gcc
#CFLAGS = -Wall -Ofast -fopt-info-vec
#CFLAGS = -Wall -O3 -march=native -fopt-info-vec
CFLAGS = -O3
LIBS = -L/opt/X11/lib -lX11
RM = /bin/rm -f

OBJ0 = graphics.o main.o

EXEC = god_mod

god_mod: $(OBJ0)
	$(LD) $(LDFLAGS) $(OBJ0) $(LIBS) -o $(EXEC)


graphics.o: graphics.c graphics.h
	$(CC) $(CFLAGS) $(INCLUDES) -c graphics.c

main.o: main.c graphics.h
	$(CC) $(CFLAGS) $(INCLUDES) -c main.c

clean:
	$(RM) $(EXEC) $(OBJ0)

