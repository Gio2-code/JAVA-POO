link: main.o
	gcc main.o -o a.exe -lm

main.o:
	gcc -c main.c

clean:
	rm -f *.o *.exe
