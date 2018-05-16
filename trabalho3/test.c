#include <stdio.h>
int main(int argc, char const *argv[]) {
  char a = 'b';
  char b = 'a';

  if( a < b ) printf("%c is smaller than %c\n", a, b);
  if( a > b ) printf("%c is grater than %c\n", a, b);
  if( a == b ) printf("%c is equal to %c\n", a, b);

  if (a > b) {
    printf("ok\n");
  }else{
    printf("try again\n");
  }
  return 0;
}
