#include <iostream>
#include <list>
#include <queue>
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

void dfsHelperFunc(int u,vector<bool>&visited){
cout<<u<<" ";
visited[u]=true;
for(int vertex:l[u]){
    if(!visited[vertex]){
        dfsHelperFunc(vertex,visited);
    };
};
};

void dfs(){
vector<bool> visited(v,false);
int u = 1;
dfsHelperFunc(u,visited);
cout<<endl;
};


void bsf(){
queue<int> q;
vector<bool> visted (v,false);
q.push(1);
visted[1]=true;
while(q.size()>0){
    int u = q.front();
    q.pop();
    cout<<u<<" ";
    for(int vertex: l[u]){
        if(!visted[vertex]){
            visted[vertex]=true;
            q.push(vertex);
        };
    };
}
cout<<endl;
}

};

int main(){
    Graph graph(7);
    graph.insertVertex(1,2);
    graph.insertVertex(1,3);
    graph.insertVertex(2,4);
    graph.insertVertex(2,3);
    graph.insertVertex(4,5);
    graph.insertVertex(4,6);
    graph.bsf();
    graph.dfs();
    return 0;
}