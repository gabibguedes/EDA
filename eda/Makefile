all:
	gcc -o obj/file_manipulation.o -c lib/file_manipulation.c
	gcc -o obj/bin_operations.o -c lib/bin_operations.c
	gcc -o obj/ilbp.o -c lib/ilbp.c
	gcc -o obj/glcm.o -c lib/glcm.c
	gcc -o obj/main_functions.o -c lib/main_functions.c
	gcc projeto2.c obj/file_manipulation.o obj/bin_operations.o obj/ilbp.o obj/glcm.o obj/main_functions.o -lncurses -lm -o bin/a.out

.PHONY: clean
clean:
	rm obj/*
	rm bin/*

run:
	bin/a.out
