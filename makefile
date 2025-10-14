flags = -Llib -Iinclude
srcs = $(wildcard src/*.c)

ldaCds:
	gcc -c $(srcs) $(flags)
	mv *.o build/
	ar rcs build/libldaCds.a $(wildcard build/*.o)

.PHONY: c
c:
	rm build/*.o build/*.a