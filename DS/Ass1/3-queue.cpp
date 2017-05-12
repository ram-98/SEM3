#include <iostream>
#include <stdlib.h>
#define SIZE 5
using namespace std;

int c_array[SIZE];
int front =-1,rear=-1,number;

void Enqueue(int number);
int Dequeue();
void display();
int isfull();
int isempty();

int main()
{
	cout<<"Circular queue with max SIZE "<<SIZE<<"is being implemented .Please select following options"<<endl;
	int option;
	do{
	cout<<"Press 1 for Enqueue \n 2 for Dequeue \n 3 for display \n 4 for exit"<<endl;
	cin>>option;
	switch(option){
		case 1:
				Enqueue(number);
				break;
		case 2:
				if(isempty()){
					cout<<"Queue is empty "<<endl;
				}
				else{
				number =Dequeue();
				cout<<"The element deleted is "<<number<<endl;
				}
				break;
		case 3:
				display();
				break;
		case 4:
				cout<<"Exiting the program"<<endl;
				exit(0);
		default:
				cout<<"Invalid option"<<endl;
	}
	}while(1);

	return 0;

}

void Enqueue(int number){
		if (isfull())
		{
			cout<<"Circular queue is full"<<endl;
			return;
		}
		else if (isempty()){
			front=0;
			rear=0;
		}
		else{
			rear=(rear+1)%SIZE;
		}
		cout<<"Enter an integer u want to Enqueue"<<endl;
		cin>>number;
		c_array[rear]=number;	
		return;
}
int Dequeue(){
		if(front==rear){
			number=c_array[front];
			front=-1;
			rear=-1;
			return number;
		}
		else{
			number=c_array[front];
			front=(front+1)%SIZE;
			return number;
		}

}
int isfull(){
	if ((rear+1)%SIZE==front)
		return 1;
	else
		return 0;
}
int isempty(){
	if(front==-1)
		return 1;
	else
		return 0;
}
void display(){
	if(isempty()){
		cout<<"Empty queue"<<endl;
		return;
	}
	else{
		cout<<"Elements in circular queue are "<<endl;
		for (int i = front; i <=rear; i++)
		{
			cout<<c_array[i]<<" ";
		}
		cout<<endl;
	}
}
