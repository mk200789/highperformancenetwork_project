#include <stdio.h>

#define MAX 5

int queue_array[MAX];
int rear = -1;
int front = -1;

void insert_queue(x)
int x;
{
	if(rear == MAX - 1){
		printf("overflow\n");
	}
	else{
		if (front == -1){
			/* if queue initially empty*/
			front = 0;
		}
		rear += 1;
		queue_array[rear] = x;
	}
}

void remove_queue()
{
	if (front == -1 || front > rear){
		printf("underfow\n");
	}
	else{
		queue_array[front] = 0;
		front = front + 1;
	}
}

void display_queue(){
	printf("|");
	for (int i=0; i<=rear; i++){
		printf("%d| ", queue_array[i]);
	}
	printf("\n");
}


int main(){
	printf("Size of the array is: %lu\n", sizeof(queue_array));
	insert_queue(10);
	insert_queue(40);
	display_queue();
	remove_queue();
	display_queue();
	insert_queue(15);
	insert_queue(45);
	display_queue();
	remove_queue();
	display_queue();
}