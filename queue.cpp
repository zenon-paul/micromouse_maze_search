#include"container.h"
#include<stdlib.h>
d_queue::d_queue(int l):leng(l),tail(-1),head(0){
	body = (int*)calloc(leng,sizeof(int));
}
d_queue::~d_queue() {
	free(body);
}
int d_queue::put(int input) {
	if (((tail + 2) % leng) == head) {//((x->tail + 2) % x->leng) >= (x->head)この場合値が二度と入らなくなってしまうので==にしよう
		return 0;
	}
	body[(tail + 1) % leng] = input;
	tail++;
	return 1;
}
int d_queue::get(int* result) {
	if (((tail + 1) % leng) == head) {
		return 0;
	}
	*result = body[head % leng];
	head++;
	return 1;
}
//-------------------------------------------------
d2_queue::d2_queue(int l):leng(l),tail(-1),head(0){
	body = (int*)calloc(leng, sizeof(int));
	index = (int*)calloc(leng, sizeof(int));
}
d2_queue::~d2_queue() {
	free(body);
	free(index);
}
int d2_queue::put(int input, int inputind) {
	if (((tail + 2) % leng) == head) {//((x->tail + 2) % x->leng) >= (x->head)この場合値が二度と入らなくなってしまうので==にしよう
		return 0;
	}
	body[(tail + 1) % leng] = input;
	index[(tail + 1) % leng] = inputind;
	tail++;
	return 1;
}
int d2_queue::get(int* result, int* resultind) {
	if (((tail + 1) % leng) == head) {
		return 0;
	}
	*result = body[head % leng];
	*resultind = index[head % leng];
	head++;
	return 1;
}