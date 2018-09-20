#include "PriorityQueue.hpp"
#include <iostream>
using namespace std;
typedef PriorityQueue::DataType DataType;


PriorityQueue::PriorityQueue(unsigned int capacity )
{
	capacity_ = capacity;
	heap_ = new DataType[capacity_+1];
	size_ = 0;
}

PriorityQueue::~PriorityQueue()
{
	delete[] heap_;
	heap_==NULL;
}

bool PriorityQueue::enqueue( DataType value)
{
	if(full())
		return false;

	heap_[size_+1] = value;
	++size_;


	int index = size_;
	DataType temp = 0;

	while( index > 1 && heap_[index] > heap_[index/2])
	{
		temp = heap_[index];
		heap_[index] = heap_[index/2];
		heap_[index/2] = temp;
		index /= 2;
	}

	return true;
}

bool PriorityQueue::dequeue()
{
	if(empty())
		return false;

	// Switch right-most leaf with root node
	unsigned int index = 1;
	heap_[index] = heap_[size_];
	--size_;

	//Flag
	bool flag = true;
	//Temporary
	DataType temp = 0;

	while( index * 2 <= size_ && flag)
	{
		unsigned int largerChild = index*2;
		if( largerChild+1 <= size_ && heap_[largerChild+1] > heap_[largerChild])
			largerChild += 1;
		if( heap_[largerChild] > heap_[index])
		{
			temp = heap_[index];
			heap_[index] = heap_[largerChild];
			heap_[largerChild] = temp;
			index = largerChild;
		}
		else
			flag = false;
	}
	return true;
}

DataType PriorityQueue::max() const
{
	if( empty() )
		return -1;

	return heap_[1];
}

unsigned int PriorityQueue::size() const
{
	return size_;
}

bool PriorityQueue::empty() const
{
	return size_ == 0;
}

bool PriorityQueue::full() const
{
	return size_ >= capacity_;
}

void PriorityQueue::print() const
{
	if( empty())
		cout << "Empty Queue";
	else
		for( unsigned int i = 1; i <= size_; ++i)
		cout << heap_[i] << " ";
}
