calcuk: libcalcul.a
	gcc main.c show.c -o calcul -L. -lcalcul
libcalcul.a: add.o ded.o div.o mult.o libcalc.h 
	ar -rc libcalcul.a add.o ded.o div.o mult.o
add.o:
	gcc -c add.c
ded.o:
	gcc -c ded.c
div.o:
	gcc -c div.c
mult.o:
	gcc -c mult.c
clean:
	rm -f libcalcul.a add.o ded.o div.o mult.o 