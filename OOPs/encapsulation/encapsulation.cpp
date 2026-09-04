#include <iostream>
#include <cstring>
using namespace std;

class person{
    //private members
    private:
    char gender[50];
    //public members
    public:
    char name[50];
    int age;
    
    person(const char * name,int age){
        strcpy(this->name,name);
        this->age = age;
    };
    //making a getter for private member only way to access the private member
    void setGender(const char * gender ){
        strcpy(this->gender,gender);
    };

    void getGender(){
        cout<<this->gender;
    }

};

int main()
{
    person myperson("aniket",24);
    cout<<myperson.name<<endl;
    cout<<myperson.age<<endl;
    myperson.setGender("male");
    //myperson.gender="male"; //shows error
    myperson.getGender();
    return 0;
}