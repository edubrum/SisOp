// cc -pthread soma-vet2.c -o sv2
#include <pthread.h>
#include<stdio.h>
int soma1, soma2, soma3;
int vet[30];                         
void * p0(){
  int i;
  for(i=0;i<10;i++) 
     soma1 += vet[i];
}
void * p1(){
  int i;
  for(i=10;i<20;i++) 
     soma2 += vet[i];
}
void * p2(){
  int i;
  for(i=20;i<30;i++) 
     soma3 += vet[i];
}   
int main(void){
  int somatot,a;
  for(a=0;a<30;a++) {
     if(a<10)
       vet[a] = 1;
     else
     if(a<20)
       vet[a] = 2;
     else
       vet[a] = 3;
  }  
  pthread_t t0, t1, t2;
  pthread_create(&t0, NULL, p0, NULL);
  pthread_create(&t1, NULL, p1, NULL);
  pthread_create(&t2, NULL, p2, NULL);
  pthread_join(t0,NULL);
  pthread_join(t1,NULL);
  pthread_join(t2,NULL);
  somatot = soma1 + soma2 + soma3;
  printf("Soma Total: %d\n",somatot);
	for(a=0;a<30;a++)
		printf("Vet[%d] = %d\n",a,vet[a]);
	return(0);
}
