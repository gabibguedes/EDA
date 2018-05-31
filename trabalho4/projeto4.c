#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define TIME_UNITY 5

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
int using_runway(Runway *, Flight *, Flight *);
 void no_fuel(Flight *);

int main() {
	Flight *first_flight = NULL;
	int number_of_flights, arrivals, take_off, wrong_number=1;
	int *p_arrivals, *p_take_off;

	first_flight = (Flight*)(malloc(sizeof(Flight)));
	srand(time(NULL));

	//Estabelecendo número de voos de Aterrisagem e decolagem
	arrivals = (rand() % 23) + 10;
	take_off = (rand() % 23) + 10;
	number_of_flights = take_off + arrivals;

	p_arrivals = (int*)(malloc(sizeof(int)));
	p_take_off = (int*)(malloc(sizeof(int)));

	*p_arrivals = arrivals;
	*p_take_off = take_off;

	printf("arrivals= %d\n", arrivals);
	printf("take_off= %d\n", take_off);
	printf("number_of_flights= %d\n\n", number_of_flights);

	for (int i = 0; i < number_of_flights; i++) {
		set_flight(first_flight, p_arrivals, p_take_off);
	}
	print_flights(first_flight);
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

	if (flight_list == NULL) {
		*flight_list = *new_flight;
	}else{
		include_flight(new_flight, flight_list);
	}

 }

 void print_flights(Flight* first) {
 	Flight* element = first;
	int a=0, d=0;

	while (element !=NULL) {
		printf("code: %s\n", element->code);
		printf("status: %c\n", element->status);
		printf("index: %d\n", element->index);
		printf("fuel: %d\n", element->fuel);
		//
		// if (element->status == 'A') {
		// 	a++;
		// }else if(element->status == 'D'){
		// 	d++;
		// }else{
		// 	printf("Q q tá acontecendu?\n");
		// }
		// printf("As=%d\t Ds=%d\n\n", a,d);
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
	 int time_passed = 0;
	 Flight *airplane = list->next, *managed;
	 Runway *track1, *track2, *track3;

	 int landing = 4 * TIME_UNITY;
	 int taking_off = 2 * TIME_UNITY;

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

		if (track1 != NULL) {
			track1->time_of_use -= TIME_UNITY;
		}
		if (track2 != NULL) {
			track2->time_of_use -= TIME_UNITY;
		}

		 // verifica_zeros --> chamar uma função aki
		 	//no_fuel(airplane);
		 	if (using_runway(track1, airplane, list)){
				printf("\nTRACK1\n");
				printf("\tcode: %s\n", track1->airplane->code);
				printf("\tstatus: %c\n", track1->airplane->status);
				printf("\tindex: %d\n", track1->airplane->index);
				printf("\tfuel: %d\n", track1->airplane->fuel);
				airplane = airplane->next;
			}
		 	if(using_runway(track2, airplane, list)){
				printf("\nTRACK2\n");
				printf("\tcode: %s\n", track2->airplane->code);
				printf("\tstatus: %c\n", track2->airplane->status);
				printf("\tindex: %d\n", track2->airplane->index);
				printf("\tfuel: %d\n", track2->airplane->fuel);
				airplane = airplane->next;
			}
			// if (track3.airplane == NULL) {
			//
			// }





			time_passed += TIME_UNITY;

			if (track1->time_of_use == 0) {
				track1->airplane = NULL;
			}
			if (track2->time_of_use == 0) {
				track2->airplane = NULL;
			}
	}

 }

 int using_runway(Runway *track, Flight *airplane, Flight *list){
	 int landing = 4 * TIME_UNITY;
	 int taking_off = 2 * TIME_UNITY;

	 if (track->airplane == NULL) {
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

 //
 // void track3(){
 //
 // }

 void no_fuel(Flight *first){
	 Flight *element = first->next, *before = first;

	 while (element != NULL) {
	 	if(element->fuel == 0){
			printf("if\n");
			before->next = element->next;
			element->next = first;
			first = element;
			element = before->next;
		}else{
			printf("else\n");
			element = element->next;
		}
	 }
 }

 // int get_hour(){

	// char timeStr[9];
 	// _strtime(timeStr);
 	//  printf( "%s \n", timeStr);

 // }
