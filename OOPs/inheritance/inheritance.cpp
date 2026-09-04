#include <iostream>
#include <string>
using namespace std;

class vehicals{
public:
string brand;
int price;

vehicals(const string & brand,int price): brand(brand), price(price) {};

};

//single inheritence:
class car: public vehicals{
    public:
    string model;

    car(const string& model, const string& brand, int price )
    :vehicals(brand,price)
    {
    this->brand=brand;
    this->model=model;
    this->price=price;
    };

    void display(){
        cout<<brand<<endl;
        cout<<model<<endl;
        cout<<price<<endl;
    };
};

int main()
{
car mycar("civic","honda",20000);
mycar.display();
return 0;
};