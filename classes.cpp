#include <iostream>
#include <string>
using namespace std;
class student{
    int rollNo;   
    public:
    string name;
    void createStudent(int r, string n);
    void printStudents();
};
void student::createStudent(int r,string n){
  rollNo=r;
  name=n;
};
void student::printStudents(){
cout<<rollNo<<" "<<name;
};
int main(){
    student student1;
    student1.createStudent(1, "aniket");
    student1.printStudents();
    return 0;
}