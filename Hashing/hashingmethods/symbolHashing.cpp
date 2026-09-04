#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct symbol{
    string name;
    string type;
    string vaule;
    bool occupied;
};

class HashTable {
    
    int table_size;
    vector<symbol> table;
    
    int hashFunction(const string& key ){
        int sum=0;
        for(char c : key) sum+=c;
        return sum%table_size;
    };

    public:
    
    HashTable(int n){
     table_size=n;
     table.resize(table_size);
     for(int i=0; i<=n;i++) table[i].occupied=false;
    };
    
    

    void insertKey(const string& name,const string& type,const string& value){
        int hashkey = hashFunction(name);
        table[hashkey]={name,type,value,true};
    }
};
