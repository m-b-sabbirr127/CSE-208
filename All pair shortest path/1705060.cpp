#include<bits/stdc++.h>
#define INFINITY 99999999
#define NIL -1
using namespace std;
typedef pair<int, double> g_Pair;
typedef pair<double,int> nPair;

class Edge
{
    int from,to;
    double weight;
public:
    Edge();
    Edge(int,int,double);
    void setter(int,int,double);
    double get_weight();
    int get_source();
    int get_dest();
};
Edge::Edge()
{
    from=0;
    to=0;
    weight=0;
}

void Edge::setter(int u,int v,double w)
{
    from=u;
    to=v;
    weight=w;
}
double Edge::get_weight()
{
    return weight;
}
int Edge::get_source()
{
    return from;
}
int Edge::get_dest()
{
    return to;
}

class Graph
{
    int V,E;
    bool directed;
    list< pair<int, double> > *adj;
    vector<Edge*> edges;
    //Edge *edges;

    double **dist,*d;
    int **parent,*p;

public:
    Graph(bool);
    void setnVertices(int);
    bool addEdge(int u, int v, double w);
    void printGraph();
    void removeEdge(int,int);
    Edge* searchEdge(int,int);
    void reweightEdge(int,int,double);
    double getshortestPath(int,int);
    void printShortestpath(int,int);
    void printDistMatrix();
    void printParentMatrix();
    void cleanSpinfo();
    bool isEdge(int,int);
    double getWeight(int, int);
    void floydWarshall();
    double* bellmanFord(int);
    void relax(int,int,double);
    void dijkstra(int);
    void johnson();



    ~Graph();

};
Graph::Graph(bool dir)
{
    V=0;
    directed=dir;
}


void Graph::setnVertices(int V)
{
    this->V = V;
    adj = new list<g_Pair>[V];
    //edges=new vector<Edge>[E];
    dist = new double*[V];
    parent= new int*[V];
    d=new double[V];
    p=new int[V];
    for(int ii=0; ii<V; ii++)
    {
        dist[ii] = new double[V];

    }
    for(int ii=0; ii<V; ii++)
    {
        parent[ii] = new int[V];
    }

}

bool Graph::addEdge(int u, int v, double w)
{
    if(u==v || v>=V||u>=V)
        return false;
    adj[u].push_back(make_pair(v, w));
    Edge *e=new Edge;
    e->setter(u,v,w);
    edges.push_back(e);
    return true;
}

void Graph::printGraph()
{
    list<pair<int,double>>::iterator iter;
    for(int u=0; u<V; u++)
    {
        cout<<u+1<<":";

        for(iter=adj[u].begin(); iter!=adj[u].end(); ++iter)
        {
            cout<<"-->"<<(*iter).first+1<<"("<<(*iter).second<<")";
        }
        cout<<endl;
    }

}
Edge* Graph::searchEdge(int u, int v)

{
    //vector<Edge>::iterator ii;

    for( auto ii=edges.begin(); ii!=edges.end(); ++ii)
    {
        if((*ii)->get_source()==u&&(*ii)->get_dest()==v)
        {

            return (*ii);
        }


    }
    return NULL;


}
void Graph::removeEdge(int u,int v)
{
    list<pair<int,double>>::iterator iter;
    if(searchEdge(u,v)!=NULL)
    {
        for(iter=adj[u].begin(); iter!=adj[u].end(); ++iter)
        {
         if(v==(*iter).first)
            {
                //cout<<" Mara khai"<<endl;
                adj[u].erase(iter);
            }


        }

    }
    for( auto ii=edges.begin(); ii!=edges.end(); ++ii)
    {
        int u1=(*ii)->get_source();
        int v1=(*ii)->get_dest();
        if(u==u1&&v==v1)
            edges.erase(ii);

    }

}
void Graph::printShortestpath(int u,int v)
{
    int papa=parent[u][v];
    if(papa==NIL)
    {
        cout<<v+1;
        return;
    }

    printShortestpath(u,papa);
    cout<<"-->"<<v+1<<"("<<getWeight(parent[u][v],v)<<")";


}
void Graph::reweightEdge(int u,int v,double w)
{
    list<pair<int,double>>::iterator iter;
    if(searchEdge(u,v)!=NULL)
    {
        for(iter=adj[u].begin(); iter!=adj[u].end(); ++iter)
        {
            if(v==(*iter).first)
                (*iter).second=w;

        }

    }
    Edge *e=searchEdge(u,v);
    e->setter(u,v,w);



}
bool Graph::isEdge(int u,int v)
{
    if(searchEdge(u,v)!=NULL)
        return true;
    return false;

}
double Graph::getWeight(int u, int v)
{
    list<pair<int,double>>::iterator iter;
    for(iter=adj[u].begin(); iter!=adj[u].end(); ++iter)
    {
        if(v==(*iter).first)
            return (*iter).second;

    }
    return INFINITY;

}
Graph::~Graph()
{
    for(int i=0; i<V; i++)
    {
        delete[] dist[i];
        delete[] parent[i];

    }
    delete[] d;
    delete[] p;
    delete[] parent;
    delete[] dist;

}
void Graph::floydWarshall()
{

    for( auto ii=edges.begin(); ii!=edges.end(); ++ii)
    {
        int u=(*ii)->get_source();
        int v=(*ii)->get_dest();
        double w =(*ii)->get_weight();
        dist[u][v]=w;
        parent[u][v]=u;

    }
    for(int i=0; i<V; i++)
        dist[i][i]=0;

    for(int k=0; k<V; k++)
    {
        for(int i=0; i<V; i++)
        {
            for(int j=0; j<V; j++)
            {
                if(i==k||j==k||i==j)
                    continue;
                if(dist[i][k]+dist[k][j]<dist[i][j])
                {
                    dist[i][j]=dist[i][k]+dist[k][j];
                    parent[i][j]=parent[k][j];
                }
            }
        }


    }
    cout<<"Floyd-Warshall Algorithm Implemented"<<endl;

}
void Graph::printDistMatrix()
{
    for(int i=0; i<V; i++)
    {


        for(int j=0; j<V; j++)
        {
            if(dist[i][j]>=-1000+INFINITY)
                cout<<"INF\t";
            else
                cout<<dist[i][j]<<"\t";

        }
        cout<<endl;
    }
    cout<<endl;
}
void Graph::printParentMatrix()
{
    for(int i=0; i<V; i++)
    {
        for(int j=0; j<V; j++)
        {
            if(parent[i][j]==-1)
                cout<<"NIL\t";
            else
                cout<<parent[i][j]+1<<"\t";
        }
        cout<<endl;
    }
    cout<<endl;

}
void Graph::cleanSpinfo()
{
    for(int ii=0; ii<V; ii++)
    {
        for(int j=0; j<V; j++)
        {
            dist[ii][j]=INFINITY;
        }
    }
    for(int ii=0; ii<V; ii++)
    {
        for(int j=0; j<V; j++)
        {
            parent[ii][j]=NIL;

        }

    }
    cout<<"APSP Matrices Cleared"<<endl;

}
double* Graph::bellmanFord(int s)
{

    for(int i=0; i<V; i++)
    {
        d[i]=INFINITY;


    }

    d[s]=0;
    // parent[s]=s;
    for(int i=0; i<V-1; i++)
    {
        for (auto j=edges.begin(); j!=edges.end(); ++j)
        {
            relax((*j)->get_source(),(*j)->get_dest(),(*j)->get_weight());
        }
    }
    for (auto j=edges.begin(); j!=edges.end(); ++j)
    {
        if (d[(*j)->get_source()]!= INFINITY&& d[(*j)->get_source()] + (*j)->get_weight()<d[(*j)->get_dest()])
            return NULL;
    }

    return d;

}
void Graph::relax(int u,int v, double w)
{
    if(d[v]>d[u]+w)
    {
        d[v]=d[u]+w;
        //parent[v]=u;

    }
}
void Graph::dijkstra(int src)
{

    for(int i=0; i<V; i++)
    {
        d[i]=INFINITY;
        p[i]=NIL;

    }

    priority_queue< nPair, vector <nPair>, greater<nPair> > pq;
    //vector<double> dis(V, INFINITY);
    pq.push(make_pair(0,src));
    d[src] = 0;
    // p[src]=NIL;

    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();

        list< pair<int, double> >::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
        {
            int v = (*i).first;
            double weight = (*i).second;

            if (d[v] > d[u] + weight)
            {
                p[v]=u;
                d[v] = d[u] + weight;
                pq.push(make_pair(d[v],v));
            }
        }
    }
}
double Graph::getshortestPath(int u,int v)
{
    // bellmanFord(u);
    return dist[u][v];
}

void Graph::johnson()
{

    int s=0;
    double *h=new double[V+1];
    Graph g1(true);
    g1.setnVertices(V+1);

    for( auto ii=edges.begin(); ii!=edges.end(); ++ii)
    {
        int u=(*ii)->get_source()+1;
        int v=(*ii)->get_dest()+1;
        double w=(*ii)->get_weight();
        g1.addEdge(u,v,w);
    }

    for(int i=1; i<V+1; i++)
        g1.addEdge(s,i,0);
    double *a=g1.bellmanFord(s);
    if(a==NULL)
        cout<<"It contains Negative edge cycle"<<endl;
    else
    {
        for(int i=0; i<V+1; i++)
        {
            h[i]=a[i+1];


        }


        for (auto j=edges.begin(); j!=edges.end(); ++j)

        {
            int u=(*j)->get_source();
            int v=(*j)->get_dest();

            double w =(*j)->get_weight()+h[u]-h[v];
            reweightEdge(u,v,w);
        }



        for(int i=0; i<V; i++)
        {
            dijkstra(i);
            for(int j=0; j<V; j++)
            {
                parent[i][j]=p[j];
                dist[i][j]=d[j]+h[j]-h[i];
            }
        }
        for (auto j=edges.begin(); j!=edges.end(); ++j)

        {
            int u=(*j)->get_source();
            int v=(*j)->get_dest();

            double w =(*j)->get_weight()-h[u]+h[v];
            reweightEdge(u,v,w);
        }




    }
    cout<<"Johnson's Algorithm Implemented"<<endl;


}
int main()
{
    int V,E,ch;
    int u, v;
    double w;
    cout<<"Enter the number of vertices and Edges : ";
    cin>>V>>E;
    Graph g(true);
    g.setnVertices(V);
    cout<<"Enter the source ,Destination and Weight of Edges :"<<endl;
    for(int i=0; i<E; i++)
    {
        cin>>u>>v>>w;
        g.addEdge(u-1,v-1,w);
    }
    cout<<"Graph Created"<<endl;
    while(1)
    {
        cout<<"\n 1. Clear APSP Matrices."<<endl;
        cout<<" 2. Implement Floyd Warshall Algorithm."<<endl;
        cout<<" 3. Implement Johnson's Algorithm"<<endl;
        cout<<" 4. Query"<<endl;
        cout<<" 5. Print Graph"<<endl;
        cout<<" 6. Print Distance Matrix"<<endl;
        cout<<" 7. Print Predecessor Matrix"<<endl;

        cin>>ch;
        if(ch==1)
        {
            g.cleanSpinfo();
        }
        else if(ch==2)
        {
            g.floydWarshall();
        }
        else if(ch==3)
        {
            g.johnson();
        }
        else if(ch==5)
        {
            g.printGraph();
        }
        else if(ch==6)
        {
            g.printDistMatrix();
        }
        else if(ch==7)
        {
            g.printParentMatrix();
        }
        else if(ch==4)
        {
            cout<<"Enter the source and Destination : "<<endl;
            cin>>u>>v;
            cout<<"The Shortest path weight: "<<g.getshortestPath(u-1,v-1)<<endl;
            cout<<"The path is:"<<endl;
            g.printShortestpath(u-1,v-1);

        }

        else
            break;
    }

}





