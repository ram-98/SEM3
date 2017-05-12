#include <iostream>
#include<malloc.h>
#include<cstdlib>
#include<climits>

using namespace std;

struct bheap
{
	int degree,key;
	bheap * parent;
	bheap *leftchild;
	bheap* rsibling;
};

bheap* H=NULL;
bheap* H1=NULL;
bheap* H2=NULL;


bheap * Make_BinomialHeap(){
		bheap* Htemp = new bheap();
		return Htemp;
}

bheap * MinDegree(bheap * a, bheap* b){
		if(a->degree < b->degree)
			return a;
		else
			return b;
}

bheap * BinomialHeapMerge(bheap * H1, bheap *H2){
				bheap * a = H1;
				bheap * b = H2;
				bheap * c;
				H1 = MinDegree(a, b);

				if (H1 == b)
				   	   b = a;
				a = H1;
				while (b != NULL){
			    	if (a->rsibling ==NULL){
			          	   a->rsibling = b;
			               break;
			           }
			          else if (a->rsibling->degree< b->degree)
			                  	   a = a->rsibling;
			           else {
	                  	    c = b->rsibling;
	                       b->rsibling = a->rsibling;
	                       a->rsibling = b;
	                       a = a->rsibling;
	                       b = c;
			                   }
                   }
                return a;
               }

bheap * BinomialHeapUnion(bheap *H1,bheap * H2){
		H = Make_BinomialHeap();
		H = BinomialHeapMerge( H1, H2);
		bheap * prev_x = NULL;
		bheap * x= H;
		bheap * next_x = x->rsibling;
		while (next_x != NULL){
		       if ((x->degree != next_x->degree) || (next_x->rsibling != NULL && next_x->rsibling->degree == x->degree)){
		             prev_x = x;
		             x = next_x;
		             }
		            else if (x->key <= next_x->key){
		                 	   x->rsibling = next_x->rsibling;
		                       next_x->parent= x;
								next_x->rsibling = x->leftchild;
								x->leftchild = next_x;
								x->degree = x->degree + 1;	
		                  }
		                 else {
		                 	if (prev_x == NULL){
		                          H = next_x;
		                     }
		                  else {
		                      prev_x->rsibling = next_x;
		                  }
		                  x->parent= next_x;
							x->rsibling = next_x->leftchild;
							next_x->leftchild = x;
							next_x->degree = next_x->degree + 1;	
		                      x = next_x;
		              }
		         next_x = x->rsibling;
		     }
		return H ;
}

void  Binomial_HeapInsert(int x){
			H1 = Make_BinomialHeap();
			H1->parent = H1->leftchild =H1->rsibling =NULL;
			H1->degree = 0;
			H1->key=x;
			if (H==NULL){
				H=H1;
				return;
			}
			H=BinomialHeapUnion(H,H1);
			return;
		}
bheap* BinomialHeapMinimum(){
			bheap *x = H;
			bheap* y=NULL;
			int min = INT_MAX;
			while (x != NULL){
			       if (x->key < min){
			             min = x->key;
			             y=x;
			             }
			         x = x->rsibling;
			     }
			return y;
		}
void Display() {    //display 
  for (bheap *temp = H; temp != NULL; temp = temp->rsibling) {
    		cout<< "\nBinomial Tree degree :" <<temp->degree<< endl;
    		cout<<temp->key << "\t\t-----rootkey "<< endl;
    		for (bheap *temp2 = temp; temp2 != NULL; temp2 = temp2->leftchild) {
    				
    				for ( bheap *temp3= temp2->leftchild;temp3!=NULL  ;temp3=temp3->rsibling )
    				{	
    						cout<< temp3->key << "\t";
    				}
    				cout << endl;
      			}
  }
}
void DeleteMin(){
		    bheap *h,*del = BinomialHeapMinimum();  
		    if (del->key == H->key)
		    	 h = H->leftchild;
		    else
		    	 h = del->leftchild;    //h = min node ->leftchild
		    bheap *t = h;
		    bheap *temp;
		    if (t != NULL) {    
		      t = t->rsibling;
		      h->rsibling = NULL;
		      while (t != NULL) {
		        temp = t->rsibling;
		        t->rsibling = h;
		        h = t;
		        t = temp;
		      }
		    }
		    //deleting the min-node
		    if (del->key == H->key) {
		      temp = H;
		      H = H->rsibling;
		      free(temp);
		    }
		    else {
		      temp = del;
		      bheap * p=H;
		      while(p->rsibling-> key!=del->key){
		      			p=p->rsibling;
		      }	
		      p->rsibling=del->rsibling;
		      free(temp);
		    }
		    if (H==NULL && h ==NULL)
		    {
		    	return;
		    }
		    else if(H==NULL && h !=NULL){
		    	H=h;
		    	return;
		    }
		    else if(H!=NULL && h ==NULL)
		    {
		    	return;
		    }
		    H=BinomialHeapUnion(h, H);
		  }




int main()
{
	int option,value;
	cout<< "Binomial heap is running\n Enter an option\n" << endl;
	while(1){ 	
	        	cout<<"\n 1:Insert  2:Find Minimum  3:display 4:Exit 5: Delete minimum\n";
	        	cin>>option;
			switch(option){
			       case 1:
			       		cout<<"Enter the integer you want to add \n";
					  	cin>>value;
			       		Binomial_HeapInsert(value);
			       		break;
			       case 2:
			       		if (H != NULL) {
					         cout<< "THe mininum in BinomialHeap is :" <<BinomialHeapMinimum()->key<< endl;
					        }
					    else
        	 				cout<< "BinomialHeap is empty\n" << endl;
			       		break;
			       case 3:
			       		if (H != NULL) {
			       			Display();
					        }
					    else
        	 				cout<< "BinomialHeap is empty\n" << endl;
			       		break;
			       case 4:
			       		exit(0);
			       		break;
			       	case 5:
			       		if (H != NULL) {
					         cout<< "THe mininum in BinomialHeap is :" <<BinomialHeapMinimum()->key<<" deleted"<< endl;
					         DeleteMin();
					        }
					    else
        	 				cout<< "BinomialHeap is empty\n" << endl;

			       		break;

			       }
	}
	return 0;
}