#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define TIME_UNITY 5
#define GMT (-3)

typedef struct flight_data {
	char code[7]; //CCIIII
	char status; //A ou D
	int index; //index do código de voo
	int fuel; //Quantidade de combustivel 0 a 12
	struct flight_data *next;
} Flight;

typedef struct runway_data {
	int id; //1, 2 ou 3
	int time_of_use; //quantidade de unidades de tempo
	Flight *airplane; //Avião na pista
} Runway;

Flight set_flight(Flight*, int*, int*);
int choose_index(Flight*);
char flight_status(int*, int*);
int get_fuel();
void include_flight(Flight*, Flight*);
void print_flights(Flight* );
void flight_manager(Flight*);
int using_runway(Runway *, Flight *);
Flight* Check_for_no_fuel(Flight *);
void spending_fuel(Flight *);
void print_action(Runway *, int);
Flight* managing_track3(Runway *, Runway *, Runway *, Flight *, int);
void get_hour(int);
void print_airport(Flight *, int, int, int);
void print_alert_crashing(Flight *, int);
void print_alert_detour(Runway *, int);

int main() {
	Flight *first_flight;
	int number_of_flights, arrivals, take_off, wrong_number=1;
	int *p_arrivals, *p_take_off;

	first_flight = (Flight*)(malloc(sizeof(Flight)));
	first_flight->index = NULL;

	srand(time(NULL));

	//Estabelecendo número de voos de Aterrisagem e decolagem
	arrivals = (rand() % 23) + 10;
	take_off = (rand() % 23) + 10;
	number_of_flights = take_off + arrivals;

	p_arrivals = (int*)(malloc(sizeof(int)));
	p_take_off = (int*)(malloc(sizeof(int)));

	*p_arrivals = arrivals;
	*p_take_off = take_off;

	for (int i = 0; i < number_of_flights; i++) {
		set_flight(first_flight, p_arrivals, p_take_off);
	}
	print_airport(first_flight, number_of_flights, arrivals, take_off);
	flight_manager(first_flight);
	return 0;
}

Flight set_flight(Flight *flight_list, int* arrivals, int* take_off) {
 	Flight *new_flight;
	new_flight = (Flight*)(malloc(sizeof(Flight)));
	int index;

 	char flight_codes[64][7] = {"VG3001\0", "JJ4404\0", "LN7001\0", "TG1501\0", "GL7602\0", "TT1010\0", "AZ1009\0", "AZ1008\0",
													"AZ1010\0", "TG1506\0", "VG3002\0", "JJ4402\0", "GL7603\0", "RL7880\0", "AL0012\0", "TT4544\0",
													"TG1505\0", "VG3003\0", "JJ4403\0", "JJ4401\0", "LN7002\0", "AZ1002\0", "AZ1007\0", "GL7604\0",
													"AZ1006\0", "TG1503\0", "AZ1003\0", "JJ4403\0", "AZ1001\0", "LN7003\0", "AZ1004\0", "TG1504\0",
													"AZ1005\0", "TG1502\0", "GL7601\0", "TT4500\0", "RL7801\0", "JJ4410\0", "GL7607\0", "AL0029\0",
													"VV3390\0", "VV3392\0", "GF4681\0", "GF4690\0", "AZ1020\0", "JJ4435\0", "VG3010\0", "LF0920\0",
													"AZ1065\0", "LF0978\0", "RL7867\0", "TT4502\0", "GL7645\0", "LF0932\0", "JJ4434\0", "TG1510\0",
													"TT1020\0", "AZ1098\0", "BA2312\0", "VG3030\0", "BA2304\0", "KL5609\0", "KL5610\0", "KL5611\0"};

	index = choose_index(flight_list);
	new_flight->index = index;
	strncpy(new_flight->code, flight_codes[index], 7);
	new_flight->status = flight_status(arrivals, take_off);
	new_flight->fuel = get_fuel();
	new_flight->next = NULL;

	if (flight_list->index == NULL) {
		*flight_list = *new_flight;
	}else{
		include_flight(new_flight, flight_list);
	}

}

void print_flights(Flight* first) {
	//[código do voo – P/D – prioridade]
 	Flight* element = first;

	while (element !=NULL) {
		printf("\n\t[Código do vôo: %s - ", element->code);
		if(element->status == 'A'){
			printf(" P - %.2d]", element->fuel);
		}else{
			printf(" D - --]");
		}
		element = element->next;
	}
}

 void include_flight(Flight * new_flight, Flight * list){
	 Flight *element = list;
	 int not_found = 1;

	 while (element != NULL && not_found) {
		 if (element->next == NULL) {
			 element->next = new_flight;
			 not_found = 0;
		 }else{
			 element = element->next;
		 }
	 }
 }

// Function created for choosing a flight on flight_code[64]
 int choose_index(Flight *list){
	 Flight *list_element = list;
	 int index, equal = 1, found;

	 while(equal){
		 index = (rand() % 64);
		 found = 0;
		 while(list_element != NULL){
			 if(index == list_element->index){
				 found = 1;
			 }
			 list_element = list_element->next;
		 }
		 if (found) {
			 equal = 1;
		 }else{
			 equal = 0;
		 }
	 }
	 return index;
 }


char flight_status(int *arrivals, int *take_off) {
	int num;
	char status;
	int n_arrivals = *arrivals, n_take_off = *take_off;

	if (n_take_off == 0 && n_arrivals == 0) {
		printf("ERRO 404: Flight not found\n");
		exit(-1);
	}if (n_take_off == 0) {
	 	status = 'A';
		n_arrivals--;
	}else if(n_arrivals == 0) {
		status = 'D';
		n_take_off--;
	}else{
		num = (rand() % 2);
		if(num == 1){
			status = 'A';
			n_arrivals--;
		}else{
			status = 'D';
			n_take_off--;
		}
	}

	*take_off = n_take_off;
	*arrivals = n_arrivals;
	return status;
 }

int get_fuel() {
	int amount_fuel;
	amount_fuel = (rand() % 13);
	return amount_fuel;
 }

void flight_manager(Flight *list){
	 int time_passed = 0, count =0 ;
	 Flight *airplane = list, *managed;
	 Runway *track1, *track2, *track3;

	 //Iniciando as pistas
	 track1 = (Runway*)(malloc(sizeof(Runway)));
	 track2 = (Runway*)(malloc(sizeof(Runway)));
	 track3 = (Runway*)(malloc(sizeof(Runway)));

	 track1->id = 1;
	 track1->airplane = NULL;

	 track2->id = 2;
	 track2->airplane = NULL;

	 track3->id = 3;
	 track3->airplane = NULL;

	while(airplane != NULL){
		//Diminui o combustivel se passaram 50 min
		if((time_passed != 0) && ((time_passed % 50) == 0)){
			spending_fuel(airplane);
		}

		if (track1->airplane != NULL) {
			track1->time_of_use -= TIME_UNITY;
		}
		if (track2->airplane != NULL) {
			track2->time_of_use -= TIME_UNITY;
		}
		if (track3->airplane != NULL) {
			track3->time_of_use -= TIME_UNITY;
		}
		if (track1->time_of_use == 0) {
			free(track1->airplane);
			track1->airplane = NULL;
		}
		if (track2->time_of_use == 0) {
			free(track2->airplane);
			track2->airplane = NULL;
		}
		if (track3->time_of_use == 0) {
			free(track3->airplane);
			track3->airplane = NULL;
		}

	 // verifica_zeros --> chamar uma função aki
	 airplane = Check_for_no_fuel(airplane);

	 	if (using_runway(track1, airplane)){
			print_action(track1, time_passed);
			airplane = airplane->next;
			count++;
		}
	 	if(using_runway(track2, airplane)){
			print_action(track2, time_passed);
			airplane = airplane->next;
			count++;
		}
		airplane = managing_track3(track3, track2, track1, airplane, time_passed);

		time_passed += TIME_UNITY;
	}
}

void spending_fuel(Flight *	first){
	Flight *element = first;
	while (element != NULL) {
		if (element->status == 'A') {
			element->fuel -= 1;
		}
		element = element->next;
	}
}

int using_runway(Runway *track, Flight *airplane){
	 int landing = 4 * TIME_UNITY;
	 int taking_off = 2 * TIME_UNITY;

	 if (track->airplane == NULL && airplane != NULL) {
		 track->airplane = airplane;
		 if (airplane->status == 'A') {
			 track->time_of_use = landing;
		 }else if(airplane->status == 'D'){
			 track->time_of_use = taking_off;
		 }
		 return 1;
	 }else{
		 return 0;
	 }
 }


 Flight* managing_track3(Runway *track3, Runway *track2, Runway *track1, Flight *airplane, int time_passed){
	 Flight *element, *before;
	 int landing = 4 * TIME_UNITY;
	 int taking_off = 2 * TIME_UNITY;

	 if (airplane != NULL) {
		 //Verifica situação de emergencia
		 if((track1->airplane != NULL) && (track2->airplane != NULL)){
			 if (airplane->status == 'A' && airplane->fuel == 0) {
				 if (track3->airplane == NULL) {
					// pouso de emergência
					track3->airplane = airplane;
					track3->time_of_use = landing;
					print_alert_detour(track3, time_passed);
					airplane = airplane->next;
					return airplane;

				// Verifica se está no tempo de caida de combustivel e se tem tempo para
				//posar no proximo while, ou seja, se é divisivel por 50 ou se o resto dessa
				//divisão é maior que 30(tempo necessário para pouso = 20) o avião cai
				}else if(((time_passed != 0) && ((time_passed % 50) == 0))||
				((time_passed != 0) && ((time_passed % 50) > 30))){
					print_alert_crashing(airplane, time_passed);
					airplane = airplane->next;
					return airplane;
				}
			 }
		 }
		 //Proximo a decolar
		 if(track3->airplane == NULL){
			 //Verifica 1o
			 if(airplane->status == 'D'){
				 track3->airplane = airplane;
				 track3->time_of_use = taking_off;
				 print_action(track3, time_passed);
				 airplane = airplane->next;
				 return airplane;
			 }else if(airplane->next !=NULL){
				 //A partir do 2o
				 element=airplane->next;
				 before = airplane;
				 while (element != NULL) {
					 if(element->status == 'D'){
						 //Se B for = 0, temos que conectar A e C
						 before->next = element->next;//proximo de A = C
						 element->next = airplane;//proximo de B = A
						 airplane = element;//primeiro elemento = B

						 // decola o bixin
						 track3->airplane = airplane;
						 track3->time_of_use = taking_off;
						 print_action(track3, time_passed);
						 airplane = airplane->next;
						 return airplane;

					 }else{
						 before = before->next; //É incrementado para a lista ser percorrida
						 element = element->next; //É incrementado para a lista ser percorrida
					 }
				 }
			 }
		 }
	 }
	 return airplane;
}


Flight* Check_for_no_fuel(Flight *first){
	 Flight *element = first->next; /*Começa a partir do 2o*/
	 Flight *before = first; /*Começa do 1o*/

	 //Vê todos os elementos não nulos
	 while (element != NULL) {
		 //Se o elemento tiver combustivel = 0
		 //Vamos pensar em A B C
		 if((element->fuel == 0) && (element->status == 'A')){
			 //Se B for = 0, temos que conectar A e C
			 before->next = element->next;//proximo de A = C
			 element->next = first;//proximo de B = A
			 first = element;//primeiro elemento = B
			 element = before->next;//proximo elemento a ser tratado = C
			 before = before;
			 //Como o proximo elemento a ser tratado é o proximo do before,
			 //o before continua o mesmo.
		 }else{
			 before = before->next; //É incrementado para a lista ser percorrida
			 element = element->next; //É incrementado para a lista ser percorrida
		 }
	 }
	 return first;
 }

void print_action(Runway *runway, int time_passed){

	printf("\n");
	printf("Código do voo: %s\n", runway->airplane->code);
	printf("Status: ");
	if(runway->airplane->status == 'A'){
		printf("aeronave pousou\n");
	}else{
		printf("aeronave decolou\n");
	}
	printf("Horário do início do procedimento: ");
	get_hour(time_passed);
	// printf("Nivel de combustivel: %d\n", runway->airplane->fuel);
	printf("Número da pista: %d\n", runway->id);
}

void get_hour(int time_passed){
	int hours, min;


	time_t raw_time;
  struct tm *flight_time;
	time ( &raw_time );
  flight_time = gmtime ( &raw_time );

	if (time_passed + flight_time->tm_min >= 60) {
		hours = time_passed/60;
		min = time_passed%60;
	}else{
		hours = 0;
		min = time_passed;
	}
	flight_time->tm_hour = 8 + hours;
	flight_time->tm_min = min;

	printf("%.2d:%.2d\n", flight_time->tm_hour, flight_time->tm_min);

 }

 void print_alert_crashing(Flight *airplane, int time_passed) {
	 printf("\n****************************************\n");
	 printf("****************************************\n");
	 printf("   ALERTA CRÍTICO, AERONAVE IRÁ CAIR   \n");
	 printf("   Hora do alerta: ");
	 get_hour(time_passed);
	 printf("   Código do voo: %s\n", airplane->code);
	 printf("****************************************\n");
	 printf("****************************************\n");
 }
 void print_alert_detour(Runway *track, int time_passed) {
	 printf("\n****************************************\n");
	 printf("   ALERTA GERAL DE DESVIO DE AERONAVE   \n");
	 print_action(track, time_passed);
	 printf("****************************************\n");
 }

 void print_airport(Flight *first_flight, int n_flights, int n_landings, int n_take_offs){
	 printf("|--------------------------------------------|\n");
	 printf("|-----Aeroporto Internacional de Fegahel-----|\n");
	 printf("|--------------------------------------------|\n");
	 printf(" Hora Inicial: ");
	 get_hour(0);
	 printf(" Fila de Pedidos: ");
	 print_flights(first_flight);
	 printf("\n\n");
	 printf(" Número de vôos: %d\n", n_flights);
	 printf(" Número de aproximações: %d\n", n_landings);
	 printf(" Número de decolagens: %d\n", n_take_offs);
	 printf("\n|--------------------------------------------|\n\n");
	 printf("Listagem de eventos: \n");

 }
