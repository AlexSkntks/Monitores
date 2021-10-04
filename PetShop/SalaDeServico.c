#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sala;
sem_t sem_gatos;
sem_t sem_caes;
pthread_mutex_t mutex;

int numeroDeCaesNaFila = 0;
int gatosNaSala = 0;
int qtdGatosNaFila = 0;

int MAXIMO;//Quantidade de cães OU gatos que podem entrar na sala de serviço

void um_gato_quer_servico(){

	qtdGatosNaFila++;

	if(numeroDeCaesNaFila != 0){
		if(gatosNaSala){//Se os gatos estão na sala, esperar por vaga
			sem_wait(&sala);
		}else{//Caso tenha cachorros na fila e a tenha cães na sala, espera que esvazie a fila
			sem_wait(&sem_gatos);
			sleep(2);
			sem_wait(&sala);
		}
	}else{//Se não tem cães na fila, espera uma vaga
		sem_wait(&sala);
	}

	gatosNaSala++;
	qtdGatosNaFila--;

}

void gato_atendido(){

	gatosNaSala--;

	if(numeroDeCaesNaFila){
		if(gatosNaSala == 0){//Libera os cachorros para ocuparem a sala
			for(int i = 0; i < numeroDeCaesNaFila; i++){
				sem_post(&sem_caes);
			}	
		}
	}
	sem_post(&sala);
	
}

void um_cao_quer_servivo(){
	

	numeroDeCaesNaFila++;

	if(gatosNaSala == 0){//Se não tem gatos na sala, espera vaga
		sem_wait(&sala);
	}else{//Se tem gatos na sala, esperar até que possa entrar
		sem_wait(&sem_caes);
		sem_wait(&sala);
	}

}

void cao_atendido(){

	numeroDeCaesNaFila--;

	if(numeroDeCaesNaFila == 0){
		for(int i = 0; i < qtdGatosNaFila; i++){
			sem_post(&sem_gatos);
		}
	}
	sem_post(&sala);
	
}	

int inicializaSala(int maximo, int qtdCaes, int qtdGatos){
	
	MAXIMO = maximo;

	srand(time(NULL));
	pthread_mutex_init(&mutex, NULL);

	if(sem_init(&sem_gatos, 0, 0) == -1){
		return 1;
	}

	if(sem_init(&sem_caes, 0, 0) == -1){
		return 1;
	}

	if(sem_init(&sala, 0, MAXIMO) == -1){
		return 1;
	}

}