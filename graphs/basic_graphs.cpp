#include <iostream>
#include <list>
using namespace std;

class Graph{
int v;
list<int> * l;
public:
Graph(int v){
    this->v=v;
    l= new list<int> [v];
}

void insertVertex(int v, int u){
    l[v].push_back(u);
    l[u].push_back(v);
};

};

int main(){
    Graph graph(6);
    return 0;
}