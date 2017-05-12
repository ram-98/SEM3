#include <iostream>
#include<math.h>
#include<malloc.h>
using namespace std;

struct student
{
	string name;
	string rollnumber;
	int age;
	string gender;
};

int main()
{
	int size;
	cout<<"enter no of students"<<endl;
	cin>>size;
	struct student array[size];
	for (int i = 0; i < size; i++)
	{
		cout<<"Enter name of "<<i+1<<" student "<<endl;
		cin>>array[i].name;
		cout<<"Enter rollnumber of "<<i+1<<" student "<<endl;
		cin>>array[i].rollnumber;
		for (int j = 0; j <i; j++)
		{
			if(array[i].rollnumber==array[j].rollnumber){
				cout<<"Roll number duplicacy is found.Enter a Unique rollnumber"<<endl;
				exit(0);
			}
		}
		cout<<"Enter age of "<<i+1<<" student "<<endl;
		cin>>array[i].age;
		cout<<"Enter Gender of "<<i+1<<" student "<<endl;
		cin>>array[i].gender;
	}
	void display()

	return 0;
}