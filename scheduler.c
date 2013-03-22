//
//  scheduler.c
//  
//
//  Created by Melyssa Son on 3/21/13.
//
//

#include <stdio.h>

#include "scheduler.h"
#include "tasks.h"

void scheduler()
{
    int t = 0;          /* current time */
    int k = 0;          /* current frame */
    int taskIdx = 0;    /* keeps track what task we're on */
    int idle = 1;       /* keeps track if we executed a task or not */
    
    while(1)
    {
        idle = 1;
        //sleep(1); // FOR DEBUG ONLY!
        
        /* t is not incremented here like it is in the book, this is
         because we don't have timers. t is incremented by the execution
         time when a task is scheduled or when it idles */
        k = (t/FRAME_SIZE)%FRAMES;
        
        /* Assumption: no tasks run over... since we don't have a timer, this
         has to be true */
        
        /* execute PERIODIC tasks */
        if(tasks[k][taskIdx] != NULL && taskIdx < MAX_TASKS_PER_FRAME)
        {
            /* simulate the passage of time */
            //DEBUG: printf("Scheduler executing a task t=%d, k=%d, taskIdx=%d\n", t, k, taskIdx);
            t += tasks[k][taskIdx]->executionTime;
            tasks[k][taskIdx]->taskFunction();
            idle = 0;
            
            /* increment taskIdx */
            if(k == (t/FRAME_SIZE)%FRAMES)
            {
                taskIdx++;
            }
            else
            {
                taskIdx = 0; 
            }
            
        } 
        else   
        {
            /* execute APERIODIC tasks */
            if(!isEmpty(&aperiodicQ)) 
            {
                int remainingTime = FRAME_SIZE - (t%FRAME_SIZE);
                
            
                /* Since we can't premept jobs in this setup, don't run aperiodic tasks
                 unless you have enough time in the frame */
            
                Task * newTask = queuePeek(&aperiodicQ);
                // DEBUG printf("t= %d Remaining Time: %d execution: %d\n", t,  remainingTime, newTask->executionTime);
                if(newTask->executionTime <= remainingTime)
                {
                    /* execute it */
                    t += newTask->executionTime;
                    newTask->taskFunction();
                    queueRemove(&aperiodicQ);
                    idle = 0;
                }
            }
            
            /* execute SPORADIC tasks */
            if(!isEmpty(&sporadicQ)) 
            {
                int remainingTime = FRAME_SIZE - (t%FRAME_SIZE);
                
                /* This is the major difference between the sporadic and aperiodic
                 tasks: If we don't have time to run the sporadic task, it doesn't
                 get run at all because late is worse than never, and is thus 
                 removed whether it runs or not */ 
                
                Task * newTask = queueRemove(&sporadicQ);
                if(newTask->executionTime <= remainingTime)
                {
                    /* execute it */
                    t += newTask->executionTime;
                    newTask->taskFunction();
                    idle = 0;
                }
            }
                
        }
        
        if(idle)
        {
            /* no tasks were executed, advance the clock anyways */
            // DEBUG: printf("Idling... t=%d frame=%d\n", t, k);
            t++;
        }

        
        //reset taskIdx if needed
        if(k != (t/FRAME_SIZE)%FRAMES)
        {
            taskIdx = 0;
        }
        
    }
   
}

int main(void)
{
    printf("Here we go...\n");

    // Make some aperiodic tasks
    queueInsert(&taskB, &aperiodicQ);
    queueInsert(&taskC, &aperiodicQ);
    
    scheduler();
    
    return 0; 
}