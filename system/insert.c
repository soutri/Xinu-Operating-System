/* insert.c - insert */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  insert  -  Insert a process into a queue in descending key order
 *------------------------------------------------------------------------
 */
status	insert(
	  pid32		pid,		/* ID of process to insert	*/
	  qid16		q,		/* ID of queue to use		*/
	  int32		key		/* Key for the inserted process	*/
	)
{
	//int16	curr;			/* Runs through items in a queue*/
	//int16	prev;			/* Holds previous node index	*/
	struct qentry *curr;
	struct qentry *prev;

	if (isbadqid(q) || isbadpid(pid)) {
		return SYSERR;
	}

	curr= &queuetab[firstid(q)];
	while (curr!=NULL && curr->qkey >= key) {
		curr = queuetab[curr->proc_id].qnext;
	}

	/* Insert process between curr node and previous node */

	//prev = queuetab[curr].qprev;	/* Get index of previous node	*/
	//queuetab[pid].qnext = curr;
	//queuetab[pid].qprev = prev;
	//queuetab[pid].qkey = key;
	//queuetab[prev].qnext = pid;
	//queuetab[curr].qprev = pid;

	prev = queuetab[curr->proc_id].qprev;
	queuetab[pid].qnext = curr;
	queuetab[pid].qprev = prev;
	queuetab[pid].qkey = key;
	queuetab[pid].proc_id=pid;
	queuetab[prev->proc_id].qnext=&queuetab[pid];
	queuetab[curr->proc_id].qprev=&queuetab[pid];

	return OK;
}
