#define PRI_PAGOS 1
#define PRI_ANULACIONES 2
#define PRI_OTROS 3
#define PRI_DEFECTO -1

#include <linux/sched.h>
#include <linux/module.h>
#include <linux/kernel.h>


int crear_procesos(struct task_struct*);
int habilitar(struct task_struct*);
int mata_proceso(struct task_struct*);

int buscar_bloqueado(void);
int buscar_victima(int);
int actualizar_procesos(struct task_struct*);

void revisor(void);
