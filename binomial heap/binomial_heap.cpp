#include<bits/stdc++.h>
#define INFINITY 9999999
using namespace std;
struct node
{
public:

    int data,degree;
    node *child;
    node *parent;
    node *sibling;
};
node* Reverse(node* head)
{

    if (head == NULL || head->sibling == NULL)
        return head;
    node* rest = Reverse(head->sibling);
    head->sibling->sibling = head;
    head->sibling = NULL;

    return rest;
}

class Binomial_heap
{

public:
    node* head;
    Binomial_heap();
    int Find_min();
    int Extract_min();
    void Insert(int);
    void Union(Binomial_heap);
    void print();
    void link(node*,node*);



};
Binomial_heap::Binomial_heap()
{
    head=NULL;
}
void Binomial_heap::link(node* y,node* z)
{
    y->parent=z;
    y->sibling=z->child;
    z->child=y;
    z->degree=z->degree+1;
}
int Binomial_heap::Find_min()

{
    int minimum=INFINITY;
    node* x=this->head;
    while(x!=NULL)
    {
        if (x->data < minimum)
            minimum=x->data;
        x=x->sibling;

    }
    return minimum;
}
void Binomial_heap::print()
{
    cout<<"Printing Binomial Heap..."<<endl;
    node *z=head;
    while(z!=NULL)
    {
        cout<<"Binomial Tree, B"<<z->degree<<endl;
        int i=1;
        cout<<"Level 0: "<<z->data<<endl;
        vector<node*> v,v1;
        node* y=z->child;
        while(y!=NULL)
        {
            v.push_back(y);
            y=y->sibling;

        }
        while(!v.empty())
        {
            cout<<"Level "<<i<<": ";
            for(auto ii=v.begin(); ii!=v.end(); ++ii)
            {

                cout<<(*ii)->data<<" ";
                node *x=(*ii)->child;
                while(x!=NULL)
                {
                    v1.push_back(x);
                    x=x->sibling;
                }
            }
            cout<<endl;
            v=v1;
            v1.clear();
            i++;
        }
        z=z->sibling;
    }
}
void Binomial_heap::Union(Binomial_heap bh)
{
    if(this->head==NULL)
    {
        this->head=bh.head;
    }
    else
    {

        node* x=this->head;
        node *y=bh.head;
        Binomial_heap final_heap;
        //cout<<"ashe";

        if(x->degree <= y->degree)
        {
            final_heap.head=x;
            x=x->sibling;
        }
        else
        {
            final_heap.head=y;
            y=y->sibling;
        }
        node *z=final_heap.head;
        while (x!=NULL&&y!=NULL)
        {
            if(x->degree <= y->degree)
            {
                z->sibling=x;
                z=z->sibling;
                x=x->sibling;
            }
            else
            {
                z->sibling=y;
                z=z->sibling;
                y=y->sibling;
            }
        }
        while (x!=NULL)
        {
            z->sibling=x;
            z=z->sibling;
            x=x->sibling;
        }

        while (y!=NULL)
        {
            z->sibling=y;
            z=z->sibling;
            y=y->sibling;
        }
        this->head=final_heap.head;
        x=this->head;
        node* prev_x=NULL;
        node* next_x=x->sibling;
        while(next_x!=NULL)
        {
            if(x->degree!=next_x->degree||(next_x->sibling!=NULL&&next_x->sibling->degree==x->degree))
            {
                prev_x=x;
                x=next_x;

            }
            else
            {
                if(x->data<=next_x->data)
                {
                    x->sibling=next_x->sibling;
                    link(next_x,x);

                }
                else
                {
                    if(prev_x==NULL)
                    {
                        head=next_x;


                    }
                    else
                    {
                        prev_x->sibling=next_x;
                    }
                    link(x,next_x);
                    x=next_x;
                }

            }
            next_x=x->sibling;


        }
    }
}
void Binomial_heap::Insert(int key)
{
    Binomial_heap bh;

    node* z=new node;

    z->parent=NULL;
    z->child=NULL;
    z->sibling=NULL;
    z->data=key;
    z->degree=0;
    //cout<<"ashe";
    //cout<<z->data<<" "<<z->degree;
    if(this->head==NULL)
    {
        this->head=z;
        return;
    }
    bh.head=z;

    Union(bh);

}
int Binomial_heap::Extract_min()
{
    int minimum=INFINITY;
    node* x=this->head;
    node* temp;
    node* prev;
    while(x!=NULL)
    {
        if (x->data < minimum)
        {
            minimum=x->data;
            temp=x;
        }

        x=x->sibling;

    }
    if(temp==head)
    {
        head=temp->sibling;
    }
    else
    {

        node* z=head;
        while(z!=NULL)
        {
            if(z->sibling==temp)
            {
                prev=z;
                break;
            }
            z=z->sibling;
        }
        prev->sibling=temp->sibling;

    }
    Binomial_heap h2;
    temp->child=Reverse(temp->child);
    h2.head=temp->child;
    delete temp;
    Union(h2);

    return minimum;
}
int* getNumberFromString(string s)
{
    int *arr=new int[1000];
    int i=1,temp_int;
    stringstream str_strm;
    str_strm << s;
    string temp_str;
    while(!str_strm.eof())
    {
        str_strm >> temp_str;
        if(stringstream(temp_str) >> temp_int)
        {
            arr[i++]=temp_int;
            //cout<<temp_int;
        }
        temp_str = "";
    }
    arr[0]=i;
    return arr;
}

int main()
{
    Binomial_heap h;
    freopen("output.txt","w",stdout);
    int *arr=new int[1000];
    fstream newFile;
    newFile.open("in1.txt",ios::in);
    if (!newFile)
    {
        cout << "\nError occurs while opening file.\n";
        return 1;
    }
    if (newFile.is_open())
    {
        string line;
        while(getline(newFile,line))
        {
            if(line[0]=='I')
            {
                // cout<<line[0]<<endl;
                arr=getNumberFromString(line);
                h.Insert(arr[1]);
            }
            else if(line[0]=='F')
            {
                //  cout<<line[0]<<endl;
                int m=h.Find_min();
                if(m==INFINITY)
                    cout<<"Binomial heap is empty"<<endl;
                else
                    cout<<"Find min returned "<<m<<endl;
            }
            else if(line[0]=='E')
            {
                int m=h.Extract_min();
                if(m==INFINITY)
                    cout<<"Binomial heap is empty"<<endl;
                else
                    cout<<"Extract-min returned "<<m<<endl;
            }
            else if(line[0]=='P')
            {
                h.print();
            }
            else if(line[0]=='U')
            {
                arr=getNumberFromString(line);
                Binomial_heap h2;
                for(int i=1; i<arr[0]; i++)
                {
                    h2.Insert(arr[i]);
                    //cout<<arr[i]<<" ";
                }
                //cout<<h2.head->data;
                h.Union(h2);
            }
            else
                break;
        }
        newFile.close();
    }
    return 0;


}

