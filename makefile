CFLAGS=	-c -std=c99 -Wall -Wextra

all: base

global.o: global.c
	gcc $(CFLAGS) $^

deplacements.o: deplacements.c
	gcc $(CFLAGS) $^

initialisation.o: initialisation.c
	gcc $(CFLAGS) $^

test.o: test.c
	gcc $(CFLAGS) $^

sauvegarde.o: sauvegarde.c
	gcc $(CFLAGS) $^

base: global.o deplacements.o initialisation.o test.o sauvegarde.o
	gcc -o projet $^

exe: base
	./projet

clean:
	rm -f *.o
	rm -f projet

add:
	git add *.c
	git add makefile
	git add projet
	git add sauvegarde.txt
	git add	ToDoList.txt
	git add README.txt
	git commit
	git push

sync:
	git fetch origin
	git merge origin/master
