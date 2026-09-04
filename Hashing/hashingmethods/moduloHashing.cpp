#include <iostream>
#include <vector>
using namespace std;
int table[26];

int hashFunction(int data)
{
    int key;
    key = data%26;
    return key;     
}

void insertDatainHashTable(int data){
    int hashkey = hashFunction(data);
    table[hashkey]=data;
}

int deleteDatainHashTable(int data){
    int hashkey = hashFunction(data);
    int temp = table[hashkey];
    table[hashkey]=-1;
    return temp;
}

int main(){
    return 0;
}