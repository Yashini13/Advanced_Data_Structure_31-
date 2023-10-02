#include <iostream>
#include <bits/stdc++.h>
using namespace std;
struct Node{
int data;
struct Node *prev;
struct Node *next;
};
void push(struct Node **head_ref, int new_data)
{
  struct Node *newNode= new Node();
  newNode->data=new_data;
  newNode->next=(*head_ref);
  newNode->prev=NULL;
  if((*head_ref)!=NULL)
    (*head_ref)->prev=newNode;
  (*head_ref)=newNode;  
}
void insertAtStart(struct Node **head_ref, int data)
{
   struct Node *newNode= new Node();
  newNode->data=data;
  newNode->next=(*head_ref);
  newNode->prev=NULL;
  if((*head_ref)!=NULL)
    (*head_ref)->prev=newNode;
  (*head_ref)=newNode;   
}
void insertAtLast(struct Node **head, int data)
{
    struct Node *newNode = new Node();
    newNode->data=data;
    newNode->next=NULL;
    if(*head==NULL)
     { *head=newNode;
       newNode->prev=NULL;
     }
    struct Node *temp=(*head);
      while(temp->next!=NULL)
       temp=temp->next;
    temp->next=newNode;
    newNode->prev=temp; 
}
int calcSize(struct Node *node)
{
    int result=0;
        while(node!=NULL)
        { 
        result++;    
        node=node->next;
        } 
    return result; 
}
void insertAtPosition(struct Node **head, int data,int pos){
    int size= calcSize( *head );
    if(pos<0||pos>size)
     return;
    if(pos==0)
      insertAtStart(head,data);
    if(pos==size)
      insertAtLast(head, data);
    else{
        struct Node *temp= *head;
        struct Node *newNode= new Node();
        newNode->data=data;
        newNode->next=NULL;
        while(--pos)
        {
            temp=temp->next;
        }
        struct Node *temp2 = temp->next;
        newNode->data=data;
        newNode->next=temp->next;
        newNode->prev=temp;
        temp->next=newNode;
        temp2->prev=newNode;
    }   
}
void deleteNode(struct Node **head, struct Node *del)
{
    //Default case
    if(*head==NULL || (del)==NULL)
    return;
    if(*head == del)
     *head= del->next;
    //delete at tail
     if(del->next != NULL) 
     del->next->prev=del->prev;
     ///delete at head
     if(del->prev!=NULL)
     del->prev->next=del->next;
    free(del);      
}
void display(struct Node *node){
    struct Node *end;
  cout<<"List in Forward direction: ";
   while (node != NULL)
    {
      printf (" %d ", node->data);
      end = node;
      node = node->next;
}
}
int main(){
   struct Node *head=NULL;
   push(&head, 4); 
   push(&head, 45);
   push(&head, 34); 
   push(&head, 58);
   push(&head, 12);
   insertAtStart(&head, 55); 
   insertAtPosition(&head, 81,3);
   insertAtLast(&head ,67);
   display(head);
   cout<<"\n deleting nodes \n";
    deleteNode(&head, head); /*delete first node*/
    deleteNode(&head, head->next); /*delete middle node*/
    deleteNode(&head, head->next); /*delete last node*/
    display(head);
   cout<<"size of the linked list is "<<calcSize(head);
}