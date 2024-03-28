#include"container.h"
#include<stdlib.h>
int chmin(int a, int b) {
	if (a < b)
	{
		return 1;
	}
	else return 0;
}
int chmax(int a, int b) {
	if (a > b)
	{
		return 1;
	}
	else return 0;
}
void swap(int* x, int* y) {
	int restnum;
	restnum = *x;
	*x = *y;
	*y = restnum;
}
d_prqueue::d_prqueue(int s):size(s),tail(0){
	body = (int*)calloc(size,sizeof(int));
}
d_prqueue::~d_prqueue() {
	free(body);
}
void d_prqueue::make_heap(int broad) {
	for (int i = broad; i > 0;)
	{
		if (chmax(body[i], body[(i - 1) / 2]))//親　＜　子
		{
			break;
		}
		else
		{
			swap(&(body[(i - 1) / 2]), &(body[i]));
			i = (i - 1) / 2;
		}
	}
}
void d_prqueue::remake_heap(int broad) {
	for (int i = 0; (2 * i + 1) <= broad;)
	{
		if (2 * i + 2 <= broad) {
			if (chmax(body[2 * i + 1], body[2 * i + 2]))
			{
				if (chmax(body[i], body[2 * i + 2]))
				{
					swap(&(body[2 * i + 2]), &(body[i]));
					i = 2 * i + 2;
				}
				else
				{
					break;
				}
			}
			else
			{
				if (chmax(body[i], body[2 * i + 1]))
				{
					swap(&(body[2 * i + 1]), &(body[i]));
					i = 2 * i + 1;
				}
				else
				{
					break;
				}

			}
		}
		else
		{
			if (chmax(body[i], body[2 * i + 1]))
			{
				swap(&(body[2 * i + 1]), &(body[i]));
				i = 2 * i + 1;
			}
			else
			{
				break;
			}
		}
	}
}
int d_prqueue::put_check() {
	if (size <= tail)
	{
		return 1;
	}
	return 0;
}
int d_prqueue::get_check() {
	if (0 >= tail)
	{
		return 1;
	}
	return 0;
}
int d_prqueue::put(int y) {
	if (put_check())
	{
		return 0;
	}
	body[tail] = y;
	tail++;
	make_heap(tail - 1);
	return 1;
}
int d_prqueue::get(int* y) {
	if (get_check())
	{
		return 0;
	}
	*y = body[0];
	body[0] = body[tail - 1];
	tail--;
	remake_heap(tail - 1);
	return 1;
}
//--------------------------------------------------------------------------
d2_prqueue::d2_prqueue(int s):size(s),tail(0) {
	body = (int*)calloc(size,sizeof(int));
	index = (int*)calloc(size, sizeof(int));
}
d2_prqueue::~d2_prqueue() {
	free(body);
	free(index);
}
void d2_prqueue::make2_heap(int broad) {
	for (int i = broad; i > 0;)
	{
		if (chmax(body[i], body[(i - 1) / 2]))
		{
			break;
		}
		else
		{
			swap(&(body[(i - 1) / 2]), &(body[i]));
			swap(&(index[(i - 1) / 2]), &(index[i]));
			i = (i - 1) / 2;
		}
	}
}
void d2_prqueue::remake2_heap(int broad) {
	for (int i = 0; (2 * i + 1) <= broad;)
	{
		if (2 * i + 2 <= broad) {
			if (chmax(body[2 * i + 1], body[2 * i + 2]))
			{
				if (chmax(body[i], body[2 * i + 2]))
				{
					swap(&(body[2 * i + 2]), &(body[i]));
					swap(&(index[2 * i + 2]), &(index[i]));
					i = 2 * i + 2;
				}
				else
				{
					break;
				}
			}
			else
			{
				if (chmax(body[i], body[2 * i + 1]))
				{
					swap(&(body[2 * i + 1]), &(body[i]));
					swap(&(index[2 * i + 1]), &(index[i]));
					i = 2 * i + 1;
				}
				else
				{
					break;
				}

			}
		}
		else
		{
			if (chmax(body[i], body[2 * i + 1]))
			{
				swap(&(body[2 * i + 1]), &(body[i]));
				swap(&(index[2 * i + 1]), &(index[i]));
				i = 2 * i + 1;
			}
			else
			{
				break;
			}
		}
	}
}
int d2_prqueue::put2_check() {
	if (size <= tail)
	{
		return 1;
	}
	return 0;
}
int d2_prqueue::get2_check() {
	if (0 >= tail)
	{
		return 1;
	}
	return 0;
}
int d2_prqueue::put(int y, int i) {
	if (put2_check())
	{
		return 0;
	}
	body[tail] = y;
	index[tail] = i;
	tail++;
	make2_heap(tail - 1);
	return 1;
}
int d2_prqueue::get(int* y, int* i) {
	if (get2_check())
	{
		return 0;
	}
	*y = body[0];
	*i = index[0];
	body[0] = body[tail - 1];
	index[0] = index[tail - 1];
	tail--;
	remake2_heap(tail - 1);
	return 1;
}