//Simple SDL2 threads example

//Program creates 2 threads which increment their parameter by 1.

#include <iostream>
#include <SDL.h>

//increments a by 1 every 1 sec.
static int threadFunction1(void* ptr)
{
	int* ptr2 = (int*) ptr;

	int i = 0;
	for (i = 0; i < 25; i++)
	{
		*ptr2 = *ptr2 + 1;
		SDL_Delay(1000);
	}
	return 0;
}

//increments b by 1 every 2 sec.
static int threadFunction2(void* ptr)
{
	int* ptr2 = (int*)ptr;
	int i = 0;
	for (i = 0; i < 25; i++)
	{
		*ptr2 = *ptr2 + 1;
		SDL_Delay(2000);
	}
	SDL_Delay(2000);
	return 0;
}

int main(int argc,char* args[]){	
	SDL_Thread* thread1;
	SDL_Thread* thread2;

	printf("Simple threads example!!!\n\n");

	int a = 0;
	int b = 0;

	int stop = false;

	//create threads
	thread1 = SDL_CreateThread(threadFunction1, "T1", &a);
	thread2 = SDL_CreateThread(threadFunction2, "T2", &b);

	int ret1 = 1;
	int ret2 = 1;
	
	while (stop == false)
	{
		printf("a (thread1): %d\nb (thread2): %d\n", a, b);
		SDL_Delay(500);

		if (a > 20)
		{
			stop = true;
		}
	}

	printf("Waiting for threads to finish ... ");
	if (thread1 == NULL)
	{
		printf("in creating thread");
		exit(EXIT_FAILURE);
	}
	else
	{
		SDL_WaitThread(thread1, &ret1);
	}

	if (thread2 == NULL)
	{
		printf("in creating thread");
		exit(EXIT_FAILURE);
	}
	else
	{
		SDL_WaitThread(thread2, &ret2);
	}

	return 0;
}




