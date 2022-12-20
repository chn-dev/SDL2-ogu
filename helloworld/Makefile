%.o: %.c
	aarch64-linux-gnu-g++ -c $< -o $@ -I../SDL2-ogu/include
	
%: %.o
	aarch64-linux-gnu-g++ $< -o $@ -L../SDL2-ogu/lib -lSDL2 -lSDL2main -lm -lpthread -ldl

all: helloworld

helloworld.o: helloworld.c

helloworld: helloworld.c

clean:
	rm helloworld *.o

