# Estrutura de Dados 1 - Trabalho 2

##### Discentes
* Felipe Campos de Almeida, 16/0119553
* Gabriela Barrozo Guedes, 16/0121612
* Helena Bretas Goulart, 16/0124034

## Instruções para compilação

A primeira etapa é baixar a biblioteca ncurses.h, como demonstrado abaixo:

```
sudo apt-get install libncurses5-dev
```

Em nosso trabalho, temos as bibliotecas na pasta lib/, os arquivos .o na pasta obj/  e os executaveis na pasta bin/

##### Para rodar o programa execute:

* Para compilar as bibliotecas:

```
gcc -o obj/file_manipulation.o -c lib/file_manipulation.c
gcc -o obj/bin_operations.o -c lib/bin_operations.c
gcc -o obj/ilbp.o -c lib/ilbp.c
gcc -o obj/glcm.o -c lib/glcm.c
gcc -o obj/main_functions.o -c lib/main_functions.c

```

* Para compilar o programa:

```
gcc projeto2.c obj/file_manipulation.o obj/bin_operations.o obj/ilbp.o obj/glcm.o obj/main_functions.o -lncurses -lm -o bin/a.out

```

* Para rodar o programa:

```
bin/a.out

```

##### Referência para criação de bibliotecas:

https://www.cs.swarthmore.edu/~newhall/unixhelp/howto_C_libraries.html
