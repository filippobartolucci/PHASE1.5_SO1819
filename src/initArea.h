#include "pcb.h"
#include "const.h"
#include "handler.h"
#include "interrupt.h"
#include "listx.h"
#include "scheduler.h"
#include "types_rikaya.h"


/* Lista dei processi ready */
extern INIT_LIST(ready_queue);
/* Puntatore al processo atti,vo */
extern pcb_t* current_process
/* Contatore processi */
extern u32 process_count;
/* Contatore processi bloccati per I/O */
extern u32 soft_block_count;

/* Puntatori alle NEW AREA della ROM */
extern state_t *sysbk_newarea = SYSBK_NEWAREA;
extern state_t *program_trap_newarea = PRGTRP_NEWAREA;
extern state_t *interrupt_newarea = INT_NEWAREA;
extern state_t *tblmgt_newarea = TLB_NEWAREA;


HIDDEN inline void initSYS(u32 status);
HIDDEN inline void initPGMTRP(u32 status);
HIDDEN inline void initINT(u32 status);
HIDDEN inline void initTLB(u32 status);
void initNEWAREA(void);

