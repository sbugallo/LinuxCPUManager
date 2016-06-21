#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sched.h>
#include<errno.h>

int main (int argc, char *argv[]){

	int prueba;

	struct sched_param nodo;
        nodo.sched_priority = 99;
        if(sched_setscheduler(0,SCHED_FIFO,&nodo)!=0)
		printf("Error al asignar prioridad a pruebas\n");

	prueba=atoi(argv[1]);

	switch(prueba){
		case 1	:	prueba1();
				break;

		case 2	:	prueba2();
				break;

		case 3	:	prueba3();
				break;

		case 4	:	prueba4();
				break;

		case 5	:	prueba5();
				break;

		case 6	:	prueba6();
				break;

		case 7	:	prueba7();
				break;

		case 8	:	prueba8();
				break;

		case 9	:	prueba9();
				break;	
		default:
		printf("Selecciona una prueba al invocar\n");
				break;
	}
	
	return 0;
}

void prueba1(){
	int i;
	int pid;

	for(i=0; i<2; i++){
		if((pid=fork())==-1){
			printf("Error al hacer el fork\n");
			exit(1);
		}
		if(pid==0){
			if(execl("pagos",NULL)==-1){
				printf("Error al ejecutar execl\n");
				exit(1);
			}
		}
	}
	for(i=0;i<2;i++){
		wait(2);
	}
	return;
}

void prueba2(){ 
	int i;
        int pid;

	if((pid=fork())==-1){
        	printf("Error al hacer el fork\n");
                exit(1);
      	}
        if(pid==0){
        	if(execl("gradas",NULL)==-1){
        		printf("Error al ejecutar execl\n");
               		exit(1);
		}
       	}

	if((pid=fork())==-1){
                printf("Error al hacer el fork\n");
                exit(1);
        }
        if(pid==0){
       		if(execl("prereservas",NULL)==-1){
                	printf("Error al ejecutar execl\n");
               		 exit(1);
		}
        }
 	
	for(i=0;i<2;i++){
                wait(2);
        }
       
	return;
}

void prueba3(){
	int i;
        int pid;

	if((pid=fork())==-1){
                printf("Error al hacer el fork\n");
                exit(1);
        }
        if(pid==0){   
        	if(execl("pagos",NULL)==-1){
                	printf("Error al ejecutar execl\n");
                	exit(1);
		}
        }

        if((pid=fork())==-1){
                printf("Error al hacer el fork\n");
                exit(1);
        }
        if(pid==0){   
        	if(execl("prereservas",NULL)==-1){
                	printf("Error al ejecutar execl\n");
                	exit(1);
		}
        }

 	for(i=0;i<2;i++){
                wait(2);
        }
        return;

}

void prueba4(){
	int i;
        int pid;

 	if((pid=fork())==-1){
                printf("Error al hacer el fork\n");
                exit(1);
        }
        if(pid==0){   
        	if(execl("pagos",NULL)==-1){
                	printf("Error al ejecutar execl\n");
                	exit(1);
		}
        }
	
	wait(1);

	return;
}

void prueba5(){
	int i;
        int pid;
 
	if((pid=fork())==-1){
                printf("Error al hacer el fork\n");
                exit(1);
        }
        if(pid==0){   
        	if(execl("prereservas",NULL)==-1){
                	printf("Error al ejecutar execl\n");
                	exit(1);
		}
        }
 	
	wait(1);
	
	return;
}

void prueba6(){
	int i;
        int pid;

 	 for(i=0; i<4; i++){
                if((pid=fork())==-1){
                        printf("Error al hacer el fork\n");
                        exit(1);
                }
                if(pid==0){
                        if(execl("pagos",NULL)==-1){
                                printf("Error al ejecutar execl\n");
                                exit(1);
                        }
                }
        }
	for(i=0;i<4;i++){
                wait(4);
        }
   
	return;
}

void prueba7(){
	int i;
        int pid;

	for(i=0; i<4; i++){
                if((pid=fork())==-1){
                        printf("Error al hacer el fork\n");
                        exit(1);
                }
                if(pid==0){
                        if(execl("anulaciones",NULL)==-1){
                                printf("Error al ejecutar execl\n");
                                exit(1);
                        }
                }
        }
	
	for(i=0;i<4;i++){
                wait(4);
        }
        return;

}

void prueba8(){
	int i;
        int pid;

	 for(i=0; i<6; i++){
                if((pid=fork())==-1){
                        printf("Error al hacer el fork\n");
                        exit(1);
                }
                if(pid==0){
                        if(execl("pagos",NULL)==-1){
                                printf("Error al ejecutar execl\n");
                                exit(1);
                        }
                }
        }
	
	for(i=0;i<6;i++){
                wait(6);
        }
        return;
}

void prueba9(){
	int i;
        int pid;

	 for(i=0; i<3; i++){
                if((pid=fork())==-1){
                        printf("Error al hacer el fork\n");
                        exit(1);
                }
                if(pid==0){
                        if(execl("gradas",NULL)==-1){
                                printf("Error al ejecutar execl\n");
                                exit(1);
                        }
                }
        }
	if((pid=fork())==-1){
                printf("Error al hacer el fork\n");
                exit(1);
        }
       	if(pid==0){
              	if(execl("anulaciones",NULL)==-1){
                	printf("Error al ejecutar execl\n");
               		exit(1);
		}
        }

	for(i=0;i<6;i++){
                wait(6);
        }
        return;
}

