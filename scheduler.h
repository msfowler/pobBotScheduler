//
//  scheduler.h
//  scheduler
//
//  Created by Melyssa Son on 3/21/13.
//
//

#ifndef scheduler_scheduler_h
#define scheduler_scheduler_h


#include "tasks.h"


#define FRAMES 4                /* Frames per hyperperiod */
#define FRAME_SIZE 10
#define MAX_TASKS_PER_FRAME 10  /* Maximum periodic tasks per frame */
#define QUEUE_SIZE 20

extern Task lookLeftTask;
extern Task lookRightTask;
extern Task lookCenterTask;
extern Task lookLeftCenterTask;
extern Task lookRightCenterTask;
extern Task realignCenterTask;
extern Task captureImgLeftTask;
extern Task captureImgRightTask;
extern Task captureImgCenterTask;
extern Task captureImgLeftCenterTask;
extern Task captureImgRightCenterTask;
extern Task decipherImgLeftTask;
extern Task decipherImgRightTask;
extern Task decipherImgCenterTask;
extern Task decipherImgLeftCenterTask;
extern Task decipherImgRightCenterTask;
extern Task initiateCrossingTask;
extern Task crossTrackTask;
extern Task avoidRobotTask;
extern Task approachTrackTask;

/* A two dimensional array of Task pointers of the task schedule
 Each row corresponds to a frame. The row contains pointers to the
 tasks to be exectuted in the frame in order. The last task to be
 executed should be followed by NULL. Denoted by L(k) on page 91
 in the book by Liu. */
Task * tasks[FRAMES][MAX_TASKS_PER_FRAME] =
{   /* Frame 1*/ {&lookLeftTask, &captureImgLeftTask, &lookLeftCenterTask, &captureImgLeftCenterTask, &lookCenterTask, NULL, NULL, NULL, NULL, NULL},
    /* Frame 2*/ {&captureImgCenterTask, &lookRightCenterTask, &captureImgRightCenterTask, &lookRightTask, &captureImgRightTask, &decipherImgLeftTask, &decipherImgLeftCenterTask, &decipherImgCenterTask, NULL, NULL},
    /* Frame 3*/ {&decipherImgRightCenterTask, &decipherImgRightTask, &realignCenterTask, &initiateCrossingTask, NULL, NULL, NULL, NULL, NULL, NULL},
    /* Frame 4*/ {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL}
};


/* APERIODIC and SPORADIC queues */
typedef struct
{
    Task * arr[QUEUE_SIZE];
    int rear;
    int front;
}Cqueue;

Cqueue _aperiodicQ = { .rear = -1, .front = -1};
Cqueue _sporadicQ = { .rear = -1, .front = -1};

void * aperiodicQ = (void *)&_aperiodicQ;
void * sporadicQ = (void *)&_sporadicQ;

void scheduler();


/***************** QUEUE OPERATIONS *************************/

/* Insert a task into the queue*/ 
int queueInsert(Task * tsk, void * queue)
{
    Cqueue * q = (Cqueue *)queue; 
    
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

int isEmpty(void * queue)
{
    Cqueue * q = (Cqueue *)queue; 
    if(q->front == -1)
    {
        return 1;
    }
    
    return 0;
}

/* remove a task from the queue */ 
Task * queueRemove(void * queue)
{
    Task * item;
    Cqueue * q = (Cqueue *)queue;
    
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
Task * queuePeek(void * queue)
{
    Task * item;
    Cqueue * q = (Cqueue *)queue;
    
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
