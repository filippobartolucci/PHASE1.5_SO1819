/*						*
 *		 PHASE1 RIKAYA	   		*
 *						*
 * 	 Sviluppato dal gruppo lso19az22 	*
 *						*
 * 	 Componenti del gruppo:	   		*
 *	   - Filippo Bartolucci	   		*
 *	   - Francesco Cerio		     	*/

#ifndef _HANDLER_H
#define _HANDLER_H

#include "listx.h"
#include "utils.h"
#include "initArea.h"
#include "scheduler.h"
#include "asl.h"

/* Funzioni per la gestione delle eccezioni */
void sysbk_handler(void);
void int_handler(void);
void tlb_handler(void);
void pgmtrp_handler(void);

HIDDEN void getCpuTime(unsigned int* user, unsigned int* kernel, unsigned int* wallclock);
HIDDEN int createProcess(state_t* statep, int priority, void** cpid);
HIDDEN void verhogen(int* semaddr);
HIDDEN void terminateProcess();
#endif
