#include<bits/stdc++.h>
#define Red 0
#define Black 1
using namespace std;
struct node
{
    int data;
    node* left;
    node* right;
    node* parent;
    int color;
    node()
    {
        this->data = 0;
        left = right = parent = NULL;
        this->color = Red;
    }

};

class Red_BlackTree
{
    node *root;
    node *remove_data(node*&,int);
    void insert_in(int, node*);
    node *Find_in(int, node *);
    node *FindMin(node*);
    void Left_Rotate(node*&);
    void Right_Rotate(node*&);
    void InsertFixup(node*&);
    void print(node*);
    void DeleteFixup(node*&,node*&);
public:
    Red_BlackTree();
    node* Find(int);
    void Delete(int);
    void insert(int);
    void PrintRBT();
    //void inorder(node *);
    //void preorder(node *);

};
Red_BlackTree::Red_BlackTree()
{

    root= NULL;
}
node* Red_BlackTree::Find_in(int key,node *leaf)
{
    if(leaf!=NULL)
    {
        if(key==leaf->data)
            return leaf;
        if(key<leaf->data)
            return Find_in(key, leaf->left);
        else
            return Find_in(key, leaf->right);
    }
    else
        return NULL;
}
node* Red_BlackTree::Find(int key)
{
    return Find_in(key,root);
}
void Red_BlackTree::Left_Rotate(node *&x)
{
    node *y= x->right;
    x->right=y->left;
    if (x->right != NULL)
        x->right->parent = x;
    y->parent=x->parent;
    if(x->parent==NULL)
    {
        root=y;
    }
    else if(x==x->parent->left)
    {
        x->parent->left=y;
    }
    else
        x->parent->right=y;
    y->left=x;
    x->parent=y;

}
void Red_BlackTree::Right_Rotate(node *&x)
{

    node *y=x->left;
    //cout<<y->data;
    x->left=y->right;
    if (x->left != NULL)
        x->left->parent = x;
    y->parent=x->parent;

    if(x->parent==NULL)
    {
        root=y;
    }
    else if(x==x->parent->left)
    {

        x->parent->left=y;
    }
    else
    {
        // cout<<"eine ";
        x->parent->right=y;
    }

    y->right=x;
    x->parent=y;

}
void Red_BlackTree::insert_in(int key, struct node *leaf)
{
    if(key<leaf->data)
    {
        if(leaf->left!=NULL)
        {
            insert_in(key,leaf->left);
        }

        else
        {
            leaf->left=new node;
            leaf->left->parent=leaf;
            leaf->left->left=NULL;
            leaf->left->right=NULL;
            leaf->left->color=Red;
            leaf->left->data=key;



        }
    }
    else if(key>leaf->data)
    {
        if(leaf->right!=NULL)
            insert_in(key,leaf->right);
        else
        {
            leaf->right=new node;
            leaf->right->parent=leaf;
            leaf->right->left=NULL;
            leaf->right->right=NULL;
            leaf->right->color=Red;
            leaf->right->data=key;
        }

    }
}
void Red_BlackTree::InsertFixup( struct node *&z)
{
    // cout<<"fixup e ashe";
    node *parentz = NULL;
    node *grand_parent = NULL;
    while(z!=root&&z->color!=Black&&z->parent->color==Red)
    {
        parentz=z->parent;
        grand_parent=z->parent->parent;
        //cout<<"ei porjonto ashe "<<parentz->data<<" "<<grand_parent->data;
        if(parentz==grand_parent->left)
        {
            node *y =grand_parent->right; //uncle
            if(y!=NULL&&y->color==Red)
            {
                grand_parent->color=Red;
                parentz->color=Black;
                y->color=Black;
                z=grand_parent;
            }
            else
            {
                if(z==parentz->right)
                {
                    Left_Rotate(parentz);
                    //cout<<"ekhane elo";
                    z=parentz;
                    parentz=z->parent;

                }
                parentz->color=Black;
                grand_parent->color=Red;
                Right_Rotate(grand_parent);
                // z=parentz;
            }
        }
        else
        {
            node *y =grand_parent->left; //uncle

            if(y!=NULL&&y->color==Red)
            {
                grand_parent->color=Red;
                parentz->color=Black;
                y->color=Black;
                z=grand_parent;
            }
            else
            {

                if(z==parentz->left)
                {
                    //z=z->parent;

                    //
                    Right_Rotate(parentz);
                    //cout<<"ekhane elo";
                    z=parentz;
                    parentz=z->parent;


                }
                parentz->color=Black;
                grand_parent->color=Red;
                Left_Rotate(grand_parent);
            }
        }
    }
    //  cout<<"Eine ay  ";
    root->color=Black;
}
int colorx(node* x)
{
    int c;
    if(x==NULL)
        c=Black;
    else if(x->color==Black)
        c=Black;
    else
        c=Red;
    return c;
}
void Red_BlackTree::insert(int key)
{
    node *z=Find(key);
    if(z)
        return;
    else
    {
        if(root!=NULL)
        {
            insert_in(key,root);
            z=Find(key);
            // cout<<z->data<<" "<<z->parent->data<<endl;
            InsertFixup(z);


        }
        else
        {
            root=new node;
            root->data=key;
            root->left=NULL;
            root->right=NULL;
            root->parent=NULL;
            root->color=Black;

        }



    }
}
void Red_BlackTree::print(node *leaf)
{
    if(leaf)
    {
        cout<<leaf->data<<":";
        if(leaf->color==Red)
            cout<<"r";
        else
            cout<<"b";
    }
    else
        return;
    if(leaf->left==NULL&&leaf->right==NULL)
    {
        return;
    }

    else
    {
        cout<<"(";
        print(leaf->left);
        cout<<")(";
        print(leaf->right);
        cout<<")";
    }



}
void Red_BlackTree::PrintRBT()
{
    print(root);

}
node* Red_BlackTree:: FindMin(node *root)
{
    while(root->left != NULL)
        root = root->left;
    return root;
}

node *Red_BlackTree::remove_data(node *&leaf,int key)
{
    if(leaf==NULL)
        return leaf;
    else if(key<leaf->data)
        leaf->left=remove_data(leaf->left,key);
    else if(key>leaf->data)
        leaf->right= remove_data(leaf->right,key);
    else
    {
        if(leaf->left==NULL&&leaf->right==NULL)
        {
            leaf=NULL;
            delete leaf;

        }
        else if(leaf->left == NULL)
        {
            struct node *temp = leaf;
            leaf = leaf->right;
            leaf->parent=temp->parent;
            delete temp;
        }
        else if(leaf->right == NULL)
        {
            struct node *temp = leaf;
            leaf = leaf->left;
            leaf->parent=temp->parent;
            delete temp;
        }
        else
        {
            struct node *temp = FindMin(leaf->right);
            //cout<<leaf->right->data;
            leaf->data = temp->data;
            //cout<<temp->data;

            leaf->right = remove_data(leaf->right,temp->data);
        }

    }
    return leaf;
}
void Red_BlackTree::DeleteFixup(node *&x, node *&parentx)
{
    // cout<<parentx->data;
    //cout<<parentx->righ->data;
    int c=colorx(x);



    while(x!=root&&c==Black)
    {

        //cout<<"aslo";
        if(parentx->right==NULL&&parentx->left==NULL)
        {
            if(colorx(parentx)==Red)
            {
                parentx->color=Black;
                return;
            }

            else
            {
                x=parentx;
                parentx=x->parent;
            }

        }
        else if(parentx->left==x)
        {
            // cout<<"aslo";
            node *w=parentx->right;
            //cout<<w->data;
            if(w->color==Red)
            {
                w->color=Black;
                parentx->color=Red;
                Left_Rotate(parentx);
                w=parentx->right;
            }

            if(colorx(w->right)==Black&&colorx(w->left)==Black)
            {
                w->color=Red;
                x=parentx;
                parentx=parentx->parent;
                c=x->color;
            }
            else
            {

                if(colorx(w->right)==Black)
                {
                    // cout<<"aslo";
                    w->left->color=Black;
                    w->color=Red;
                    Right_Rotate(w);
                    w=parentx->right;

                }

                w->color=parentx->color;
                parentx->color=Black;

                w->right->color=Black;
                Left_Rotate(parentx);
                x=root;
                c=Black;
            }

        }
        else
        {

            //cout<<"aslo";
            node *w=parentx->left;
            //cout<<w->data;
            if(w->color==Red)
            {
                w->color=Black;
                parentx->color=Red;
                Right_Rotate(parentx);
                w=parentx->left;
            }
            if(colorx(w->right)==Black&&colorx(w->left)==Black)
            {
                //cout<<"aslo";
                w->color=Red;
                x=parentx;
                parentx=x->parent;
                c=x->color;
            }
            else
            {
                if(colorx(w->left)==Black)
                {
                    w->right->color=Black;
                    w->color=Red;
                    Left_Rotate(w);
                    w=parentx->left;

                }
                w->color=parentx->color;
                parentx->color=Black;
                w->left->color=Black;
                Right_Rotate(parentx);
                x=root;
                c=Black;
            }




        }

    }



    x->color=Black;

}
void Red_BlackTree::Delete(int key)
{
    if(Find(key))
    {
        node *z=Find(key);
        node *y,*x;

        if(z->left==NULL||z->right==NULL)
            y=z;
        else
        {
            y = FindMin(z->right);
        }
        // cout<<y->data ;
        node* parenty=y->parent;
        if(y->left!=NULL)
            x=y->left;
        else if(y->right!=NULL)
            x=y->right;
        else
        {
            x=NULL;
            // cout<<"aslo";
        }

        int c=y->color;

        root=remove_data(root,key);

        if(root)
        {

            if(c==Black)
            {
                //cout<<"aslo";
                DeleteFixup(x,parenty);
            }

        }

    }


    return;
}


int main()
{
    Red_BlackTree rbt;
    ifstream file;
    // FILE *file2;
    file.open("input0.txt");
    freopen("output.txt","w",stdout);
    int n;
    char i;
    //string l,nl;
    while(!file.eof())
    {

        file>>i>>n;




        if(i=='I')
        {


            // cin>>n;
            rbt.insert(n);
            rbt.PrintRBT();
            cout<<endl;
            //break;
        }
        else if(i=='F')
        {

            //cin>>n;
            if(rbt.Find(n))
                cout<<"True"<<endl;
            else
                cout<<"False"<<endl;
            // break;

        }
        else if(i=='D')
        {

            // cin>>n;
            rbt.Delete(n);
            rbt.PrintRBT();
            cout<<endl;
            // break;

        }
        else
            cout<<" Command NOT found"<<endl;





    }


//file.close();
//file2->close();
    return 0;

}




