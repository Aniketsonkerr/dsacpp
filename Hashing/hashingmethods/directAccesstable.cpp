#include <iostream>
using namespace std;

int table[10];

void insertDataInTable(int data) {
    table[data] = data;
}

int getdata(int data) {
    return table[data];
}

int deleteData(int data) {
    int temp = table[data];
    table[data] = -1;   // mark as deleted
    return temp;
}

int main() {
    insertDataInTable(0);
    insertDataInTable(2);
    insertDataInTable(3);

    cout << "Value at index 2: " << getdata(2) << endl;
    cout << "Deleted value: " << deleteData(2) << endl;
    cout << "Value at index 2 after deletion: " << getdata(2) << endl;

    return 0;
}
