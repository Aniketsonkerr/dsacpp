#include <iostream>
#include <string>
#include <cstring>
#include <vector>
using namespace std;
int main()
{
//modern c++ string:
string name = "aniket";
cout<<name<<endl;
cout<<name[0]<<endl;
cout<<name[6]<<endl;//no output hence null value
cout<<sizeof(name)/sizeof(name[0])<<endl;
// c-string char arr[]:
char name2[]="aniket";
cout<<name2<<endl;
cout<<name2[0]<<endl;
cout<<name2[6]<<endl;//no output hence null value
cout<<sizeof(name2)/sizeof(name2[0])<<endl;
//vector<char> string:
vector<char> name3(name.begin(),name.end());
// for (char c:name3) cout<<c;
cout<<name3[3]<<endl;
cout<<name3[6]<<endl;
cout<<name3.size()<<endl;
cout<<sizeof(name3)/sizeof(name3[0])<<endl;
return 0;
};