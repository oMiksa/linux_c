#calcuk:
#	gcc main.c show.c -o calc -L. -lcalc
dll: libadd.so libdivs.so libmult.so libsub.so
libadd.so: add.o 
	gcc -shared add.o -o ./plag/libadd.so
libsub.so: sub.o 
	gcc -shared sub.o -o ./plag/libsub.so
libdivs.so: divs.o 
	gcc -shared divs.o -o ./plag/libdivs.so
libmult.so: mult.o 
	gcc -shared mult.o -o ./plag/libmult.so
add.o:
	gcc -fpic -c add.c
sub.o:
	gcc -fpic -c sub.c
divs.o:
	gcc -fpic -c divs.c
mult.o:
	gcc -fpic -c mult.c
clr:
	rm -f add.o sub.o divs.o mult.o 