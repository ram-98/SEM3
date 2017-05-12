*******EVERYTHING IS TAKEN FROM CORNEN AND IMPLEMENTED.THE ALGORITHMS ARE TAKEN SAME AS THEM AND IMPLEMENTED****

#include<iostream>
#include <stdlib.h>

using namespace std;

struct BstNode {        //Node containing data,left adn right child pointers
    int data; 
    BstNode* left;
    BstNode* right;
};
BstNode* temp = NULL;       
int  deletestatus;      //Deletestatus to know whether element is deleted or not
BstNode* root = NULL;  // Creating an empty tree and root is BST pointer

BstNode* GetNewNode(int data) {         //Getting a new node with data inserted
    BstNode* newNode = new BstNode();
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

void Insert(int data) {                     //Insert function
    BstNode *z=GetNewNode(data);            // z is the new node to be inserted in tree
    BstNode * y=NULL;
    BstNode* x=root;
    while(x!=NULL){                   //Searching for correct positon "y" to insert new node "z"
        y=x;
        if (z->data<x->data)
        {
            x=x->left;
        }
        else   
            x=x->right;
    }
    if (y==NULL)                     //If empty tree make z as root
    {
        root=z;
    }
    else if(z->data <y->data){          //Put z to left of y
        y->left=z;
    }
    else
        y->right=z;                      //Put z to right of y

    return ;
}
bool Search(BstNode* root,int data) {       //Searching function
    if(root == NULL) {
        return false;
    }
    else if(root->data == data) {                 //  If found return true 
        return true;
    }
    else if(data <= root->data) {
        return Search(root->left,data);         //Recurrsively go through left and right untill correct value is found
    }
    else {
        return Search(root->right,data);
    }
}
void display_inorder(BstNode* root){            //Inorder printing
    if(root==NULL)
        return;
    display_inorder(root->left);
    cout<<root->data<<endl;
    display_inorder(root->right);

}
BstNode* FindMin_RightTree(BstNode* root)       //Finding successror  
{   
    while(root->left != NULL) 
        root = root->left;
    return root;
}
BstNode* Delete(BstNode* root, int data) {      

    if(root == NULL)
         return root; 
    else if(data < root->data) 
        root->left = Delete(root->left,data);
    else if (data > root->data)
         root->right = Delete(root->right,data);               //  ready to be deleted    
    
    else {
                                                                // Case 1:  No child
        if(root->left == NULL && root->right == NULL) { 
            delete root;
            root = NULL;
            deletestatus=deletestatus+1;
        }
                                                                //Case 2: One child 
        else if(root->left == NULL) {
            BstNode* temp = root;
            root = root->right;
            delete temp;
            deletestatus=deletestatus+1;
        }
        else if(root->right == NULL) {
            BstNode* temp = root;
            root = root->left;
            delete temp;
            deletestatus=deletestatus+1;
        }
                                                                // case 3: 2 children
        else { 
            BstNode* temp = FindMin_RightTree(root->right);
            root->data = temp->data;
            root->right = Delete(root->right,temp->data);
        }
        
    }
    return root;
}


int main() {
    int number;
    cout<<"Binarysearchtree is being implemented using linkedlists.Please select following options"<<endl;
    int option;
    do{
    cout<<"Press 1 for Insert a node\n 2 for Delete a node   \n 3 for display in Inorder \n 4 for Searching a value in Bst\n 5 for exit"<<endl;
    cin>>option;
    switch(option){
        case 1:
                cout<<"Enter an integer u want to Insert"<<endl;
                cin>>number;
                Insert(number);
                break;
        case 2:
                if(root==NULL){
                    cout<<"Bst is empty "<<endl;
                }
                else{
                cout<<"Enter an integer u want to Delete"<<endl;
                cin>>number;
                deletestatus=0;
                BstNode* temp2= Delete(root,number);
                if (deletestatus==0)
                    cout<<"Value entered is not found .Deletion unsuccessful"<<endl;
                else if(deletestatus==1)
                    cout<<"Deletion sucessfull"<<endl;
            }
                break;
        case 3:
                cout<< "the root value is "<<root->data<< endl;
                cout<<"Inorder tranversal is"<<endl;    
                display_inorder(root);
                break;
        case 4:
                cout<<"Enter number be searched\n";
                cin>>number;
                if(Search(root, number) == true) 
                    cout<<number<<" is Found\n";
                else
                     cout<<number<<" Not Found\n";
                 break;
        case 5:
                cout<<"Exiting the program"<<endl;
                exit(0);
        default:
                cout<<"Invalid option"<<endl;
    }
    }while(1);

    return 0;
}