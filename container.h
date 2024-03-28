#pragma once


//----------stack.cpp-----------------------------
class d_stack {
private:
	int tail;
	int leng;//この値はindexではなくデータの個数とする
public:
	int* body;
	d_stack(int l);
	~d_stack();
	int push(int input);
	int get(int* result);
	int get_len();
};

class d2_stack {
private:
	int tail;
	int leng;//この値はindexではなくデータの個数とする
	int* body;
	int* index;
public:
	d2_stack(int l);
	~d2_stack();
	int push(int input, int inputind);
	int get(int* result, int* resultind);
};

//----------queue.cpp-----------------------------
class d_queue {
private:
	int head;
	int tail;
	int leng;
	int* body;
public:
	d_queue(int l);
	~d_queue();
	int put(int input);
	int get(int* result);

};

class d2_queue {
private:
	int head;
	int tail;
	int leng;
	int* body;
	int* index;
public:
	d2_queue(int l);
	~d2_queue();
	int put(int input, int inputind);
	int get(int* result, int* resultind);
};


//----------priority_queue.cpp-------------------
class d_prqueue {
private:
	int size;
	int tail;
	int* body;
public:
	d_prqueue(int s);
	~d_prqueue();
	void make_heap(int broad);
	void remake_heap(int broad);
	int put_check();
	int get_check();
	int put(int y);
	int get(int* y);
};

class d2_prqueue {
private:
	int size;
	int tail;
	int* body;
	int* index;
public:
	d2_prqueue(int s);
	~d2_prqueue();
	void make2_heap(int broad);
	void remake2_heap(int broad);
	int put2_check();
	int get2_check();
	int put(int y, int i);
	int get(int* y, int* i);
};
