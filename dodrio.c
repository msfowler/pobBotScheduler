#include "dodrio.h"

int detectedObject [] = {0, 0, 0, 0, 0};
// also a global image

void initCameraAndLCD();

void initRobit()
{
  printf("Initializing robit\n");
}

void rotateLeft() 
{
  printf("Moving robit left\n");
}

// I don't know how many degrees right this rotates
void rotateRight()
{
  printf("Moving robit right\n");
}

// I don't know how far forward this moves the robot
void moveForward()
{
  printf("Moving robit forward\n");
}

// I don'tk now how far backward this moves the robot
void moveBackward()
{
  printf("Moving robit backward\n");
}

// Each of the above rotate/move functions stays ON until stopMovement() is called
void stopMovement()
{
  printf("Stopping robit\n");
}
	
void initCameraAndLCD()
{
  printf("Initializing camera and LCD screen\n");
}

void captureImage()
{
  printf("Capturing image\n");      
}

void decipherImage() 
{
  printf("Decipering image\n");
}
