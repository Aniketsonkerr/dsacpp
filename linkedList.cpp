#include <iostream>
using namespace std;
class node{
    public:
    int data;
    node * next;
    node(int data){
        this->data=data;
        this->next=NULL;
    };
};

class linkedlist{
    private:
    node * head;
    public:
    linkedlist(){
        head=NULL;
    };
    void createNode(){
        int data;
        cout<<"enter data: "<<endl;
        cin>>data;
        node* newNode = new node(data);
        if(head==NULL){
            head = newNode;
        }else{
            node * current = head;
            while(current->next!=NULL){
                current=current->next;
            };
            current->next=newNode;
        };
    };
    
    void printList(){
        if(head!=NULL){
            node* current = head;
            while(current!=NULL){
                cout<<current->data<<" ";
                current=current->next;
            };
        }else{
            cout<<"linked list is empty"<<endl;
        };
    };

    void insertAtSpecificPos(int data,int pos){
        node* newNode = new node(data);
            if(pos==0)
            {
            node* temp = head;
            head=newNode;
            newNode->next=temp;
            };
            int count=0;
            node * temp = head;
            while(temp!=NULL && count<pos-1)
            {
            temp=temp->next;
            count++;
            };
            if(temp==NULL)
            {
            cout<<"position is out of bounds"<<endl;
            delete newNode;
            }else
            {
            newNode->next=temp->next;
            temp->next=newNode;
            };
                                               };
    
    node* deleteFromBeginning()
    {
    if(head==NULL)
    {
        return 0;
    }else
    {
        node*temp=head;
        head=head->next;
        return temp;
    }
    };

    node * deleteFromEnd()
    {
       if(head==NULL)
       {
        cout<<"list is empty"<<endl;
        return NULL;
       };
       if(head->next=NULL){
        node* temp = head;
        head = NULL;
        return temp;
       }
       node* temp = head;
       while(temp->next->next!=NULL)
       {    
            node* current = temp->next;
            temp->next=NULL;
            return current;        
       }
    };
    
    node* deleteNodeByPos(int pos)
    {
     if(head==NULL)
     {
        cout<<"list is empty"<<endl;
        return NULL;
     }
     if(head!=NULL && pos==1)
     {
        node* temp = head;
        head=NULL;
        return temp; 
     };
      
     node* current = head;
     int count=0;
     while(current->next->next!=NULL && count<pos-1){
        count++;
        current=current->next;
     }
     if(current!=NULL){
       node* temp = current->next;
       current->next=current->next->next; 
     }
    };            
                                              
};




int main(){
    int x;
    cout<<"enter number of nodes: "<<endl;
    cin>>x;
    linkedlist list;
    for(int i=0;i<x;i++){
        list.createNode();
    };
    list.printList();
    return 0;
}