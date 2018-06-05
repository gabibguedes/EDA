#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define FILE_NAME "contatosiug.txt"

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
void add_contact(Contact *);
void search_contact(Contact*);
void print_addres(Contact*);
void remove_contact(Contact*);
void new_file(Contact*);

int main() {
 Contact *contatinho;
 contatinho = read_contact_list();
  menu(contatinho);

  return 0;
}
void print_addres(Contact* firstContact){
  Contact * first = firstContact;
  while (first != NULL) {
    printf("%s\n", first->name);
    printf("end. anterior: %p\n", first->before);
    printf("end. atual:    %p\n", first);
    printf("end. proximo:  %p\n\n", first->next);
    first = first->next;
  }
}


Contact* read_contact_list(){
  Contact *firstContact, *lastContact;
  char dolar;

  FILE *fp;
  fp = fopen(FILE_NAME, "a+");

  lastContact = NULL;
  firstContact = NULL;

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
  fclose(fp);

  if ((firstContact->name == NULL ) || !(strcmp(firstContact->name, "")) ){
    firstContact = firstContact->next;
    firstContact->before = NULL;
  }
  Contact * last = firstContact, *c;
  while (last->next != NULL) {
    if ((last->phone == NULL ) || (!strcmp(last->phone, ""))) {
      c = last->next;
      last = last->before;
      last->next = c;
    }
    last = last->next;
  }
  if ((last->phone == NULL ) || (!strcmp(last->phone, ""))) {
    last = last->before;
    last->next = NULL;
  }

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

void see_all(Contact *contact_list){
  //Method to see all contact in alphabetical order
  int seeing = 1, i=0;
  char input;
  contact_list = read_contact_list();
  Contact *contact = contact_list;
  system("clear");

  printf("====== CONTATOS ======\n\n");

  if (contact_list == NULL) {
    printf("\n\nVocê ainda não possui contatos :(\n");
  }

  while (contact != NULL) {
    printf("%s --",contact->name );
    printf(" %s\n", contact->phone);

    i++;
    contact = contact->next;
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
  menu(contact_list);
}
void add_contact(Contact *contact_list){
  //Method to add a new contact to the list
  Contact new_contact, *firstContact;

  new_contact.next = NULL;
  new_contact.before = NULL;

  system("clear");
  printf("==== NOVO CONTATO ====\n\n");
  getchar();
  printf("Nome: ");
  scanf("%[^\n]", new_contact.name);
  getchar();

  printf("Telefone (XXXXX-XXXX): ");
  scanf("%s", new_contact.phone);
  getchar();

  printf("Endereço: ");
  scanf("%[^\n]", new_contact.address);

  printf("Cep: ");
  scanf("%d", &new_contact.cep);

  getchar();
  printf("Aniversário (DD/MM/AAAA): ");
  scanf("%[^\n]", new_contact.birthday);

  insertion_sort(contact_list, &new_contact);

  FILE *fp;
  fp = fopen(FILE_NAME, "a+");
  fprintf(fp, "%s\n", new_contact.name);
  fprintf(fp, "%s\n", new_contact.phone);
  fprintf(fp, "%s\n", new_contact.address);
  fprintf(fp, "%d\n", new_contact.cep);
  fprintf(fp, "%s\n", new_contact.birthday);
  fprintf(fp, "$\n");
  fclose(fp);
  firstContact = read_contact_list();
  menu(firstContact);

}

void search_contact(Contact *contact_list){
  //Method to serch and show the contacts with the selected name
  Contact *selected = contact_list;
  char name[101], input;
  int seeing=1, found=0;

  system("clear");
  printf("=== BUSCAR CONTATO ===\n\n");
  getchar();
  printf("Nome: ");
  scanf("%[^\n]", name);
  getchar();

  while(selected != NULL){
    if (!strcmp(selected->name, name)) {
      printf("\n\n%s\n", selected->name);
      printf("%s\n", selected->phone);
      printf("Endereço: ");
      printf("%s\n", selected->address);
      printf("CEP: ");
      printf("%d\n", selected->cep);
      printf("Aniversário: ");
      printf("%s\n", selected->birthday);
      found = 1;
    }
    selected = selected->next;
  }

  if(!found){
    printf("\n\nERRO 404 Contato não encontrado :(\n");
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
  menu(contact_list);
}

void remove_contact(Contact *contact_list){
  //Method to remove a contact from the list
  char name[101], answer;
  Contact *selected = contact_list, *neighbor;
  int removed=0, seeing=1;

  system("clear");
  printf("=== REMOVER CONTATO ==\n\n");
  printf("Nome: ");
  getchar();
  scanf("%[^\n]", name);
  getchar();

  while(selected != NULL){
    if (!strcmp(selected->name, name)) {
      strcpy(selected->name, "");
      strcpy(selected->phone, "");
      strcpy(selected->address, "");
      strcpy(selected->birthday, "");

      if (selected->before != NULL) {
        neighbor = selected->before;
        neighbor->next = selected->next;
      }else if(selected->before == NULL){
        contact_list = selected->next;
        contact_list->before = NULL;
      }

      if (selected->next != NULL) {
        neighbor = selected->next;
        neighbor->before = selected->before;
      }
      free(selected);
      removed ++;
    }
    selected = selected->next;
  }
  if(removed == 0){
    printf("\n\nERRO 404 Contato não encontrado!\n");
    sleep(2);
  }else{

    while(seeing){
      printf("\n\nDeseja mesmo remover %d contato(s)? (S/N)\n", removed);
      scanf("%c", &answer);
      if (answer == 's' || answer == 'S') {
        new_file(contact_list);

        printf("\nContato(s) removido(s) com sucesso!\n");
        sleep(2);
        seeing = 0;
      }else if(answer == 'n' || answer == 'N'){
        printf("\nOperação cancelada.\n");
        sleep(2);
        seeing = 0;
      }else{
        printf("\n\nInsira uma opção valida\n");
      }
    }
  }
  contact_list = read_contact_list();
  menu(contact_list);
}

void new_file(Contact * contact_list){
  Contact *new_contact = contact_list, *c;
  FILE *fp;
  fp = fopen(FILE_NAME, "w+");
  while (new_contact != NULL) {
    if ((new_contact->phone == NULL ) || (!strcmp(new_contact->phone, ""))) {
      c = new_contact->next;
      new_contact = new_contact->before;
      new_contact->next = c;
    }
    fprintf(fp, "%s\n", new_contact->name);
    fprintf(fp, "%s\n", new_contact->phone);
    fprintf(fp, "%s\n", new_contact->address);
    fprintf(fp, "%d\n", new_contact->cep);
    fprintf(fp, "%s\n", new_contact->birthday);
    fprintf(fp, "$\n");
    new_contact = new_contact->next;
  }
  fclose(fp);
}

void menu_options(){
  system("clear");
  printf("======== MENU ========\n\n");
  printf ("Seja bem-vindo a lista telefonica!\n\n");
  printf("1- Inserir novo registro\n");
  printf("2- Remover registro\n");
  printf ("3- Visualizar registro selecionado\n");
  printf ("4- Visualizar registros em ordem alfabetica\n");
  printf ("5- Sair\n\n");
}

void menu(Contact *contact_list){
  int value;

  menu_options();
  scanf("%d", &value);

  switch (value){
     case 1:
	    add_contact(contact_list);
      break;

    case 2:
      remove_contact(contact_list);
      break;

     case 3:
     search_contact(contact_list);
     break;

    case 4:
	    see_all(contact_list);
      break;

     case 5:
	    exit(-1);
      break;

     default :
      printf ("Por favor, insira uma opcao valida!\n");
      getchar();
      sleep(2);
      menu(contact_list);
      break;
  }

}
