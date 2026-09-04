#include <iostream>
#include <cstring>

using namespace std;

class employee {
    private:
    int salary;
    public:
    char name[50];
    
    employee(const char * name){
      strcpy(this->name,name);          
    };
    void setSalary(int salary){
       this->salary=salary;
    };
    void friend getSalary(employee emp);
};

void getSalary(employee emp){
    cout<<emp.salary;
};

int main(){
    employee employ1("aniket");
    employ1.setSalary(100000000);
    cout<<employ1.name<<endl;
    getSalary(employ1);
}