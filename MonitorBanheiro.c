#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "MonitorBanheiro.h"

char flag = 'n';//F ou V indica qual time está no banheiro atualmente
int pessoasNoBanheiro = 0;//Quantidade de pessoas no banheiro
int temFlamenguistaNaFila = 0;
pthread_cond_t vaga;// Todas as threads ficam paradas até que tenha uma vaga no banheiro

pthread_cond_t vascainoPodeEntrar;
pthread_cond_t flamenguistaPodeEntrar;

pthread_mutex_t mutex;

void flamenguistaQuerEntrar(){
	pthread_mutex_lock(&mutex);
	
	if(flag == 'n'){//Flamenguistas entram primeiro no banheiro
		flag = 'f';
	}else if(flag == 'f'){

		if(pessoasNoBanheiro == 3){
			temFlamenguistaNaFila++;
			pthread_cond_wait(&vaga, &mutex);
			temFlamenguistaNaFila--;
		}
		
	}else{//Se o time no banheiro for vasco, flamenguista espera até poder entrar
		temFlamenguistaNaFila++;
		pthread_cond_wait(&flamenguistaPodeEntrar, &mutex);
		temFlamenguistaNaFila--;
		flag = 'f';
	}
	
	pessoasNoBanheiro++;
	pthread_mutex_unlock(&mutex);
}

void flamenguistaSai(){
	pthread_mutex_lock(&mutex);

	pessoasNoBanheiro--;
	pthread_cond_signal(&vaga);//Libera uma vaga para alguém entrar

	if(temFlamenguistaNaFila == 0 && pessoasNoBanheiro == 0){//Quando sai um flamenguista e não houver outros na fila, vascaínos podem entrar
		pthread_cond_signal(&vascainoPodeEntrar);
	}else{
		pthread_cond_signal(&flamenguistaPodeEntrar);
	}

	pthread_mutex_unlock(&mutex);
}

void vascainoQuerEntrar(){
	pthread_mutex_lock(&mutex);

	if(pessoasNoBanheiro){
		if(flag == 'v'){
			if(pessoasNoBanheiro == 3){
				pthread_cond_wait(&vaga, &mutex);
			}
		}else{
			pthread_cond_wait(&vascainoPodeEntrar, &mutex);
		}
	}else if(temFlamenguistaNaFila){//Caso tenha flamenguista, espera até poder entrar

		pthread_cond_wait(&vaga, &mutex);
		pthread_cond_wait(&vascainoPodeEntrar, &mutex);

	}

	pessoasNoBanheiro++;
	flag = 'v';
	
	pthread_mutex_unlock(&mutex);
}

void vascainoQuerSair(){

	pthread_mutex_lock(&mutex);

	pessoasNoBanheiro--;
	pthread_cond_signal(&vaga);

	if(temFlamenguistaNaFila){
		if(pessoasNoBanheiro == 0){
			pthread_cond_signal(&flamenguistaPodeEntrar);
		}
	}else{
		pthread_cond_signal(&vascainoPodeEntrar);
	}
	
	pthread_mutex_unlock(&mutex);
}

/*Monitor não recebe Parâmetros, é bem específico para o problema*/
void inicializaMonitor(){
	pthread_cond_init(&vascainoPodeEntrar, NULL);
	pthread_cond_init(&flamenguistaPodeEntrar, NULL);
	pthread_cond_init(&vaga, NULL);
	pthread_mutex_init(&mutex, NULL);
}