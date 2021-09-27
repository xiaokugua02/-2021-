//#include<iostream>
#include<stdio.h>
typedef struct Point
{
	unsigned long y_i;
	unsigned long x_i;
}Line;
int main()
{
	int number_line = 0;
	int number_point = 0;
	//std::cin >> number_line >> number_point;
	scanf("%d %d", &number_line, &number_point);
	Point* L = new Point[number_line + number_point];
	Point* P = &L[number_line];
	for (int i = 0; i < number_line; i++)
	{
		//std::cin >> L[i].x_i >> L[i].y_i;
		scanf("%lu %lu", &L[i].x_i , &L[i].y_i);
	}
	for (int i = 0; i < number_point; i++)
	{
		//std::cin >> P[i].x_i >> P[i].y_i;
		scanf("%lu %lu", &P[i].x_i, &P[i].y_i);
	}
	for (int i = 0; i < number_point; i++)
	{	
		int lo = 0;
		int hi = number_line;
		while (lo < hi)
		{
			int mi = (lo + hi) >> 1;
			P[i].x_i* L[mi].y_i + P[i].y_i * L[mi].x_i < L[mi].y_i* L[mi].x_i ?
				hi = mi : lo = mi + 1;
		}
		//std::cout << lo << '\n';
		printf("%d\n", lo);
	}
	delete[] L;
	return 0;
}