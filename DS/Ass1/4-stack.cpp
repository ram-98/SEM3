#include <iostream>
#include <stdlib.h>
#define SIZE 5
using namespace std;

int stack[SIZE];
int top=-1,number;

void push(int number);
int pop();
int isempty();
int isfull();
void display();

int main()
{
	int option;
	cout<<"Stack with max SIZE "<<SIZE <<",using arrays is being implemented .Please select following options"<<endl;
	do{
	cout<<"\n******Press 1 for Push *******\n********Press 2 for Pop*********\n*******Press 3 for display ********\n *******Press 4 for exit******\n"<<endl;
	cin>>option;
	switch(option){
		case 1:
				if (isfull()){
					cout<<"Stack is full"<<endl;
					}
				else{
				cout<<"Enter an integer u want to push"<<endl;
				cin>>number;
				push(number);
				}
				break;
		case 2:
				if(isempty()){
					cout<<"Stack is empty "<<endl;
				}
				else{
				number =pop();
				cout<<"The element Popped is "<<number<<endl;
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
void push(int number){
	top=top+1;
	stack[top]=number;
	return;
}
int pop(){
	number=stack[top];
	top=top-1;
	return number;
}
int isempty(){
	if(top==-1){
		return 	1;
	}
	else{
		return 0;
	}
}
int isfull(){
	if(top==4){
		return 1;
	}
	else
		return 0;
}
void display(){
		if(isempty()){
		cout<<"Empty stack"<<endl;
		return;
	}
	else{
		cout<<"Elements in stack are "<<endl;
		for (int i = 0; i <=top; i++)
		{
			cout<<stack[i]<<" ";
		}
		cout<<endl;
	}
}