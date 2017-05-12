#include<iostream>
#include<string.h>
#include<cstdlib>

using namespace std;

struct node                        //struct for node of a hash table
{
	int key;
	string name;
	char rollno[25];
	int flag;
	int flag2;// for checking if the record is deleted or not
};

struct node  arr[32];
int array[32];
int count=0;

int convert_integer(char *rollno)       //function that returns the key value
{
	int sum=0;
	int key;
	for(int j=0;j<strlen(rollno);j++)
	{
		sum=sum + rollno[j];
	}
	key=sum % 32;
	//cout<<" Key is :"<<key<<endl;
	return key;
}

void insert(string name, char*rollno)          //function to insert the new Record in to hash table
{   count++;
	int k;
	k=convert_integer(rollno);
	if(arr[k].flag==0)
	{	
		arr[k].name=name;
		strcpy(arr[k].rollno,rollno);
		arr[k].flag=1;
		arr[k].flag2=1;
	}
	else
	{
		while(arr[k].flag!=0)
		{
			k++;
			k=k%32;
		}
		arr[k].name=name;
		strcpy(arr[k].rollno,rollno);
		arr[k].flag=1;
		arr[k].flag2=1;
	}
	return;
}

int search(char*rollno)             //function to search for a Record in the hash table
{
	int k,f=0;
	k=convert_integer(rollno);
	if(arr[k].flag==0 && arr[k].flag2==0)
	{
		cout<<"Record not found"<<endl;
		return 1;
	}
	if(arr[k].flag==0 && arr[k].flag2==1)
	{
		cout<<"Record not found"<<endl;
		return 1;
	}
	for(int j=0;j<32;j++)    
	{
		array[j]=0;
	}
	while(arr[k].flag2!=0)
	{
		int p=0;
		for(int j=0;j<32;j++)                //an array with all 1's means that table is full and required record is not found
		{
			if(array[j]==1)
			{
				p++;
			}
		}
		if(p==32)
		{
			cout<<"Record not found"<<endl;
			return 1;
		}
		else
		{
			if((!strcmp(arr[k].rollno,rollno)) && arr[k].flag!=0)
			{
				f++;
				cout<<"Record is found \n";
				return 0 ;
			}
			else
			{
				k++;
				k=k%32;
				array[k]=1;
			}
		}
	}
	if(f==0)
	{
		cout<<"Record is not found \n";
		return 1;
	}
	return 0;	
}
  
void display()                     //function to print all the records in hash table
{
	cout<<"List is :"<<endl;
	for(int i=0;i<32;i++)
	{
		if(arr[i].flag==1)
		{
			cout<<"key is :"<<arr[i].key<<endl;
			cout<<"Name is :"<<arr[i].name<<endl;
			cout<<"roll no is :"<<arr[i].rollno<<endl;
			cout<<"\n\n";
		}
	}
	return;
}

void assign_key()
{
	for(int i=0;i<32;i++)
	{
		arr[i].key=i;
		arr[i].flag=0;
		arr[i].flag2=0;
	}
	return ;
}


void del(char*rollno)              //function to delete a record from the hash table
{	
	count--;
	int k;
	k=convert_integer(rollno);
	if(!strcmp(arr[k].rollno,rollno)) 
	{
		arr[k].flag=0;
		arr[k].flag2=1;
		cout<<"Record deleted"<<endl;
		return;
	}
	else
	{
		while(arr[k].flag2!=0)
		{
			if(!strcmp(arr[k].rollno,rollno)) 
			{
				arr[k].flag=0;
				arr[k].flag2=1;
				cout<<"Record deleted\n";
				return  ;
			}
			else
			{
				k++;
				k=k%32;
			}
		}
	}
	return ;
}

int main()
{
	assign_key();
	string name;
	char rollno[25];
	int n,j=1,k;
	while(j>0)
	{
		cout<<"Enter 1 to insert a record \n";
		cout<<"Enter 2 to delete a record \n";
		cout<<"Enter 3 to search for a record \n";
		cout<<"Enter 4 to print the list\n";
		cout<<"Enter 5 to exit \n";
		cin>>n;
		switch(n)
		{
			case 1 :
				cout<<"***** the record to be inserted *****\n";
				cout<<"Enter the name of the person\n";
				cout<<"Enter the roll number \n";
				cin>>name;
				cin>>rollno;
				if(count>=23)
				{
					cout<<"Table is full and cannot be inserted\n";
				}
				k=search(rollno);
				if(k==1 && count<32)
				{
					insert(name,rollno);
				}
				else
				{
					cout<<"This roll no already exits and two persons with same roll no cannot be present\n";
				}
				break;
				
			case 2:
				cout<<"Enter the roll number of the record to be deleted \n";
				cin>>rollno;
				k=search(rollno);
				if(k==0)
				{
					del(rollno);
				}
				else
				{
					cout<<"No such record to delete"<<endl;
				}
				break;
				
			case 3:
				cout<<"Enter the roll number of the record to search \n";
				cin>>rollno;
				search(rollno);
				break;
				
			case 4:
				display();
				break;
				
			case 5:
				exit(j);
				
			
			default :
				cout<<"Wrong input ...\n";
		}
	}
	
}
