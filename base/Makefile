LDFLAGS = -lraylib -lm
#LIBS = 

Compile: main.c
	gcc -o a.out main.c $(LDFLAGS) -g

test: a.out
	./a.out

clean:
	rm -f a.out