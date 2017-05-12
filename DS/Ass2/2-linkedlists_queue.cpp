#include <iostream>
#include <stdlib.h>
using namespace std;

struct node
{
	int value;
	node* link;
};

void Enqueue(int number);
int Dequeue();
void display();
int isempty();

struct node* front=NULL;
struct node* rear=NULL;
int number;

int main()
{
	cout<<"Queue is being implemented using linkedlists.Please select following options"<<endl;
	int option;
	do{
	cout<<"Press 1 for Enqueue \n 2 for Dequeue \n 3 for display \n 4 for exit"<<endl;
	cin>>option;
	switch(option){
		case 1:
				cout<<"Enter an integer u want to Enqueue"<<endl;
				cin>>number;
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
	node* temp=(node*)new node;
	temp->value=number;
	temp->link=NULL;
	if (front==NULL && rear==NULL)
	{
		front=rear=temp;
		return;
	}
	rear->link=temp;
	rear=temp;
}

int Dequeue(){
	node* temp=front;
	if (front==rear)
	{
		front=rear=NULL;
		number=temp->value;
		delete(temp);
	}
	else{
	front=temp->link;
	number=temp->value;
	delete(temp);
	}
	return number;

}

int isempty(){
	if(front==NULL)
		return 1;
	else 
		return 0;
}
void display(){
	node* temp=front;
	if(isempty()){
		cout<<"Empty queue"<<endl;
		return;
	}
	else{
		cout<<"Elements in circular queue are "<<endl;
	while(temp!=NULL){
		cout<<temp->value<<" ";
		temp=temp->link;
	}
	cout<<endl;
}
}