//
//  tasks.h
//  scheduler
//
//  Created by Melyssa Son on 3/21/13.
//
//

#ifndef scheduler_tasks_h
#define scheduler_tasks_h


typedef struct
{
    void (*taskFunction)(void);
    int executionTime;
} Task;

/*********** TASK A ***********/
void taskAfunction()
{
    printf("Hello I am task A!\n"); 
    
}

Task taskA = { .taskFunction = taskAfunction, .executionTime = 3 };

/*********** TASK B ***********/
void taskBfunction()
{
    printf("Hello I am task B!\n");
    
}

Task taskB = { .taskFunction = taskBfunction, .executionTime = 1 };

/*********** TASK C ***********/

void taskCfunction()
{
    printf("Hello I am task C!\n");
    
}

Task taskC = { .taskFunction = taskCfunction, .executionTime = 5 };

#endif
