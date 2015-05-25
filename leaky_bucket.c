/*
Implementing a basic leaky bucket algorithm.
*/

/*
INCLUDES
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

/*
DEFINES
*/
#define INPUT_FILE "jurrassic_1.txt"
#define OUTPUT_FILE "shape.txt"
#define BUCKET_SIZE 5000
#define TRUE 1
#define FALSE 0

/*
PROTOTYPES
*/
int bucketInput(int, int);

/* 
GLOBAL
*/
int counter = 0;

int bucketInput(int a, int b){
	if (a > BUCKET_SIZE){
		printf("\tBucket overflow.\n");
		return TRUE;
	}
	else{
		while(a>b){
			printf("\t%d bytes outputted\n", b);
			a -=b;
			counter++;
			sleep(1);
		}

		if (a>0)
			printf("\tLast %d bytes sent", a);
		printf("\tBucket output successful.\n");
		
	return FALSE;
	}

}


int main(){
	time_t start_time;
	FILE *fp, *sp;
	int time_ms, length, i, old_counter, current_time, overflow;
	int leakRate, packetSize, delay;

	fp = fopen(INPUT_FILE, "r");
	sp = fopen(OUTPUT_FILE, "w");
	//fprintf(sp, "Packet No. Delay Packet Size\n");

	printf("Leak Rate: ");
	scanf("%d", &leakRate);

	
	if (fp == NULL){
		fprintf(stderr, "Can't open input file jurassic.txt.\n");
		exit(1);
	}
	else{
		i = 1;
		old_counter = 0;
		start_time = time(NULL);
		while(fscanf(fp, "%d %d", &time_ms, &length) != EOF){
			current_time = (time(NULL)-start_time);
			counter = 0;
			while (current_time != time_ms/40 && time_ms <=current_time){
				printf("current_time %ld\n", (time(NULL)-start_time));
				printf("time_ms %d\n", time_ms/40);
				printf("hello\n");
				counter++;
				sleep(1);
				current_time = (time(NULL)-start_time);
				//printf("looping %d %d\n", current_time, time_ms/40);
			}

			//printf("bingo %d %d\n", current_time, time_ms/40);
			//old_counter = counter;
			packetSize = length;
			printf("Packet no %d\t Packet size = %d\n", i, packetSize);
			overflow = bucketInput(packetSize, leakRate);
			if (overflow == 0){
				fprintf(sp, "%d\t\t\t%d\t\t\t%d\n", i, (int)(counter-old_counter), packetSize);
			}
			else{
				fprintf(sp, "%d\t\t\t%s\t\t\t%d\n", i, "-", packetSize);
			}
			i++;
		}

	}
	fclose(fp);
	fclose(sp);
	return 0;
}