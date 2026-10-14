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

void printGraph(){
    for(int i=0;i<v;i++){
        cout<<i<<":";
        for(int edges: l[i]){
        cout<<edges<<" ";
      }
      cout<<endl;
      ;
    }
};

};

int main(){
    Graph graph(7);
    graph.insertVertex(1,2);
    graph.insertVertex(1,3);
    graph.insertVertex(2,4);
    graph.insertVertex(2,3);
    graph.insertVertex(4,5);
    graph.insertVertex(4,6);
    graph.printGraph();
    return 0;
}