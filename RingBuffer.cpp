#include <iostream>
#include <chrono>
#include <thread>
#include <windows.h>

using namespace std;
using namespace chrono;
using namespace this_thread;

#define BUFSIZE 8

#define PI 3.141592
#define SECOND_MILISECOND 1000


#define TIME_INTERVAL 10
#define SIMULATION_TIME 20000

#define DATA_CREATE_AVERAGE 3
#define DATA_CREATE_SIGMA 0.2

#define DATA_PROCESS_AVERAGE 3
#define DATA_PROCESS_SIGMA 0.2

bool stopFlag = false;

struct Buffer
{
	int *data;
	int dataCreate = 0;
	int dataProcess = 0;
};
typedef struct Buffer RingBuffer;

double Gaussian(double time, double T, double sigma);
void createData(RingBuffer *buf);
void processData(RingBuffer *buf);

double Gaussian(double time, double T, double sigma)
{
	double s = 2.0 * sigma * sigma;
	return (exp(-((time - T)*(time - T)) / s)) / sqrt(PI * s);
}

void createData(RingBuffer *buf)
{
	int index = 0;
	int cData = 0;
	double timeSum = 0;
	double accumulate_probablity = 0;
	double create_probability = 0;

	while (!stopFlag) 
	{
		srand( GetTickCount() );
		milliseconds time(TIME_INTERVAL);
		sleep_for(time);

		timeSum += TIME_INTERVAL;
		accumulate_probablity += Gaussian(timeSum/ SECOND_MILISECOND, DATA_CREATE_AVERAGE, DATA_CREATE_SIGMA);
		
		create_probability = rand() % 1000;
		
		if (create_probability < accumulate_probablity * SECOND_MILISECOND)
		{
			if (buf->dataCreate - buf->dataProcess >= BUFSIZE) printf("FAIL : DATA CREATE OVER!\n");
			else {
				buf->data[index] = cData;
				printf("SUCCESS : DATA CREATE : %d\n", cData);

				index = (index + 1) % BUFSIZE;
				buf->dataCreate++;
			}
			accumulate_probablity = 0;
			timeSum = 0;
			cData++;
		}
	}
}

void processData(RingBuffer *buf)
{
	int index = 0;
	int pData = 0;
	double timeSum = 0;
	double accumulate_probablity = 0;
	double process_probability = 0;

	while (!stopFlag) 
	{
		srand(GetTickCount());
		milliseconds time(TIME_INTERVAL);
		sleep_for(time);

		timeSum += TIME_INTERVAL;
		accumulate_probablity += Gaussian(timeSum / SECOND_MILISECOND, DATA_PROCESS_AVERAGE, DATA_PROCESS_SIGMA);

		process_probability = rand() % 1000;

		if (process_probability < accumulate_probablity * SECOND_MILISECOND)
		{
			if (buf->dataCreate - buf->dataProcess <= 0)  printf("FAIL : DATA PROCESS OVER!\n");
			else {
				pData = buf->data[index];
				printf("SUCCESS : DATA  PROCESS : %d\n", pData);

				index = (index + 1) % BUFSIZE;
				buf->dataProcess++;
			}
			accumulate_probablity = 0;
			timeSum = 0;
		}	
	}
}

int main()
{
	RingBuffer *buf;
	buf = (RingBuffer*)malloc(sizeof(RingBuffer));
	buf->data = (int*)malloc(sizeof(int)*BUFSIZE);

	thread Thread1(createData, buf);
	thread Thread2(processData, buf);

	printf("Start\n");

	milliseconds time(SIMULATION_TIME);
	sleep_for(time);

	stopFlag = true;

	Thread1.join();
	Thread2.join();
	
	printf("Finish\n");
	system("pause");
	
	return 0;
}
