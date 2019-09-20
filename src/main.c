
/*						*
 *		 PHASE1 RIKAYA	   		*
 *						*
 * 	 Sviluppato dal gruppo lso19az22 	*
 *						*
 * 	 Componenti del gruppo:	   		*
 *	   - Filippo Bartolucci	   		*
 *	   - Francesco Cerio		     	*/

#include "pcb.h"
#include "const.h"
#include "handler.h"
#include "listx.h"
#include "scheduler.h"
#include "types_rikaya.h"
#include "initArea.h"
#include "utils.h"
#include "asl.h"

/* Traced Regions */
u32 debug=0;
/* Funzioni di test per PHASE2 */
extern void test();

/* Lista dei processi ready */
LIST_HEAD(ready_queue);
/* Puntatore al processo attivo */
pcb_t* current_process = NULL;
/* Contatore processi */
u32 process_count = 0;

/* Puntatori alle NEW AREA della ROM */
state_t *sysbk_newarea = (state_t *)SYSBK_NEWAREA;
state_t *program_trap_newarea = (state_t *)PGMTRAP_NEWAREA;
state_t *interrupt_newarea = (state_t *)INT_NEWAREA;
state_t *tlbmgt_newarea = (state_t *)TLB_NEWAREA;

/* Puntatori alle OLD AREA della ROM */
state_t *sysbk_oldarea = (state_t *)SYSBK_OLDAREA;
state_t *program_trap_oldarea = (state_t *)PGMTRAP_OLDAREA;
state_t *interrupt_oldarea = (state_t *)INT_OLDAREA;
state_t *tlbmgt_oldarea = (state_t *)TLB_OLDAREA;

void dummy(){
	state_t proc;

	memset(&proc,0,sizeof(proc));
	proc.pc_epc = (u32) test;
	proc.reg_sp = RAMTOP - FRAME_SIZE *2;
	proc.status = getSTATUS()|1UL;
	debug = 0xCACCA;
	SYSCALL(SETTUTOR,0,0,0);
	debug = 0xBABBA;
	SYSCALL(CREATEPROCESS, (u32) &proc,1,0);

	setSTATUS(getSTATUS()|1UL);
	while (1)
		debug=0xBEFFA;
}

void setProcess(u32 proc, int prio, int frame){
    /* Prendo un PCB dalla lista dei PCB liberi */
	pcb_t *tmp = allocPcb();
    /* Imposto il PROGRAM COUNTER del processo */
	tmp->p_s.pc_epc = tmp->p_s.reg_t9 = (u32)proc;
    /* Imposto la priorità */
	tmp->priority = tmp->original_priority = prio;
    /* Imposto lo STACK POINTER */
	tmp->p_s.reg_sp = RAMTOP - FRAME_SIZE*frame;
    /* Imposto lo STATUS del process */
	tmp->p_s.status = 0|1<<27|0xFF<<8;

    /* Aumento il contatore dei processi */
	process_count++;
    /* Inserisco il PCB nella lista dei processi in stato ready */
	insertProcQ(&ready_queue, tmp);
}

int main(void){
    /* Inizializzazione del sistema */
    initAREA();
    initPcbs();
    initASL();
    /* Setto Interval Timer */
    *((u32 *)INT_TIMER) = (u32)PSEUDO_CLOCK_TICK;
    memset(&semd_keys,1,(sizeof(int))*7*8);

    //setProcess(test,1,2);
    setProcess(dummy,0,1);
    /* Passo il controllo allo scheduler */
    scheduler();

    /* L'esecuzione non deve mai arrivare qui */
    PANIC();
    return 0;
}
