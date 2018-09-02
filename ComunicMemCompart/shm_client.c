/*
 * shm-client - programa cliente
 * demonstra a o acesso a area de memoria criada por outro processo
 *
 * EXEMPLO de:  https://users.cs.cf.ac.uk/Dave.Marshall/C/node27.html
 *
 * Utilizado para exemplificacao por Fernando Dotti em Sistemas Operacionais
 *
 */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

#define SHMSZ     27

main()
{
    int shmid;
    key_t key;
    char *shm, *s;

    /*
     * Sabemos o nome do segmento criado pelo servidor.
     * "5678".
     */
    key = 5678;

    /*
     * Localiza o segmento. 
     */
    if ((shmid = shmget(key, SHMSZ, 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    /*
     * Associa o segmento ao nosso espaco de dados.
     */
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    /*
     * Le o que esta escrito no segmento (neste caso o que o servidor escreveu).
     */
    for (s = shm; *s != NULL; s++)
        putchar(*s);
    putchar('\n');

    /*
     * Muda o primeiro caracter do segmento para  
     * '*', indicando que leu o segmento 
     * - o servidor saira da espera - este pode ser considerado 
	 * um 'protocolo' bastante simples de comunicacao entre os processos.
     */
    *shm = '*';

    exit(0);
}
