#include <stdio.h>
#include "omp.h"
#include <time.h>
double Sum(double a[],int start,int end){
	double sum=0;
	for (int i=start;i<end;i++)
		sum=sum+a[i];
	return sum;
}
int main(){
	double a[1000000];
	for (int i=0;i<1000000;i++)
		a[i]=i+1;
	clock_t begin=clock();
	int i=0;
	double b[10];
	int start=0;
	int end=100000;
	#pragma omp parallel num_threads(10)
	{
		b[i]=Sum(a,start,end);
		start=end;
		end=end+100000;
		i++;
		#pragma omp taskwait
	}
	double total=0;
	for (int i=0;i<10;i++)
		total=total+b[i];
	printf("%f",total);
	clock_t end1=clock();
	double timeSpent=(end1-begin)/CLOCKS_PER_SEC;
	printf("\n%f",timeSpent);
}
