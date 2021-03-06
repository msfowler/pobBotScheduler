//
//  tasks.h
//  scheduler
//
//  Created by Melyssa Son on 3/21/13.
//
//

#ifndef scheduler_tasks_h
#define scheduler_tasks_h

/* Task Function prototypes */

typedef struct
{
    void (*taskFunction)(void);
    int executionTime;
} Task;

extern void * aperiodicQ;
extern void * sporadicQ;
int queueInsert(Task * tsk, void * queue);
int isEmpty(void * queue);
Task * queueRemove(void * queue);
Task * queuePeek(void * queue);

void lookLeft();
void lookRight();
void lookCenter();
void lookLeftCenter();
void lookRightCenter();
void realignCenter();
void captureImgLeft();
void captureImgRight();
void captureImgCenter();
void captureImgLeftCenter();
void captureImgRightCenter();
void decipherImgLeft();
void decipherImgRight();
void decipherImgCenter();
void decipherImgLeftCenter();
void decipherImgRightCenter();
void initiateCrossing();
void crossTrack();
void avoidRobot();
void approachTrack();

#endif
