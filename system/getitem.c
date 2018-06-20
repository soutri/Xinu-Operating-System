/* getitem.c - getfirst, getlast, getitem */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  getfirst  -  Remove a process from the front of a queue
 *------------------------------------------------------------------------
 */
pid32	getfirst(
	  qid16		q		/* ID of queue from which to	*/
	)				/* Remove a process (assumed	*/
					/*   valid with no check)	*/
{
	pid32	head;
	
		if (isbadqid(q)) {
		return SYSERR;
	}

	if (isempty(q)) {
		return EMPTY;
	}

	head = queuehead(q);
	//head= &queuetab[queuehead(q)];
	return getitem(queuetab[head].qnext->proc_id);
}

/*------------------------------------------------------------------------
 *  getlast  -  Remove a process from end of queue
 *------------------------------------------------------------------------
 */
pid32	getlast(
	  qid16		q		/* ID of queue from which to	*/
	)				/* Remove a process (assumed	*/
					/*   valid with no check)	*/
{
	pid32 tail;
	//struct qentry *tail;
		if (isbadqid(q)) {
		return SYSERR;
	}

	if (isempty(q)) {
		return EMPTY;
	}

	tail = queuetail(q);
	//tail = &queuetab[queuetail(q)];
	return getitem(queuetab[tail].qprev->proc_id);
}

/*------------------------------------------------------------------------
 *  getitem  -  Remove a process from an arbitrary point in a queue
 *------------------------------------------------------------------------
 */
pid32	getitem(
	  pid32		pid		/* ID of process to remove	*/
	)
{
	//pid32	prev, next;
	struct qentry *prev;
	struct qentry *next;
	
		if (isbadpid(pid)) {
		return SYSERR;
	}


	//next = queuetab[pid].qnext;	/* Following node in list	*/
	//prev = queuetab[pid].qprev;	/* Previous node in list	*/
	//queuetab[prev].qnext = next;
	//queuetab[next].qprev = prev;

	 next = queuetab[pid].qnext;
	 prev = queuetab[pid].qprev;
	 prev->qnext = next;
	 queuetab[next->proc_id].qprev = prev;



	return pid;
}
