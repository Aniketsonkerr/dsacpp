#include <iostream>
using namespace std;
class node{
    public:
    int data;
    node * next;
           };
class linkedList{
    public:
    node * head;

    linkedList(){
        head=NULL;
    }
    

    void insertNodeInIncreasingOrder(int data){
        node * newNode = new node;
        newNode->data=data;
        if(head==NULL || head->data>= data){
            newNode->next=head;
            head = newNode;
        }else
        {
            node * temp = head;
            while(temp->next != NULL && temp->next->data<data){
                temp=temp->next;
            };
            newNode->next=temp->next;
            temp->next=newNode;
        }
        
    };
    
    void printList(){
        node* temp=head;
        while(temp!=NULL){
            cout<<temp->data<<endl;
            temp=temp->next;
        };
    }
    
};
          

int main(){
    int n;
    cout<<"enter number for linkedList to be  created: "<<endl;
    cin>>n;
    linkedList list;
    for(int i=0;i<n;i++){
        int data;
        cout<<"enter data: "<<endl;
        cin>>data;
        list.insertNodeInIncreasingOrder(data);
    };
    
    list.printList();

    return 0;
}