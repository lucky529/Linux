libmymath.so:mymath.o
gcc -shared -o libmymath.so mymath.o
mymath.o:mymath.c
	gcc -fPIC -c mymath.c

.PHONY:output
output:
	mkdir -p lib/lib
	mkdir -p lib/include
	cp -rf *.h lib/include
	cp -rf *.so lib/lib

.PHONY:clean
clean:
	rm -f *.o *.so lib
