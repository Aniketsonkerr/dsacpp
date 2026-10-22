#include <iostream>
#include <list>
#include <vector>
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

bool cycleDecterHelper(int src,int p,vector<bool>&visited){
cout<<src<<" ";
visited[src]=true;
list<int> neibhor = l[src];
for(int vertex:neibhor){
   if(!visited[vertex]){
    cycleDecterHelper(vertex,src,visited);
   }else if(vertex!=p){
    return true;
   };
return false;
}

};

bool cycleDetectorDfs(){
    vector<bool>visited(v,false);
    for(int i=0;i<v;i++){
        if(!visited[i]){
            if(cycleDecterHelper(i,-0,visited)){
                return true;
            };
        };
    };
    
    return false;
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
    return 0;
}