#ifndef _TYPES11_H
#define _TYPES11_H

#include <umps/types.h>
#include "listx.h"

typedef unsigned int memaddr;

// Process Control Block (PCB) data structure
typedef struct pcb_t {
	/*process queue fields */
	struct list_head	p_next;

	/*process tree fields */
	struct pcb_t		*p_parent;
	struct list_head	p_child,
                        p_sib;
	/* processor state, etc */
	state_t       		p_s;
	/* process priority */
	int			priority;
	int 		original_priority;
    int tutor;
	/* key of the semaphore on which the process is eventually blocked */
	int			*p_semkey;
	/* execution time for each process */
	unsigned int 		user_time_start;
	unsigned int		user_time;
	unsigned int 		kernel_time_start;
	unsigned int 		kernel_time;
	unsigned int		total_time;
	/* Trap vectors */
	state_t *spec_oarea[3];
	state_t *spec_narea[3];
	int spec_set[3];
} pcb_t;



// Semaphore Descriptor (SEMD) data structure
typedef struct semd_t {
	struct list_head	s_next;

	// Semaphore key
	int    *s_key;

	// Queue of PCBs blocked on the semaphore
	struct list_head	s_procQ;
} semd_t;

#endif
