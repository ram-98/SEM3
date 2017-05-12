#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

template<class T>
class node{
public:
    T value;
    node *right,*left,*parent;
    node(){
        value=0;
        right=NULL;
        left=NULL;
    }
};

template<class T>
class bst{
public:
    bst(){
        root=NULL;
    }
    node<T>* root;
    node<T>* Insert(T* val){
        if(root==NULL){
            node<T>* temp=new node<T>;
            temp->value=*val;
            temp->left=NULL;
            temp->right=NULL;
            temp->parent=NULL;
            root=temp;
        }
        else{
            node<T>* temp=root;
            node<T>* par=root;
            while(1){
                if(temp->value>*val){
                    if(temp->left==NULL){
                        node<T>* newnode=new node<T>;
                        newnode->value=*val;
                        newnode->left=NULL;
                        newnode->right=NULL;
                        newnode->parent=par;
                        temp->left=newnode;
                        return newnode;
                    }
                    par=temp;
                    temp=temp->left;
                }
                else if(temp->value<*val){
                    if(temp->right==NULL){
                        node<T>* newnode=new node<T>;
                        newnode->value=*val;
                        newnode->left=NULL;
                        newnode->right=NULL;
                        newnode->parent=temp;
                        temp->right=newnode;
                        return newnode;
                    }
                    par=temp;
                    temp=temp->right;
                }
                else{
                    return temp;
                }
            }
        }
    }
    node<T>* search(T* val){
        if(root==NULL){
            return NULL;
        }
        else{
            node<T> *temp=new node<T>;
            temp=root;
            while(1){
                if(temp->value>*val){
                    if(temp->left==NULL){
                        return NULL;
                    }
                    temp=temp->left;
                }
                else if(temp->value<*val){
                    if(temp->right==NULL){
                        return NULL;
                    }
                    temp=temp->right;
                }
                else{
                    return temp;
                }
            }
        }
    }
    void Delete(T* val){
        node<T>* temp;
        temp=search(val);
        if(temp==NULL){
            return;
        }
        else{
            if(temp==root){
                if(root->left==NULL && root->right==NULL){
                    root=NULL;
                    return;
                }
                else if(root->right==NULL){
                    root=root->left;
                    root->parent=NULL;
                    return;
                }
                else if(root->left==NULL){
                    root=root->right;
                    root->parent=NULL;
                    return;
                }
                else{
                    node<T>* temp;
                    temp=root;
                    temp=root->right;
                    while(temp->left!=NULL){
                        temp=temp->left;
                    }
                    T valtemp=temp->value;
                    Delete(&valtemp);
                    root->value=valtemp;
                    return;
                }
            }
            if(temp->right==NULL && temp->left==NULL){
                if(temp->parent->right==temp){
                    temp->parent->right=NULL;
                    free(temp);
                    return;
                }
                temp->parent->left=NULL;
                free(temp);
                return;
            }
            if(temp->right==NULL){
                if(temp->parent->right==temp){
                    temp->parent->right=temp->left;
                    temp->left->parent=temp->parent;
                    free(temp);
                    return;
                }
                if(temp->parent->left==temp){
                    temp->parent->left=temp->left;
                    temp->left->parent=temp->parent;
                    free(temp);
                    return;
                }
            }
            if(temp->left==NULL){
                if(temp->parent->right==temp){
                    temp->parent->right=temp->right;
                    temp->right->parent=temp->parent;
                    free(temp);
                    return;
                }
                if(temp->parent->left==temp){
                    temp->parent->left=temp->right;
                    temp->right->parent=temp->parent;
                    free(temp);
                    return;
                }
            }
            else{
                node<T>* temp2;
                temp2=temp->right;
                while(temp2->left!=NULL){
                    temp2=temp2->left;
                }
                T valtemp;
                valtemp=temp2->value;
                Delete(&valtemp);
                temp->value=valtemp;
                return;
            }
        }
    }
 
 
};


int main(){
    bst<int> tree;
    while(1){
        printf("Enter one of the following option\n1.insert\n2.search\n3.delete\n4.exit\n");
        int option;
        scanf("%d",&option);
        if(option==1){
            printf("Enter the value to be inserted\n");
            int input;
            scanf("%d",&input);
            tree.Insert(&input);
        }
        else if(option==2){
            printf("Enter the value to be searched\n");
            int input;
            scanf("%d",&input);
            if(tree.search(&input)==NULL){
                printf("No such element is present\n");
            }
            else{
                printf("element is present\n");
            }
        }
        else if(option==3){
            printf("Enter the value to be deleted\n");
            int input;
            scanf("%d",&input);
            tree.Delete(&input);
        }
        
        else if(option==4){
            break;
        }
        else{
            printf("invalid entry\n");
        }
    }
}
