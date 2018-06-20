#include "xinu.h"
#include "future.h"

//struct queue_t* queue;

//queue_t* set_queue(int k);
//queue_t* get queue();

int count;

//ALLOCATE A NEW FUTURE IN THE GIVEN MODE
future_t* future_alloc(future_mode_t mode)
{	
	count =0;
	future_t* pntr= getmem(sizeof(future_t));
	pntr->set_queue=getmem(sizeof(struct queue_t));
	pntr->get_queue=getmem(sizeof(struct queue_t));
	pntr->mode=mode;
	pntr->state=FUTURE_EMPTY;
	return pntr; 
}


syscall future_free(future_t* f)
{
freemem(f->get_queue,sizeof(struct queue_t));
freemem(f->set_queue,sizeof(struct queue_t));
freemem(f,sizeof(f));

return OK;
//error handle
}


void enqueue_t(struct queue_t* queue,int k)
{	
	struct queue_t* temp = getmem(sizeof(struct queue_t));
	temp=queue;
	if(temp->data==0)
	{
		//	printf("got first node\n");
		temp->data=k;
		temp->next=NULL;
		//printf("first node :: %d\n", temp->data);
	
	}
	else
	{
		//printf("not first node\n");
		while(temp->next!=NULL)
		{
		//printf("temp next not null\n");
		//printf("temp data :: %d\n", temp->data);
			temp=temp->next;
	
		}
		//printf("temp next null\n");
		struct queue_t* temp1=getmem(sizeof(struct queue_t));
		temp1->data=k;
		//printf("temp1 data :: %d\n", temp1->data);
		temp1->next=NULL;
		//printf("temp data before inserting new node ::%d\n", temp->data);
		temp->next=temp1;
	}
		
		temp = queue;
	while(temp!=NULL)
	{
		//	printf(" new temp data :: %d\n",temp->data);
		temp=temp->next;
		
	
	}	
		

}


int dequeue_t(struct queue_t* q)
{	
	/*while(q!=NULL)
	{
		printf("deque :: %d\n",q->data);
		q=q->next;
		
	
	}*/
	int n=q->data;
	q->data=q->next->data;
	//printf(":: %d \n",q->data);
	q->next=q->next->next;
	//printf("dequed ::  %d",n);
		while(q->next!=NULL)
	{
		///printf("%d \n",q->data);
		q=q->next;
	}	
	
	return n;
	
}



syscall future_get(future_t* pntr,int* i)
{
	
	if(pntr->mode==FUTURE_EXCLUSIVE)
	{ 
		
		if(pntr->state!=FUTURE_READY)
		{
		pntr->state = FUTURE_WAITING;	
		pntr->pid=getpid();
		suspend(pntr->pid);	
		*i=pntr->value;
		pntr->state = FUTURE_EMPTY;	
		
		
		}
		
		return OK;
	
	}
		
	else if(pntr->mode==FUTURE_SHARED)
	{	
		if(pntr->state!=FUTURE_READY)
		{	
			pntr->state=FUTURE_WAITING;
			pntr->pid=getpid();
			enqueue_t(pntr->get_queue,pntr->pid);
			
			suspend(pntr->pid);
			*i=pntr->value;
			pntr->state = FUTURE_EMPTY;
		}
	
	
	}
	else if(pntr->mode==FUTURE_QUEUE)
	{	
		//printf("inside get queue '\n'");
		if(pntr->set_queue->data!=0)
		{	
			//printf("set_queue not empty \n");
			pntr->pid=getpid();
			//printf("get pid \n");
			int d=dequeue(pntr->set_queue);
			pntr->state=FUTURE_WAITING;
			//printf("value_dequed_set_queue \n");
			resume(d);
			//suspend(pntr->pid);
			*i=pntr->value;
			if(pntr->get_queue->data!=0)
			{
				pntr->state= FUTURE_WAITING;
			}
			else {
			pntr->state = FUTURE_EMPTY;
			}
			
		}
		else{
			int a=getpid();
			enqueue_t(pntr->get_queue,a);
			pntr->state=FUTURE_WAITING;
			//printf("consumer enqued \n");
			suspend(a);
			*i=pntr->value;
			if(pntr->get_queue->data!=0)
			{
				pntr->state= FUTURE_WAITING;
			}
			else {
			pntr->state = FUTURE_EMPTY;
			}
			
		}
	
	
	
	}


}

syscall future_set(future_t* pntr,int n)
{	
	if(pntr->mode==FUTURE_EXCLUSIVE)
	{
			int a =getpid();
			if(pntr->state==FUTURE_EMPTY||pntr->state==FUTURE_WAITING) 
			{	
			pntr->value=n;
			pntr->state = FUTURE_READY;
			resume(pntr->pid);
			}
				
	}
	else 
		if(pntr->mode==FUTURE_SHARED)
		{	count=count+1;
			if(count>1)
			{
				printf("Only one producer allowed '/n'");
				return -1;
			
			}
			int a =getpid();
			if(pntr->state==FUTURE_EMPTY||pntr->state==FUTURE_WAITING) 
			{	
			pntr->value=n;
			pntr->state = FUTURE_READY;
			while(pntr->get_queue->data!=0) {
			//printf("Ready to dequeue value\n");
			int x=dequeue_t(pntr->get_queue);
			resume(x);
			}
			}
		
		}
	else
		if(pntr->mode==FUTURE_QUEUE)
		{	//printf("Entering set_queue\n");
			if(pntr->get_queue->data!=0)
			{
				//printf("Entering future_set main if\n");
				//printf("MODE :::: %s\n", pntr->state);
				if(pntr->state==FUTURE_EMPTY||pntr->state==FUTURE_WAITING) 
			{	
					//printf("Entering future_set if\n");
					pntr->value=n;
					pntr->state = FUTURE_READY;
					int x=dequeue_t(pntr->get_queue);
					//printf("dequeue_get_queue\n%d",x);
					resume(x);
			}
				
				}
				else{
					//printf("Entering future_set main else\n");
					
					int a=pntr->pid;
					enqueue_t(pntr->set_queue,a);
					pntr->state=FUTURE_WAITING;
					//printf("value_enqued_producer\n");
					suspend(a);	
					pntr->value=n;
					pntr->state = FUTURE_READY;
				
			
			}
		
		
		
		}
		
	return OK;
}









