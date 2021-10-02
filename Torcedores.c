#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "MonitorBanheiro.h"


void* thread_flamenguista(void *id) // cada flamenguista terá um identificador de 1 a 10
{
	int cont = 0;
	while (cont < 1){
		printf ("Eu sou o(a) flamenguista%d:...Estou apertado(a)! Vou no banheiro!\n",(int)id); 
		flamenguistaQuerEntrar();
		printf ("Eu sou flamenguista-%d: ... UFA! Entrei no banheiro!\n",(int)id);
		sleep(5);
		flamenguistaSai();
		printf ("Eu sou flamenguista-%d: ... Estou aliviado! Vou torcer!\n", (int)id); sleep(5);
		cont++;
	}
}


void* thread_vascaino(void *id) // cada flamenguista terá um identificador de 1 a 10
{
	int cont = 0;
	while (cont < 1){
		printf ("Eu sou o(a) vascaino%d:...Estou apertado(a)! Vou no banheiro!\n",(int)id); 
		vascainoQuerEntrar();
		printf ("Eu sou vascaino-%d: ... UFA! Entrei no banheiro!\n",(int)id);
		sleep(5);
		vascainoQuerSair();
		printf ("Eu sou vascaino-%d: ... Estou aliviado! Vou torcer!\n", (int)id); sleep(5);
		cont++;
	}
}

int main(){

	pthread_t flamenguistaID[5];
	pthread_t vascainoID[5];

	for(int i = 0; i < 5; i++){
		pthread_create(&vascainoID[i], NULL, thread_vascaino, (void*)5+i);
		pthread_create(&flamenguistaID[i], NULL, thread_flamenguista, (void*)i);
	}

	for(int i = 0; i < 5; i++){
		pthread_join(flamenguistaID[i], NULL);
	}
	for(int i = 0; i < 5; i++){
		pthread_join(vascainoID[i], NULL);
	}
	return 0;
}