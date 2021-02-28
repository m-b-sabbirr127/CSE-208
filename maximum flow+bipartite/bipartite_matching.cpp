#include<bits/stdc++.h>
#define NIL -1
#define NULL_VALUE -999999999
#define INFINITY 999999999
#define white 0
#define black 1
using namespace std;



class Queue
{
    int queueInitSize ;
    int queueMaxSize;
    int * data;
    int length;
    int front;
    int rear;
public:
    Queue();
    ~Queue();
    void enqueue(int item); //insert item in the queue
    int dequeue(); //returns the item according to FIFO
    bool empty(); //return true if Queue is empty
};

Queue::Queue()
{
    queueInitSize = 2 ;
    queueMaxSize = queueInitSize;
    data = new int[queueMaxSize] ; //allocate initial memory
    length = 0 ;
    front = 0;
    rear = 0;
}


void Queue::enqueue(int item)
{
    if (length == queueMaxSize)
    {
        int * tempData ;
        //allocate new memory space for tempList
        queueMaxSize = 2 * queueMaxSize ;
        tempData = new int[queueMaxSize] ;
        int i, j;
        j = 0;
        for( i = rear; i < length ; i++ )
        {
            tempData[j++] = data[i] ; //copy items from rear
        }
        for( i = 0; i < rear ; i++ )
        {
            tempData[j++] = data[i] ; //copy items before rear
        }
        rear = 0 ;
        front = length ;
        delete[] data ; //free the memory allocated before
        data = tempData ; //make list to point to new memory
    }

    data[front] = item ; //store new item
    front = (front + 1) % queueMaxSize ;
    length++ ;
}


bool Queue::empty()
{
    if(length == 0)
        return true ;
    else
        return false ;
}


int Queue::dequeue()
{
    if(length == 0)
        return NULL_VALUE ;
    int item = data[rear] ;
    rear = (rear + 1) % queueMaxSize ;  // circular queue implementation
    length-- ;
    return item ;
}


Queue::~Queue()
{
    if(data)
        delete[] data; //deallocate memory
    data = 0; //set to NULL
}
class Edge
{
    int dest,flow,capacity;

public:
    Edge();
    void setter(int,int,int);
    int get_dest();
    int get_capacity();
    int get_flow();
    void set_flow(int);
    // void print();

};
Edge::Edge()
{
    dest=0;
    capacity=0;
    flow=0;

}
void Edge::setter(int v,int c,int f)
{
    dest=v;
    capacity=c;
    flow=f;
}

int Edge::get_capacity()
{
    return capacity;
}
int Edge::get_dest()
{
    return dest;
}
int Edge::get_flow()
{
    return flow;
}
void Edge::set_flow(int f)
{
    this->flow=f;
}


class Graph
{
    int V,E;
    vector<Edge*> *adj;
    int *color, *parent;
    fstream file2;


public:
    Graph();
    void setnVertices(int);
    bool addEdge(int u, int v, int c);
    Edge* searchEdge(int,int);
    bool bfs(int,int,int*);
    int Ford_Fulkerson(int,int);
    void printmatching(int,int);
    bool is_bipartite();
    bool is_bipartiteUtil(int);
    void bipartite_matching();
    ~Graph();




};
Graph::Graph()
{
    V=0;

}


void Graph::setnVertices(int V)
{
    this->V = V;
    adj = new vector<Edge*>[V];
    color=new int[V];
    parent=new int[V];


}

bool Graph::addEdge(int u, int v, int c)
{
    if(u==v || v>=V||u>=V)
        return false;
    Edge* e=searchEdge(u,v);
    if(e!=NULL)
    {
        int c_prv=e->get_capacity();
        e->setter(v,c+c_prv,0);
        adj[u].push_back(e);

    }
    else
    {
        Edge* e1=new Edge;
        e1->setter(v,c,0);
        adj[u].push_back(e1);

    }



    return true;
}

Edge* Graph::searchEdge(int u, int v)

{
    for( auto ii=adj[u].begin(); ii!=adj[u].end(); ++ii)
    {
        if((*ii)->get_dest()==v)
        {

            return (*ii);
        }


    }
    return NULL;


}
bool Graph::bfs(int s,int t,int parent[])
{

    for(int i=0; i<V; i++)
        color[i]=white;
    Queue q;
    q.enqueue(s);
    parent[s]=NIL;
    color[s]=black;

    while (!q.empty())
    {
        int u =  q.dequeue();


        for (auto ii=adj[u].begin(); ii!=adj[u].end(); ++ii)
        {
            int v =(*ii)->get_dest();
            int c =(*ii)->get_capacity();

            if (color[v]==white&&c>0)
            {
                q.enqueue(v);
                parent[v]=u;
                color[v]=black;
            }
        }
    }
    return (color[t]==black);
}
int Graph::Ford_Fulkerson(int s,int t)
{
    Graph residual;
    residual.setnVertices(V);
    //cout<<"ekhane dhukse";
    //residual.printg();
    for(int u=0; u<V; u++)
    {
        for(auto i=adj[u].begin(); i!=adj[u].end(); ++i)
        {
            int v=(*i)->get_dest();
            int c=(*i)->get_capacity();
            residual.addEdge(u,v,c);
            residual.addEdge(v,u,0);



        }
    }


    int max_flow = 0;

    while (residual.bfs( s, t, parent))
    {
        //for(int v=t; v!=s; v=parent[v])
        //cout<<v<<"<-";
        // cout<<endl;
        int path_flow = INFINITY;
        for (int v=t; v!=s; v=parent[v])
        {
            int u = parent[v];
            Edge* e= residual.searchEdge(u,v);
            path_flow = min(path_flow,e->get_capacity());
        }


        for (int v=t; v!= s; v=parent[v])
        {
            int u = parent[v];
            Edge* e_dir= residual.searchEdge(u,v);

            Edge* e_rev= residual.searchEdge(v,u);


            int c_dir= e_dir->get_capacity();
            int c_rev=e_rev->get_capacity();
            e_dir->setter(v,c_dir-path_flow,0);
            //cout<<"e pay";
            e_rev->setter(u,c_rev+path_flow,0);

            Edge* e= searchEdge(u,v);

            if(e!=NULL)
            {
                int f=e->get_flow();
                e->set_flow(f+path_flow);
            }
            else
            {
                Edge* er= searchEdge(v,u);
                int fr=er->get_flow();
                er->set_flow(fr-path_flow);



            }

        }

        max_flow += path_flow;

    }

    return max_flow;
}
void Graph::printmatching(int s,int t)
{
    file2.open("output.txt",ios::out);
    file2<<Ford_Fulkerson(s,t)<<endl;


    for(int u=0; u<V; u++)
    {
        for(auto ii=adj[u].begin(); ii!=adj[u].end(); ++ii)
        {
            int v=(*ii)->get_dest();
            int f=(*ii)->get_flow();
            if(v!=s&&u!=s&&v!=t&&u!=t&&f==1)
                file2<<u<<"  "<<v<<endl;

        }

    }
}
bool Graph::is_bipartiteUtil(int src)
{

    color[src] = black;

    Queue q;
    q.enqueue(src);
    while (!q.empty())
    {

        int u = q.dequeue();
        if (searchEdge(u,u)!=NULL)
            return false;

        for (int v = 0; v < V; ++v)
        {
            Edge* e= searchEdge(u,v);
            if (e!=NULL && color[v] == -1)
            {
                color[v] = 1 - color[u];
                q.enqueue(v);
            }

            else if (e!=NULL && color[v] == color[u])
                return false;
        }
    }

    return true;
}
bool Graph::is_bipartite()
{

    for (int i = 0; i < V; ++i)
        color[i] = -1;
    for (int i = 0; i < V; i++)
    {
        if (color[i] == -1)
            if (is_bipartiteUtil(i) == false)
                return false;
    }
    return true;
}

void Graph::bipartite_matching()
{
    file2.open("output.txt",ios::out);
    if(is_bipartite())
    {
        Graph g1;
        g1.setnVertices(V+2);
        vector<int>left;
        vector<int>right;
        for(int v=0; v<V; v++)
        {
            if(color[v]==white)
                left.push_back(v);
            else
                right.push_back(v);
        }
        //for(int i=0;i<V;i++)
        //cout<<color[i]<<endl;

        int s=V,t=V+1;
        for(int u=0; u<V; ++u)
        {
            for(auto ii=adj[u].begin(); ii!=adj[u].end(); ++ii)
            {
                int v=(*ii)->get_dest();
                if(color[u]==white)
                    g1.addEdge(u,v,1);


            }
        }

        for(auto i=left.begin(); i!=left.end(); ++i)
        {
            g1.addEdge(s,(*i),1);

        }
        for(auto i=right.begin(); i!=right.end(); ++i)
        {
            g1.addEdge((*i),t,1);

        }
        g1.printmatching(s,t);




    }
    else
    {
        file2<<"The Graph is not Bipartite"<<endl;
    }


}

Graph::~Graph()
{
    for(int i=0; i<V; i++)

        adj[i].clear();
    delete[] color;
    delete[] parent;
    file2.close();
}
int main()
{
    int n, m;
    fstream file;
    Graph g;

    file.open("in7.txt",ios::in);

    //char line[10];
    string line;
    file>>line;
    n = stoi(line);
    g.setnVertices(n);
    file>>line;
    m=stoi(line);
    //cout<<n<<" "<<m;

    while(m--)
    {
        file>>line;
        int u=stoi(line);
        file>>line;
        int v=stoi(line);
        g.addEdge(u,v,1);
        g.addEdge(v,u,1);


    }
    g.bipartite_matching();


}


