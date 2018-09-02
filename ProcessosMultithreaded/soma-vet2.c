// cc -pthread soma-vet2.c -o sv2

#include <pthread.h>

int soma1, soma2, soma3;
int vet[30000];                         
 
void * p0(){
  int i;
  for(i=0;i<10000;i++) { 
     soma1 += vet[i];
     }
}


void * p1(){
  int i;
  for(i=10000;i<20000;i++) {
     soma2 += vet[i];
     }
}

void * p2(){
  int i;
  for(i=20000;i<30000;i++) {
     soma3 += vet[i];
     }	 
}   
         


main(){

  int somatot,a;

  for(a=0;a<30000;a++) {
     if(a<10000)
       vet[a] = 1;
     else
     if(a<20000)
       vet[a] = 2;
     else
       vet[a] = 3;
  }  

  printf("MAIN\n");
 
 
  pthread_t t0, t1, t2;
  
  pthread_create(&t0, NULL, p0, NULL);
  pthread_create(&t1, NULL, p1, NULL);
  pthread_create(&t2, NULL, p2, NULL);
 
  
  pthread_join(t0,NULL);
  pthread_join(t1,NULL);
  pthread_join(t2,NULL);
 
  somatot = soma1 + soma2 + soma3;
  printf("Soma Total: %d\n",somatot);
}
