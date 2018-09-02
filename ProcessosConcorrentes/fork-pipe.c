#include <stdio.h>
int p0[2], p1[2] ;
char c, k ;
main()
{
int i, pid, pid1;
pipe(p0) ;
pid = fork() ;
if (pid != 0) {
        for (i=0; i<10; i++){
            puts("Digite um caracter: ");
            fflush(stdin);
            scanf("%c",&c); 
            write(p0[1], &c, sizeof(char));
            }
        } 
else {
     for (i=0;i<100;i++){
       read(p0[0], &k, sizeof(char)) ;
       printf("Lido do pipe: %c\n", k );
       }   
     }
}
