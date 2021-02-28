#include<bits/stdc++.h>
#define INFINITY 999999
#define BLACK -1
#define WHITE 0
using namespace std;
int minimum(int a[],int n)
{
    int m=a[0],min_idx=0;
    for(int i=1; i<n; i++)
    {
        if(a[i]<m)
        {
            m=a[i];
            min_idx=i;
        }
    }
    return min_idx;
}
using namespace std;
class Graph
{
    int nVertices, nEdges,iter ;
    int **matrix;
    int *path,*dist,*color,*d,*parent;
    int *from,*to,*weight;
    stack<int> st;

public:
    Graph(int n, int e);
    void addEdge(int u, int v,int w);
    int* Dijkstra(int s,int d);
    int bellman_ford(int s, int d);
    void relax(int,int,int);
    int* bellmanford_path(int,int);

    ~Graph();

};
Graph::Graph(int n,int e)
{
    nVertices = n;
    nEdges = e ;
    matrix = new int*[nVertices];
    for(int i=0; i<nVertices; i++)
    {
        matrix[i] = new int[nVertices];
        for(int j=0; j<nVertices; j++)
            matrix[i][j] = 0; //initialize the matrix cells to 0
    }
    dist=new int[n];
    color=new int[n];
    path=new int[n+1];
    d=new int[n];
    parent=new int[nVertices];
    from= new int[e];
    to= new int[e];
    weight= new int[e];
    iter=0;


    //dist=new int[nVertices];

}
void Graph::addEdge(int u, int v,int w)
{
    //node temp=new node(v,w);
    matrix[u][v]=w;
    from[iter]=u;
    to[iter]=v;
    weight[iter]=w;
    iter++;

}
int* Graph::Dijkstra(int s,int des)
{
    int j=nVertices,u1=s;
    int l=2;
    for(int i=0; i<nVertices; i++)
    {
        dist[i]=INFINITY;
        color[i]=WHITE;
        d[i]=INFINITY;

    }

    dist[s]=0;
    d[s]=0;

    //cout<<s<<"->"
    //path[0]=s;

    while(j>=0)
    {

        int u=minimum(d,nVertices);
        //cout<<"Ekhane mara u="<<u<<" "<<u1<<endl;
        color[u]=BLACK;
        j--;

        //path[l]=u;

        if(matrix[u1][u]!=0)
        {
            path[l]=u;
            l++;
            u1=u;
        }

        if(u==des)
        {
            path[0]=dist[des];
            path[1]=l;

            return path;


        }

        for(int k=0; k<nVertices; k++)
        {

            if(matrix[u][k]!=0)
            {


                if ((dist[k]> dist[u]+abs(matrix[u][k]))&&color[k]==WHITE)
                {
                    dist[k]=dist[u]+abs(matrix[u][k]);
                    d[k]=d[u]+abs(matrix[u][k]);




                }
            }
        }
        d[u]=INFINITY;





    }



}
int Graph::bellman_ford(int s,int d)
{
    for(int i=0; i<nVertices; i++)
    {
        dist[i]=INFINITY;
        //parent[i]=INFINITY;

    }
    dist[s]=0;
    // parent[s]=s;
    for(int i=0; i<nVertices-1; i++)
    {
        for (int j=0; j<nEdges; j++)
        {
            relax(from[j],to[j],weight[j]);
        }
    }
    for (int j=0; j<nEdges; j++)
    {
        if (dist[from[j]]!= INFINITY&& dist[from[j]] + weight[j]<dist[to[j]])
            return -1;
    }

    return dist[d];

}
void Graph::relax(int u,int v, int w)
{
    if(dist[v]>dist[u]+w)
    {
        dist[v]=dist[u]+w;
        parent[v]=u;

    }
}
int* Graph::bellmanford_path(int s,int d)
{

    int j=1;
    st.push(d);

    int i=parent[d];
    st.push(i);
    while (parent[i]!=s)
    {
        st.push(parent[i]);
        i=parent[i];
    }
    // st.push(s);
    int *a=new int[st.size()+1];
    a[0]=st.size();
    while(!st.empty())
    {
        a[j]=st.top();
        st.pop();
        j++;
    }
    return a;




}

Graph::~Graph()
{
    // delete[][] matrix;
    delete[] color;
    delete[] dist;
    delete[] path;
    delete matrix;

}

int main()
{
    int n,E,u,v,w,source,destination,*bell,*dij;
    fstream file,file2;

    // String filename="input.txt";
    file.open("input.txt",ios::in);
    file2.open("output.txt",ios::out);
    //char line[10];
    string line;
    file>>line;
    //cout<<line;
    n= stoi(line);
    //cout<<n<<endl;
    dij=new int[n];
    file>>line;
    E=stoi(line);
    //cout<<E<<endl;
    Graph g(n,E);
    while(E--)
    {
        file>>line;
        u=stoi(line);
        file>>line;
        v=stoi(line);
        file>>line;
        w=stoi(line);
        g.addEdge(u,v,w);
        // cout<<u<<" "<<v<<" "<<w<<endl;

    }
    file>>line;
    source=stoi(line);
    file>>line;
    file.close();
    destination=stoi(line);
    file2<<"Bellman Ford Algorithm:"<<endl;
    if(g.bellman_ford(source,destination)==-1)
        file2<<"Negative weight cycle detected."<<endl;
    else
    {
        file2<<g.bellman_ford(source,destination)<<endl;
        bell=g.bellmanford_path(source,destination);
        file2<<source;
        for(int j=1; j<=bell[0]; j++)
            file2<<"->"<<bell[j];


    }



    file2<<endl<<endl<<"Dijkstra Algorithm:"<<endl;
    dij= g.Dijkstra(source,destination);
    file2<<dij[0]<<endl<<source;
    for(int j=2; j<dij[1]; j++)
        file2<<"->"<<dij[j];






}
