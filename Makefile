.PHONY: all test clean pristine

all: testfs

test: testfs.o block.o image.o libvvsfs.a
	gcc -DCTEST_ENABLE -o testfs $^
	./testfs

testfs: testfs.o block.o image.o libvvsfs.a
	gcc -DCTEST_ENABLE -o $@ $^

testfs.o: testfs.c
	gcc -DCTEST_ENABLE -Wall -Wextra -c $^

block.o: block.c block.h
	gcc -Wall -Wextra -c $^

image.o: image.c image.h
	gcc -Wall -Wextra -c $^

inode.o: inode.c inode.h
	gcc -Wall -Wextra -c $^

free.o: free.c free.h
	gcc -Wall -Wextra -c $^

libvvsfs.a: testfs.o block.o image.o inode.o free.o
	ar rcs $@ $^

clean:
	rm -f tesfs.o block.o image.o inode.o free.o

pristine:
	rm -f testfs.o block.o image.o inode.o free.o libvvsfs.a testfs