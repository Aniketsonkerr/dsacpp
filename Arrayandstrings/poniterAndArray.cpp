#include <iostream>
using namespace std;
 int main()
 {
//pointer to an integer array:
 int * p;
 int arr[5]={1};
 p = arr;
 cout<<p<<" "<<arr<<endl;
 cout<<*p<<endl;
 cout<<arr[0]<<endl;
//interger pointer array:
 int * arr2[5];
 arr2[0]=p;
 cout<<"arr2 returns: "<<arr2<<endl;
 cout<<"derefencing arr2 returns: "<<*arr2<<endl;
 cout<<"arr2[i] returns: "<<arr2[0]<<endl;
 };