#include <xinu.h>
//polling
process poll(volatile int32* arr,int32 rounds,int32 j,int32 procs)
{
	
	int32 r=0;		
	int32 length=procs-1;	
	while(r<rounds)
	{
		if(arr[j]!=-1)
		{	
			printf("Ring Element %d :Round %d :value%d\n",j,r,arr[j]);
			
			if(j==length)
			{	
				arr[0]=arr[j]-1;	//checking for the last number
				if(arr[j]-1==-1)
				{
					arr[j]=-5;
				}
				else
					arr[j]=-1;
				
			}
			else
			{
				arr[j+1]=arr[j]-1;
				arr[j]=-1;
				
			}
			r++;
		
		}
		
	}
	return OK;
}
//sync using semaphore
process sem_syn(volatile int32* arr,int32 rounds,int32 l,sid32 sem,sid32 sem_next,sid32 demophor, int32 procs)
{
	int32 q=0;
	int32 data;
	while(q<rounds)
	{
		q++;
		wait(sem);
		printf("Ring Element %d :Round %d :value%d\n",l,q,arr[l]);
		//data=arr[l]-1;
		arr[(l+1)% procs] = arr[l]-1;
		signal(sem_next);
		//q++;

	}
	signal(demophor);
	return OK;	

}
