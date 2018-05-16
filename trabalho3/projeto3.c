#include <stdio.h>
#include <stdlib.h>
#define FILE_NAME "contatos2.txt"

typedef struct {
  char name[101];
  char phone[11];
  char address[101];
  unsigned int cep;
  char birthday[11];
  struct Contact *next;
  struct Contact *before;
} Contact;

Contact read_contact_list();
Contact* insertion_sort(Contact*, Contact*);
void see_all(Contact*);

int main() {
/*
  while(1){
    menu();
  }
*/
printf("1\n");
 Contact contatinho, *contatinho2;
 printf("2\n");
 contatinho = read_contact_list();
 printf("4\n");



  return 0;
}

Contact read_contact_list(){
  Contact *firstContact, nextContact, lastContact;
  char dolar;

  FILE *fp;
  fp = fopen(FILE_NAME, "r");

  fscanf(fp, "%[^\n]", lastContact.name);
  getc(fp);
  fscanf(fp, "%s", lastContact.phone);
  getc(fp);
  fscanf(fp, "%[^\n]", lastContact.address);
  fscanf(fp, "%d", &lastContact.cep);
  getc(fp);
  fscanf(fp, "%s", lastContact.birthday);
  getc(fp);
  fscanf(fp, "%c", &dolar);
  getc(fp);

  printf("NOME: %s\n",lastContact.name );
  printf("TELEFONE: %s\n", lastContact.phone);
  printf("ENDEREÇO: %s\n", lastContact.address);
  printf("CEP: %d\n", lastContact.cep);
  printf("ANIVERSÁRIO: %s\n\n", lastContact.birthday);


  lastContact.next = NULL;
  lastContact.before = NULL;

  //while(!feof(fp)){
    fscanf(fp, "%[^\n]", nextContact.name);
    getc(fp);
    fscanf(fp, "%s", nextContact.phone);
    getc(fp);
    fscanf(fp, "%[^\n]", nextContact.address);
    fscanf(fp, "%d", &nextContact.cep);
    getc(fp);
    fscanf(fp, "%s", nextContact.birthday);
    getc(fp);
    fscanf(fp, "%c", &dolar);
    getc(fp);

    nextContact.next = NULL;
    nextContact.before = NULL;

    printf("NOME: %s\n",nextContact.name );
    printf("TELEFONE: %s\n", nextContact.phone);
    printf("ENDEREÇO: %s\n", nextContact.address);
    printf("CEP: %d\n", nextContact.cep);
    printf("ANIVERSÁRIO: %s\n\n", nextContact.birthday);

    firstContact = insertion_sort(&lastContact, &nextContact);
    lastContact = nextContact;
   //}

  fclose(fp);
  see_all(firstContact);

  return *firstContact;
}

Contact* insertion_sort( Contact* old_contact,  Contact* new_contact){
//This method adds a new contact to the list (in alphabetical order) and
//returns the first element of the list

  Contact *reference = old_contact, *firstContact = old_contact, *before, *next;
  int searching = 1, bigger = 0, smaller = 0, sameletter = 1, i;

  if (new_contact->name[0] > 97) {
    new_contact->name[0] -= 32;
  }

  while(searching){
    if (reference->name[0] > 97) {
      reference->name[0] -= 32;
    }
    i=0;
    while (sameletter) {

      if (reference->name[i] > new_contact->name[i]) {
        sameletter = 0;
        smaller = 1;
        if ((smaller && bigger) || (smaller && reference->before == NULL)) {
          searching = 0;
          new_contact->before = reference->before;
          new_contact->next = reference;
          reference->before = new_contact;

          if(new_contact->before != NULL){
            reference = new_contact->before;
            reference->next = new_contact;
          }
        }else{
          reference = reference->before;
        }
      }else if(reference->name[i] < new_contact->name[i]){
        sameletter = 0;
        bigger = 1;
        printf("%d e %d\n",smaller, bigger );
        if ((smaller && bigger) || (bigger && reference->next == NULL)) {
          searching = 0;
          new_contact->next = reference->next;
          new_contact->before = reference;
          reference->next = new_contact;

          if(new_contact->next != NULL){
            reference = new_contact->next;
            reference->before = new_contact;
          }
        }else{
          reference = reference->before;
        }
      }
      i++;
    }
  }
  searching = 1;
  while (searching) {
    if(reference->before == NULL){
      searching = 0;
      firstContact = reference;
    }else{
      reference = reference->before;
    }
  }
  //see_all(firstContact);

  return firstContact;
}

void see_all(Contact *contatinho){
  //Method to see all contact in alphabetical order
  while (contatinho->next != NULL) {
    printf("endereço da variavel: %p\n", contatinho);
    printf("NOME: %s\n",contatinho->name );
    printf("TELEFONE: %s\n", contatinho->phone);
    printf("ENDEREÇO: %s\n", contatinho->address);
    printf("CEP: %d\n", contatinho->cep);
    printf("ANIVERSÁRIO: %s\n", contatinho->birthday);
    printf("next: %p\n", contatinho->next);
    printf("before: %p\n\n", contatinho->before);

    contatinho = contatinho->next;
  }

  printf("NOME: %s\n",contatinho->name );
  printf("TELEFONE: %s\n", contatinho->phone);
  printf("ENDEREÇO: %s\n", contatinho->address);
  printf("CEP: %d\n", contatinho->cep);
  printf("ANIVERSÁRIO: %s\n", contatinho->birthday);
  printf("next: %p\n", contatinho->next);
  printf("before: %p\n", contatinho->before);

}
/*
void add_contact( Contact new_contact){
  //Method to add a new contact to the list
}

void remove_contact(char name[100]){
  //Method to remove a contact from the list
}

void search_contact(char name[100]){
  //Method to serch and show the contacts with the selected name
}


void menu_options(){
  system("clear");
  printf ("Seja bem-vindo a lista telefonica!\n\n");
  printf("====== MENU ======\n");
  printf("1- Inserir novo registro\n");
  printf("2- Remover registro\n");
  printf ("3- Visualizar registro\n");
  printf ("4- Visualizar registros em ordem alfabetica\n");
  printf ("5- Sair\n");
}

void menu(){
  int value;

  menu_options();
  scanf("%d", &value);

  switch (value){
     case 1:
	    // chamada da funcao
      break;

     case 2:
	    // chamada da funcao
      break;

     case 3:
	    // chamada da funcao
      break;

    case 4:
	    // chamada da funcao
      break;

     case 5:
	    exit(-1);
      break;

     default :
      printf ("Por favor, insira uma opcao valida!\n");
  }

}
*/
