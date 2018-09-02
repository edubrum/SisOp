#include <stdio.h>

// gcc fork-tres-filhos.c -o f3f
// teste com ./f3f
//           
// compreenda a saida do programa
// reflita sobre o comportamento do fork 


main()
{
int i, pid;

  for (i= 1; i < 3; i++) {
	   // printf("Eu sou o processo %ld\n", (long) getpid() );
        if (pid = fork()==0) break ;   //  se for filho, sai do for
	}
  
  // ao sair do for, todos escrevem
  printf("Eu sou o processo %ld, e meu pai e %ld\n",(long) getpid(),(long) getppid());
}


