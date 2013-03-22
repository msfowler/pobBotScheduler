//
//  scheduler.h
//  scheduler
//
//  Created by Melyssa Son on 3/21/13.
//
//

//NOTE all tasks should be void myTask();
// The first frame to execute is frame 1 (not 0)

#ifndef scheduler_scheduler_h
#define scheduler_scheduler_h


#include "tasks.h"


#define FRAMES 5                /* Frames per hyperperiod */
#define FRAME_SIZE 5
#define MAX_TASKS_PER_FRAME 2  /* Maximum periodic tasks per frame */
#define QUEUE_SIZE 20

/* A two dimensional array of function pointers to the task schedule
 Each row corresponds to a frame. The row contains pointers to the
 tasks to be exectuted in the frame in order. The last task to be
 executed should be followed by NULL. Denoted by L(k) on page 91
 in the book by Liu. */
Task * tasks[FRAMES][MAX_TASKS_PER_FRAME] =
{   /* Frame 1*/ {&taskA,NULL},
    /* Frame 2*/ {NULL,NULL},
    /* Frame 3*/ {&taskA,NULL},
    /* Frame 4*/ {&taskA,NULL},
    /* Frame 5*/ {&taskA,NULL},
};

typedef struct
{
    Task * arr[QUEUE_SIZE];
    int rear;
    int front;
}Cqueue;

Cqueue aperiodicQ = { .rear = -1, .front = -1};
Cqueue sporadicQ = { .rear = -1, .front = -1};

void scheduler();


/***************** QUEUE OPERATIONS *************************/

int queueInsert(Task * tsk, Cqueue * q)
{
    if(q->front == (q->rear+1)%QUEUE_SIZE)
    {
        return -1; /* queue is FULL */
    }
    else
    {
        if(q->rear == -1)
        {
            q->front = q->rear = 0; //what??
        }
        else
        {
            q->rear = (q->rear+1)%QUEUE_SIZE;
        }
        
        q->arr[q->rear] = tsk;
    }
    
    return 0;
}

int isEmpty(Cqueue * q)
{
    if(q->front == -1)
    {
        return 1;
    }
    
    return 0;
}

Task * queueRemove(Cqueue * q)
{
    Task * item;
    
    if(q->front == -1)
    {
        return NULL;
    }
    else
    {
        item = q->arr[q->front];
        if(q->front == q->rear)
        {
            q->front = -1;
            q->rear = -1;
        }
        else
        {
            q->front = (q->front+1)%QUEUE_SIZE;
        }
    }
    
    return item;
    
}

/* return front of queue without actually removing it from the queue */
Task * queuePeek(Cqueue * q)
{
    Task * item;
    
    if(q->front == -1)
    {
        return NULL;
    }
    else
    {
        return q->arr[q->front];
        
    }
    
}

#endif
