#include<bits/stdc++.h>
#define INFINITY 99999999
#define NIL -1
#define WHITE 0
#define BLACK 1
using namespace std;
typedef pair<int,int> g_pair;
bool sortbyth(const tuple<int, int, int>& a, const tuple<int, int, int>& b)
{
    return (get<2>(a) < get<2>(b));
}
class Disjoint
{
    int *p;
    int *Rank;
    int i;
public:
    Disjoint();
    void Make_set(int x);
    int Find_set(int x);
    void Union(int x,int y);

};
Disjoint::Disjoint()
{
        p=new int[100];
        Rank=new int[100];
        for(int j=0;j<100;j++)
        {
            p[j]=-1;
            Rank[j]=-1;
        }
        //i=0;

}
void Disjoint::Make_set(int x)
 {
        p[x]=x;
        Rank[x]=0;
        //i++;

}
int Disjoint::Find_set(int x)
{
        if(p[x]==-1)
        {
            cout<<"The element is not found"<<endl;
            return -1;
        }
        if(p[x]==x)
        {
            return x;
        }
        else
        {
            int parent=Find_set(p[x]);
            p[x]=parent;
            return parent;
        }

}
void Disjoint::Union(int x,int y)
 {
        int rx=Find_set(x);
        int ry=Find_set(y);
        if(rx==-1||ry==-1)
            return;
        if(rx==ry)
            return;
        if(Rank[rx]>Rank[ry])
        {
            p[ry]=rx;
        }
        else if(Rank[rx]<Rank[ry])
        {
             p[rx]=ry;


        }
        else
        {
            p[ry]=rx;
            Rank[rx]++;
        }


}


class Graph
{
     int V,E;
     list< pair<int, int> > *adj;
     vector<tuple<int,int,int>> edges;
    fstream file2;
    int *parent,*key,*color;
public:
    Graph();
    void setnVertices(int);
    void addEdge(int u, int v, int w);
    void prim();
    void printTree();
    void kruskal();
    ~Graph();


};

Graph::Graph()
{
    V=0;

}
void Graph::setnVertices(int V)
{
    this->V = V;
    adj = new list<g_pair>[V];
    key = new int[V];
    parent= new int[V];
    color= new int[V];
    file2.open("output.txt",ios::out);


}
void Graph::addEdge(int u, int v, int w)
{
    if(u==v || v>=V||u>=V)
        return;
    adj[u].push_back(make_pair(v, w));
    adj[v].push_back(make_pair(u,w));
    edges.push_back(make_tuple(u,v,w));

}
void Graph::prim()
{
   file2<<" Prim's Algorithm: "<<endl;
    srand(time(NULL));
    for(int i=0; i<V; i++)
    {
        key[i]=INFINITY;
        parent[i]=NIL;
        color[i]=WHITE;

    }
    int root=rand()%V;
    parent[root]=NIL;
     file2<<"The Root Node is "<<root<<endl;
    priority_queue< g_pair, vector <g_pair>, greater<g_pair> > pq;
    pq.push(make_pair(0,root));
    key[root] = 0;
    color[root]=BLACK;
    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();

        list< pair<int,int> >::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
        {
            int v = (*i).first;
            int weight = (*i).second;

            if (key[v] >  weight&&color[v]==WHITE)
            {
                parent[v]=u;
                key[v] = weight;
                pq.push(make_pair(key[v],v));
            }
        }
        color[u]=BLACK;
    }


}
void Graph::printTree()
{
    //f.open("output.txt",ios::out);
    int sum=0;
   for(int i=0;i<V;i++)
  {
      if(parent[i]==-1)
        continue;
        sum=sum+key[i];
       file2<<parent[i]<<"  "<<i<<endl;


  }
  file2<<"The weight of tree with Prim's Algorithm is "<<sum<<endl;


}
void Graph::kruskal()
{
    file2<<" Kruskals Algorithm: "<<endl;

    int sum=0;
     Disjoint mst;
      for(int i=0;i<V;i++)
        mst.Make_set(i);
      sort(edges.begin(),edges.end(),sortbyth);
      for(int i=0;i<edges.size();i++)
      {
        int u=get<0>(edges[i]);
        int v=get<1>(edges[i]);
        int w=get<2>(edges[i]);
        if(mst.Find_set(u)!=mst.Find_set(v))
        {
            file2<<u<<"  "<<v<<endl;
            sum+=w;
            mst.Union(u,v);

        }
      }
      file2<<"The weight of tree with Kruskal's Algorithm is "<<sum<<endl<<endl;




}
Graph::~Graph()
{

    delete[] parent;
    delete[] key;
    file2.close();

}

int main()
{
    int n, m;
    fstream file;
     Graph g;

    file.open("input0.txt",ios::in);

    //char line[10];
    string line;
    file>>line;
    n= stoi(line);
    g.setnVertices(n);
    file>>line;
    m=stoi(line);

    while(m--)
    {
        file>>line;
        int u=stoi(line);
        file>>line;
        int v=stoi(line);
        file>>line;
        int w=stoi(line);
        g.addEdge(u,v,w);

    }
     g.kruskal();
     g.prim();
     g.printTree();
    file.close();

}
