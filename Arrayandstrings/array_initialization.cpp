//lets start with array initializations 
#include <iostream>
using namespace std;

int main()
{
    //1st way to initialize array:
    int arr1[5];
    //2nd way to initialize array:
    int arr2[]={1,2,3,4,5};
    //3rd way to initialize array:
    int arr3[4]={1,3};
    //now you are wondering at indices these 1 and 3 are placed in array, let's find it our selves:
    int size = sizeof(arr3)/sizeof(arr3[0]);
    for(int i=0;i<size;i++){
        cout<<i<<" "<<arr3[i]<<endl;
    }
    //output:
    // 0 1
    // 1 3
    // 2 0
    // 3 0
    return 0;
}