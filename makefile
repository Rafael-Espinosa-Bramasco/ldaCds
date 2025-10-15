flags = -Llib -Iinclude
srcs = $(wildcard src/*.c)

ldaCds:
	gcc -c $(srcs) $(flags)
	mv *.o build/
	ar rcs build/libldaCds.a $(wildcard build/*.o)
	cp licence build/licence

.PHONY: c
c:
	rm build/*.o build/*.a build/licence