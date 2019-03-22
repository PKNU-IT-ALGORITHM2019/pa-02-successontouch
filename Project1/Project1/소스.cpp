#include <stdio.h>
#pragma warning (disable:4996)
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define MAX 20

typedef struct dot {
	int index;
	int x;
	int y;
}dot;
dot array[MAX];

int check[MAX];
int num;
double min;
double cur=0;
double sum = 0;

void swap(int i, int j)
{
	dot tmp = array[i];
	array[i] = array[j];
	array[j] = tmp;
}

double distance_calculate(dot data1, dot data2)
{
	return sqrt((data1.x - data2.x)*(data1.x - data2.x) + (data1.y - data2.y)*(data1.y - data2.y));
}

double distance(int index)
{
	double tmp_sum = 0;
	if (index == num - 1) {
		tmp_sum += distance_calculate(array[index], array[0]);
		return tmp_sum;

	}
	tmp_sum += distance_calculate(array[index], array[index + 1]);
	
	return tmp_sum;
}

double tsp(int k) 
{
	
	if (k == num) {
		sum=0;
		
		for (int i = 0; i < num; i++) {
			//printf("%d ", array[i].index);
			double tmp = distance(i);
			sum += tmp;
			if (cur != 0) {
				if (sum > min)
					return 0;
			}
		}

		if (cur == 0) { //맨 처음 min
			min = sum;
			cur++;
		}

		if (min > sum) {  //min이 sum보다 크면 
			min = sum;
			for (int i = 0; i < num; i++) {
				check[i] = array[i].index;
			}
		}
		//printf("%lf", sum);
		//printf("\n");
		return 0;
	}
	

	for (int i = k; i < num; i++) {
	
		swap(k, i);
		tsp(k + 1);
		
		swap(k, i);
	}
	
}


void main()
{
	clock_t start, end;
	srand((unsigned)time(NULL));
	start = clock();
	FILE *read_fp = fopen("input3.txt", "r");
	fscanf(read_fp, "%d",&num );

	for (int i = 0; i < num; i++) {
		array[i].index = i;
		fscanf(read_fp, "%d %d", &array[i].x, &array[i].y);
	}
	fclose(read_fp);
	
	tsp(0);
	for (int i = 0; i < num; i++) {
		printf("%d ", check[i]);
	}
	printf("최솟값 %lf", min);
	end = clock();

	printf("\n걸린 시간:%.3lf초", (end - start)/ (double)1000);
	
	getchar();
	getchar();

}