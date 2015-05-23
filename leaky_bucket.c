/*
Implementing a basic leaky bucket algorithm.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


//int time = 0;
int current_amt = 0;

void bucketInput(int a, int b, int size){
	current_amt += a;
	if (current_amt > size){
		printf("\tBucket overflow.\n");
		current_amt -= a;
	}
	else{
		//time++;
		current_amt -= a;
		while(a>b){
			//printf("Time: %d seconds\n", time);
			printf("\t%d bytes outputted\n", b);
			a -=b;
			//time++;
		}
		//printf("Time: %dseconds\n", time);
		if (a>0)
			printf("\tLast %d bytes sent", a);
		printf("\tBucket output successful.\n");
		

	}

}

int main(){
	FILE *fp;
	int time_ms, length;
	int leakRate, packetSize, bucketSize;

	fp = fopen("jurrassic_1.txt", "r");

	printf("Bucket Size (in byte, i.e 8000): ");
	scanf("%d", &bucketSize);
	printf("Leak Rate: ");
	scanf("%d", &leakRate);

	if (fp == NULL){
		fprintf(stderr, "Can't open input file jurassic.txt.\n");
		exit(1);
	}
	else{
		int i = 0;
		while(fscanf(fp, "%d %d", &time_ms, &length) != EOF){
			packetSize = length;
			printf("Packet no %d\t Packet size = %d\n", i, packetSize);
			i++;
			bucketInput(packetSize, leakRate, bucketSize);
		}
	}
	fclose(fp);
	return 0;
}