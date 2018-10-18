#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
// Globally Initialized Array of size 1000
int Array[1000];
// Structure to pass across Function
struct Combo{
	int start,end;
};
// Sum Function
void * Sum(void *something){
	struct Combo A1=*(struct Combo*)something;
	int Total_sum=0;
	for (int i=A1.start;i<A1.end;i++)
		Total_sum=Total_sum+Array[i];
	return ((void*)Total_sum);
}
// Main Function
int main(){
	// Loop to initialize with 1 to 1000
	for (int i=0;i<1000;i++)
		Array[i]=i+1;
	// Create an array of 100 of Combo Structure
	struct Combo A1[10];
	int GetValue[10];
	// Create an array of threads of size 10
	pthread_t thread_t1[10];
	// Initialize combo structure and pass to creation of process
	for (int i=0;i<10;i++){
		A1[i].start=100*i;
		A1[i].end=(100*i)+100;
		pthread_create(&thread_t1[i],NULL,Sum,(void*)&A1[i]);
	}
	// Wait for all Threads for completion
	for (int i=0;i<10;i++)
		pthread_join(thread_t1[i],(void **)& GetValue[i]);
	// Sum of values return from threads
	int Total=0;
	for (int i=0;i<10;i++)
		Total=Total+GetValue[i];
	// Print the Total Sum
	printf("\nTotal Sum from all threads is : %d\n\n",Total);
	return 0;
}
