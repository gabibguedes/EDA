#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define FILE_NAME "contatos.txt"

typedef struct {
  char name[101];
  char phone[11];
  char address[101];
  unsigned int cep;
  char birthday[11];
  struct Contact *next;
  struct Contact *before;
} Contact;

Contact* read_contact_list();
Contact* insertion_sort(Contact*, Contact*);
void see_all(Contact*);
void menu(Contact*);
void menu_options();

int main() {
 Contact *contatinho;
 contatinho = read_contact_list();
 while(1){
   menu(contatinho);
 }
  return 0;
}

Contact* read_contact_list(){
  Contact *firstContact, *nextContact, *lastContact;
  char dolar;

  FILE *fp;
  fp = fopen(FILE_NAME, "r");
  lastContact = NULL;

  while(!feof(fp)){
    Contact *new_contact;
    new_contact = malloc(sizeof(Contact));

    fscanf(fp, "%[^\n]", new_contact->name);
    getc(fp);
    fscanf(fp, "%s", new_contact->phone);
    getc(fp);
    fscanf(fp, "%[^\n]", new_contact->address);
    fscanf(fp, "%d", &new_contact->cep);
    getc(fp);
    fscanf(fp, "%s", new_contact->birthday);
    getc(fp);
    fscanf(fp, "%c", &dolar);
    getc(fp);

    new_contact->next = NULL;
    new_contact->before = NULL;

    firstContact = insertion_sort(lastContact, new_contact);
    lastContact = new_contact;
  }

  firstContact = firstContact->next;

  fclose(fp);
  return firstContact;
}

Contact* insertion_sort( Contact* reference,  Contact* new_contact){
//This method adds a new contact to the list (in alphabetical order) and
//returns the first element of the list

  Contact *firstContact = reference;
  int searching = 1, bigger = 0, smaller = 0, sameletter = 1, i;

  if (reference == NULL) {
    return new_contact;
  }
  if (new_contact->name[0] > 97) {
    new_contact->name[0] -= 32;
  }
  while(searching){
    sameletter = 1;
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
          reference = reference->next;
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
    return firstContact;
}

void see_all(Contact *contatinho){
  //Method to see all contact in alphabetical order
  int seeing = 1, i=0;
  char input;
  system("clear");

  printf("====== CONTATOS ======\n\n");


  while (contatinho != NULL) {
    printf("%s --",contatinho->name );
    printf(" %s\n", contatinho->phone);

    i++;
    contatinho = contatinho->next;
  }
  while(seeing){
    printf("\n\nAperte M para voltar ao menu inicial\n\n");
    scanf(" %c", &input);
    if (input == 'm' || input == 'M') {
      seeing = 0;
    }else{
      printf("Insira uma opção valida");
    }
  }
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


*/
void menu_options(){
  system("clear");
  printf("======== MENU ========\n\n");
  printf ("Seja bem-vindo a lista telefonica!\n\n");
  printf("1- Inserir novo registro\n");
  printf("2- Remover registro\n");
  printf ("3- Visualizar registro\n");
  printf ("4- Visualizar registros em ordem alfabetica\n");
  printf ("5- Sair\n\n");
}

void menu(Contact *contact_list){
  int value;

  menu_options();
  scanf("%d", &value);

  switch (value){
     case 1:
	    printf("Ainda não implementado:( \n");
      sleep(1);
      menu(contact_list);
      break;

    case 2:
      printf("Ainda não implementado:( \n");
      sleep(1);
      menu(contact_list);
      break;

     case 3:
     printf("Ainda não implementado:( \n");
     sleep(1);
     menu(contact_list);
     break;

    case 4:
	    see_all(contact_list);
      break;

     case 5:
	    exit(-1);
      break;

     default :
      printf ("Por favor, insira uma opcao valida!\n");
  }

}
