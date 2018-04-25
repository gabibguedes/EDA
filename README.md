# Repositório de EDA

## Trabalho 2:

Em nosso trabalho, temos as bibliotecas na pasta lib/, os arquivos .o na pasta obj/  e os executaveis na pasta bin/

##### Para rodar o programa execute:

* Para compilar as bibliotecas:

```
gcc -o obj/file_manipulation.o -c lib/file_manipulation.c
gcc -o obj/bin_operations.o -c lib/bin_operations.c

```

* Para compilar o programa:

```
gcc projeto2.c obj/file_manipulation.o obj/bin_operations.o -o bin/a.out

```

* Para rodar o programa:

```
bin/a.out

```


##### Referência para criação de bibliotecas:

https://www.cs.swarthmore.edu/~newhall/unixhelp/howto_C_libraries.html
