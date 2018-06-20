#include <xinu.h>
#include <string.h>
#include <stdio.h>

void p1();
void p2();
void p3(pid32 pid);

void p2()
{	pid32 pid;
	
	
	pid=getpid();
	resume(create(p3,1024,30,"p3",1,pid));
	kprintf("\n Old prio= %d",30);
}

void p3(pid32 pid)
{	uint16 pri;
	chprio(pid,35);
	//kprintf("New prio= %d \n",pri);
}

void p1()
{
	uint16 pri1;
	pri1=resume(create(p2,1024,25,"p2 \n",0));
	kprintf("\n New prio= %d",pri1);
}


shellcmd xsh_hello(int argc,char *argv[])
{
		resume(create(p1,1024,20,"p",0));
		
		
        if(argc==2)
        {
                printf("\n Hello %s, Welcome to the world of Xinu!",argv[1]);

        }

        if(argc>2)
        {
                printf("Too many arguments in %s ",argv[0]);
        }
        if(argc<2)
        {
                printf("There should be atleast one argument in %s",argv[0]);
        }
}

