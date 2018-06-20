
#include "xinu.h"
#include "future.h"

uint future_prod(future_t* fut,int n);
uint future_cons(future_t* fut);

shellcmd xsh_future(int argc,char *argv[])
{
			
			//printf("enqued");
     if(argc==2)
       {		if(strncmp(argv[1],"-f",3)==0)
       		{
       			future_t* f_exclusive;
 					f_exclusive = future_alloc(FUTURE_EXCLUSIVE);
 					resume( create(future_cons, 1024, 20, "fcons1", 1, f_exclusive) );
  					resume( create(future_prod, 1024, 20, "fprod1", 2, f_exclusive, 1) );
		
					future_t* f_shared;
					f_shared=future_alloc(FUTURE_SHARED);
					resume( create(future_cons, 1024, 20, "fcons2", 1, f_shared) );
  					resume( create(future_cons, 1024, 20, "fcons3", 1, f_shared) );
  					resume( create(future_cons, 1024, 20, "fcons4", 1, f_shared) ); 
  					resume( create(future_cons, 1024, 20, "fcons5", 1, f_shared) );
  					resume( create(future_prod, 1024, 20, "fprod2", 2, f_shared, 2) );
  					//resume( create(future_prod, 1024, 20, "fprod2", 2, f_shared, 9) );
  					//future_free(f_shared);
  					
  					
  					future_t* f_queue;
  					f_queue=future_alloc(FUTURE_QUEUE);
					resume( create(future_cons, 1024, 20, "fcons9", 1, f_queue) );
  					resume( create(future_cons, 1024, 20, "fcons6", 1, f_queue) );
  					resume( create(future_cons, 1024, 20, "fcons7", 1, f_queue) );
  					resume( create(future_cons, 1024, 20, "fcons8", 1, f_queue) );
  					resume( create(future_prod, 1024, 20, "fprod3", 2, f_queue, 3) );
  					resume( create(future_prod, 1024, 20, "fprod4", 2, f_queue, 4) );
  					resume( create(future_prod, 1024, 20, "fprod5", 2, f_queue, 5) );
  					resume( create(future_prod, 1024, 20, "fprod6", 2, f_queue, 6) );
 					
 					//enqueue_t(f_exclusive->get_queue,1);
 					//enqueue_t(f_exclusive->get_queue,2);
 					//enqueue_t(f_exclusive->get_queue,3);
 					//dequeue_t(f_exclusive->get_queue);
					//f_shared    = future_alloc(FUTURE_SHARED);
  					//f_queue     = future_alloc(FUTURE_QUEUE);
       		
       		
       		}
       		else {
       				printf("Invalid flag set in %s ",argv[0]);
       		}
               
				
       }

       if(argc>2)
      {
              printf("Too many arguments in %s ",argv[0]);
       }
        if(argc<2)
       {
             printf("There should be atleast one argument in %s",argv[0]);
       }
       
       return OK;

}



