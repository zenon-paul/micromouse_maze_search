#include"container.h"
#include<stdlib.h>
d_stack::d_stack(int l):leng(l),tail(-1){
	body = (int*)calloc(leng,sizeof(int));
}
d_stack::~d_stack() {
	free(body);
}
int d_stack::push(int input) {
	if ((tail + 1) > (leng - 1)) {
		return 0;
	}
	body[tail + 1] = input;
	tail++;
	return 1;
}
int d_stack::get(int* result) {
	if (tail < 0) {
		return 0;
	}
	*result = body[tail];
	tail--;
	return 1;
}
int d_stack::get_len() {
	return tail;
}
//-------------------------------------------------
d2_stack::d2_stack(int l):leng(l) {
	body = (int*)calloc(leng,sizeof(int));
	index = (int*)calloc(leng, sizeof(int));
}
d2_stack::~d2_stack() {
	free(body);
	free(index);
}
int d2_stack::push(int input, int inputind) {
	if ((tail + 1) > (leng - 1)) {
		return 0;
	}
	body[tail + 1] = input;
	index[tail + 1] = inputind;
	tail++;
	return 1;
}
int d2_stack::get(int* result, int* resultind) {
	if (tail < 0) {
		return 0;
	}
	*result = body[tail];
	*resultind = index[tail];
	tail--;
	return 1;
}
