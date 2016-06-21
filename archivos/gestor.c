#include <linux/gestor.h>
#include <linux/sched.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/string.h>
#include <linux/list.h>
#include <linux/time.h>
#include <linux/signal.h>
#include <asm/cputime.h>

int num_eventos_pagos=0;
int num_eventos_anulaciones=0;
int num_eventos_otros=0;
int tmax=5;
int n=5;
int k=3;

int crear_procesos(struct task_struct *p){
	int fallo;

 	if(strcmp(p->comm,"pagos")==0){
		p->tipo=PRI_PAGOS;
 		if(habilitar(p)==0){
 			num_eventos_pagos++;
 			struct sched_param nodo;
 			nodo.sched_priority = 85;
 			//p->rt_priority = 85;
 			if((fallo=sched_setscheduler(p,SCHED_FIFO,&nodo))<0){
				printk("Ha ocurrido un error en el setscheduler");
 			}else{
				printk("+++El proceso con pid %d de tipo %s se ha anadido al sistema\n",p->pid,p->comm);
			}
 		}else{
			printk("No se ha podido introducir el proceso de tipo pagos con pid %d en el sistema\n",p->pid);
 			p->tipo=PRI_DEFECTO;
 			mata_proceso(p);
 		}
 
 
 }else 
 if(strcmp(p->comm,"anulaciones")==0){
 p->tipo=PRI_ANULACIONES; 
 if(habilitar(p)==0){
 num_eventos_anulaciones++; 
 struct sched_param nodo; 
 nodo.sched_priority = 75;
 //p->rt_priority = 75;
  if(sched_setscheduler(p,SCHED_FIFO,&nodo)<0)
	printk("Ha ocurrido un error en el setscheduler");
 else 
	printk("+++El proceso con pid %d de tipo %s se ha anadido al sistema\n",p->pid,p->comm);
 }else{
printk("No se ha podido introducir el proceso de tipo anulaciones con pid %d en el sistema\n",p->pid);
 p->tipo=PRI_DEFECTO;
 mata_proceso(p);
 }


 }else

 if(strcmp(p->comm,"gradas")==0){
 	p->tipo=PRI_OTROS; 
	 if(habilitar(p)==0){
 		num_eventos_otros++; 
 		struct sched_param nodo; 
 		nodo.sched_priority = 65;
 		//p->rt_priority = 65;
  		if(sched_setscheduler(p,SCHED_RR,&nodo)<0)
			printk("Ha ocurrido un error en el setscheduler");
 		else 
			printk("+++El proceso con pid %d de tipo %s se ha anadido al sistema\n",p->pid,p->comm);
 	}else{
	printk("No se ha podido introducir el proceso de tipo %s con pid %d en el sistema",p->comm,p->pid);

 p->tipo=PRI_DEFECTO;
 mata_proceso(p);
 }
}else

 if(strcmp(p->comm,"prereservas")==0){
        p->tipo=PRI_OTROS;
         if(habilitar(p)==0){
                num_eventos_otros++;
                struct sched_param nodo;
                nodo.sched_priority = 65;
                //p->rt_priority = 65;
                if(sched_setscheduler(p,SCHED_RR,&nodo)<0)
                        printk("Ha ocurrido un error en el setscheduler");
                else
                        printk("+++El proceso con pid %d de tipo %s se ha anadido al sistema\n",p->pid,p->comm);
        }else{
        printk("No se ha podido introducir el proceso de tipo %s con pid %d en el sistema\n",p->comm,p->pid);

 p->tipo=PRI_DEFECTO;
 mata_proceso(p);
 }
}else

 if(strcmp(p->comm,"eventos")==0){
        p->tipo=PRI_OTROS;
         if(habilitar(p)==0){
                num_eventos_otros++;
                struct sched_param nodo;
                nodo.sched_priority = 65;
                //p->rt_priority = 65;
                if(sched_setscheduler(p,SCHED_RR,&nodo)<0)
                        printk("Ha ocurrido un error en el setscheduler");
                else
                        printk("+++El proceso con pid %d de tipo %s se ha anadido al sistema\n",p->pid,p->comm);
        }else{
        printk("No se ha podido introducir el proceso de tipo %s con pid %d en el sistema",p->comm,p->pid);

 p->tipo=PRI_DEFECTO;
 mata_proceso(p);
 }

 }else{
		p->tipo=PRI_DEFECTO;
                struct sched_param nodo;
                nodo.sched_priority = 0;
                p->rt_priority = 0;
                sched_setscheduler(p,SCHED_RR,&nodo);
	}

return 0;
}


int habilitar(struct task_struct *p){
	int bloqueado = 0;
	int num_procesos = num_eventos_pagos + num_eventos_anulaciones + num_eventos_otros;
	bloqueado =buscar_bloqueado();
	if (bloqueado == 0) printk("Existe al menos un proceso bloqueado que se ha matado.\n");

	if(num_procesos == n){
		printk("Sistema saturado,se buscara de menor prioridad para matarlo\n");
		if(p->tipo == PRI_PAGOS){
			int victima = buscar_victima(p->tipo);
			if(victima != 0){
				printk("No se ha encontrado ningun proceso de menor prioridad\n");
				return -1;
			}
			return 0;
		}
		return -1;
 }
 if(num_procesos >= k){
 printk("Limite de procesos de tipo distinto de pago alcanzado.\n");
 if(p->tipo == PRI_PAGOS) return 0;
 if(p->tipo == PRI_ANULACIONES){
 printk("Se buscara un proceso de menor prioridad para matarlo\n");
 
 int victima = buscar_victima(p->tipo);
 if(victima != 0){
                                printk("No se ha encontrado ningun proceso de menor prioridad\n");
                                return -1;
                        }
                        return 0;

 }

 return -1;
 
 }
 


return 0;
}




//Busca los procesos propios que estan bloqueados 
int buscar_bloqueado(){
 struct task_struct *p;
 int flag = -1;

 //Recorremos el numero de procesos en el sistema
	 for_each_process(p){
 		if(p->tipo == PRI_PAGOS || p->tipo == PRI_ANULACIONES || p->tipo == PRI_OTROS){
 			if(cputime_to_secs(p->utime)>tmax){
				printk("---El proceso con pid %d y tipo %s ha estado dentro del sistema durante %lu segundos, por lo tanto lo matamos\n",p->pid,p->comm,cputime_to_secs(p->utime));
				mata_proceso(p);
				flag = 0;
			}
		}
	}

	return flag;
}




//Esta funcion mata el proceso y actualiza el valor de la variable que contiene el numero de procesos de este tipo en el sistema
int mata_proceso(struct task_struct *p){

	if (p->tipo==PRI_PAGOS){
		kill_pid(find_vpid(p->pid), SIGKILL ,1);
	}
	if (p->tipo==PRI_ANULACIONES){ 
                kill_pid(find_vpid(p->pid), SIGKILL ,1);
        }
	if (p->tipo==PRI_OTROS){ 
                kill_pid(find_vpid(p->pid), SIGKILL ,1);
        }
	if (p->tipo==PRI_DEFECTO){
                kill_pid(find_vpid(p->pid), SIGKILL ,1);
        }
	
	return 0;

}



int actualizar_procesos(struct task_struct *p){

	if (p->tipo==PRI_PAGOS){
		num_eventos_pagos--;
		printk("---El proceso %s con pid %d ha concluido.\n",p->comm,p->pid);
		p->tipo=PRI_DEFECTO;
		
	}
	if (p->tipo==PRI_ANULACIONES){ 
                num_eventos_anulaciones--;
               	printk("---El proceso %s con pid %d ha concluido.\n",p->comm,p->pid);
		p->tipo=PRI_DEFECTO;

        }
	if (p->tipo==PRI_OTROS){ 
                num_eventos_otros--;
               printk("---El proceso %s con pid %d ha concluido.\n",p->comm,p->pid);
		p->tipo=PRI_DEFECTO;
 
        }	
	return 0;

}




int buscar_victima(int tipo){
	struct task_struct *p;
	for_each_process(p){
		if(p->tipo > tipo){
                        struct sched_param nodo;
                        nodo.sched_priority=95;
                        sched_setscheduler(p,SCHED_RR,&nodo);
                        printk("---El proceso con pid %d de tipo %s sera matado por tener una prioridad menor\n",p->pid,p->comm);
                	mata_proceso(p);
			return 0;
		}

	}

	return -1;
}



void revisor(){
	struct task_struct *p;
	

	printk("Hay %d procesos de tipo pagos\n",num_eventos_pagos);
	printk("Hay %d procesos de tipo anulaciones\n",num_eventos_anulaciones);
	printk("Hay %d procesos de tipo pre-reservas,eventos y gradas\n",num_eventos_otros);	

	for_each_process(p){
                if(p->tipo == PRI_OTROS || p->tipo == PRI_PAGOS || p->tipo==PRI_ANULACIONES){
                        unsigned long tiempo = cputime_to_secs(p->utime);

			printk(KERN_NOTICE "El proceso de tipo %s con pid %d lleva %lu segundos en el sistema\n",p->comm,p->pid,tiempo);
                        
                }
        }

	buscar_bloqueado();

}

