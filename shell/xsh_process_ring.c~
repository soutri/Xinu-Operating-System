#include <xinu.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <process_ring.h>
shellcmd xsh_process_ring(int argc, char *argv[])
{
	int32 procs=DEFAULT_PROCS;
	int32 rounds= DEFAULT_ROUNDS;
	int32 i,j,k,l;
	int32 num,last;
	volatile int32 arr[procs];


	if(argc<1)
	{
		printf("Less number of arguments");

	}
	else if(argc>1)
		{
			for(i=1;i<argc;i++)
			{
				if(strncmp(argv[i],"-p",3)==0)
				{
					procs=atoi(argv[++i]);
					printf("Number of processes: %d\n",procs);
				
				}
				else if(strncmp(argv[i],"-r",3)==0)
				{
					rounds=atoi(argv[++i]);
					printf("Number of rounds %d\n",rounds);
				}

				else if(strncmp(argv[i],"-i",3)==0)
				{
					//if(strncmp(argv[++i],"poll",6)==0)
					if(strcmp(argv[++i],"poll")==0)
					{
						num=(procs*rounds)-1;
						arr[0]=num;
						for(k=1;k<procs;k++)
						{
							arr[k]=-1;
						}

						for(j=0;j<procs;j++)
						{
							resume(create(poll,1024,20,"Process",5,arr,rounds,j,procs));
						}
						while(arr[procs-1]!=-5);
					}	
					//if(strcmp(argv[++i],"sync")==0) //semaphore
					else
					{
							
							num=(procs*rounds)-1;
                                                        arr[0]=num;
																		
							sid32 semphor[procs];
							sid32 demophor= semcreate(0);
							for(l=0;l<procs;l++)
							{
								semphor[l] = semcreate(0);

							}
							last=procs-1;
							int32 pri;
							for(k=0;k<procs;k++)
							{	
								if(k==last)
								{	
									
									pri=resume(create(sem_syn,1024,20,"Process",7,&arr,rounds,k,semphor[k],semphor[0],demophor, procs));
									signal(semphor[0]);
								}	

								pri=resume(create(sem_syn,1024,20,"Process",7,&arr,rounds,k,semphor[k],semphor[k+1],demophor, procs));		
							}
							
							
							int32 x;
							for(x=0;x<procs;x++)
								wait(demophor);
							 	
							
					}
				

						
				}
				//help
				else if(strncmp(argv[i],"--help",8)==0)
				{
					
					printf("Use:\n");
					printf("\t%s [command]\n", argv[0]);
					printf("Description:\n");
					printf("\tPerforms a countdown based on the processes available\n");
					printf("\thelp information for a specific command\n");
					printf("Options:\n");
					printf("\t-p\tnumber of processors\n");
					printf("\t-r\tnumber of resources\n");
					printf("\t-i\ttype of synchronization\n");	
							
				
				}	

	
			}
				                          
				
		}
				
		return SHELL_OK;
}
