//program for hashtables using auxillary linked lists 
#include "iostream"
#include "string"
using namespace std;

class node{
   public:
        bool b;
        string k;
        int index;
};
class hash{
    public:
          node a[100];
          node b[100];
          void insert(string k);
          void search(string k);
          void del(string k);
          void start();
          int size;
          int hash_function(string k);
};
void hash::start()
{
  size=0;
  for(int i=0;i<100;i++)
     a[i].index=b[i].index=-1;
}
int hash::hash_function(string k)
{
       int a,hv=0,ret;
       for(int i=0;i<k.length();i++)
       {
          a=k[i];
          hv=hv+a;
       }
       ret=hv%100;
       return ret;   
}
//function to insert new record
void hash::insert(string k)
{
  int h,ph;
  h=hash_function(k);
  if(a[h].b==false)
  {
    a[h].b=true;
    a[h].k=k;
    a[h].index=-1;
   }
  else if(a[h].b==true)
  {
     if(a[h].index==-1)
     {
      b[size].b=true;
      b[size].index=-1;
      b[size].k=k;
      size++;
     }
     else
     {
      int p=a[h].index;
      while(b[p].index!=-1)
      {
        h=p;
        p=b[p].index;
      }
      b[size].b=true;
      b[size].k=k;
      b[size].index=-1;
      b[p].index=size;
      size++;
     }
   } 
}
void hash::search(string k)
{  
   int f=0;
   int h=hash_function(k);
   if(a[h].b==false)
   {
    cout<<"no element"<<endl;
    //break;
   }
   else if(a[h].k!=k && a[h].index==-1)
    {
    cout<<"no element"<<endl;       
    //break;
    }
    else if(a[h].k==k)
    {
     cout<<"element present"<<endl;
     //break;
    } 
    else
    {
      int n=a[h].index;  
      while(b[n].b==true)
      {
       if(b[n].k==k)
       {
       cout<<"element present"<<endl;
       f=1;
       break;
       }
       else
        n=b[n].index;
      }
      if(f==1)
      ;
      else
      cout<<"no element"<<endl;  
     }
}
void hash::del(string k)
{
   int f=0;
   int h=hash_function(k);
   if(a[h].b==false)
   {
    cout<<"no element"<<endl;
    //break;
    }
    else if(a[h].k!=k && a[h].index==-1)
    {
    cout<<"no element"<<endl;       
    //break;
    }
    else if(a[h].k==k)
    {
     a[h].b=false;
     cout<<"element deleted"<<endl;
     //break;
    } 
    else
    {
      int n=a[h].index;  
      while(b[n].b==true)
      {
       if(b[n].k==k)
       {
       b[n].b=false;
       cout<<"element deleted"<<endl;
       f=1;
       break;
       }
       else
        n=b[n].index;
      }
      if(f==1)
      ;
      else
      cout<<"no element"<<endl;  
     }
}
main()
{
 hash s;
 string data;
 s.start();
 	int option;
	while(1)
	{
	cout<<"1.insert"<<endl;
	cout<<"2.remove"<<endl;
	cout<<"3.search"<<endl;
	cout<<"4.exit"<<endl;
	cout<<"enter your option";
	cin>>option;
	switch(option)
	{
		case 1:
			cout<<"enter data to be inserted"<<endl;
			cin>>data;
			s.insert(data);
			cout << "Element is inserted" << endl;
		    break;
		case 2:
		    cout<<"enter the element to be deleted"<<endl;
			cin>>data;
			s.del(data);
			break;
	    case 3:
		    cout<<"enter the element to be searched"<<endl;
			cin>>data;
            s.search(data);
		case 4:
		    exit(1);
		    break;
	    default:
		    cout<<"enter correct option"<<endl; 					
	}
}
}
