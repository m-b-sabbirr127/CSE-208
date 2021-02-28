#include<bits/stdc++.h>
using namespace std;
uint64_t auxhash(const char *str)
{
    union
    {
        uint64_t h;
        uint8_t u[8];
    };
    int i=0;
    h=strlen(str);
    while (*str)
    {
        u[i%8] += *str + i + (*str >> ((h/(i+1)) % 5));
        str++;
        i++;
    }
    return h%10000;
}

unsigned long hash1(const char *str)
{
    unsigned long hash = 5381;
    int c;
    while(c = *str++)
    {
        hash = ((hash<<5)+hash)+c;
    }
    return hash%10000;
}

unsigned long hash2(const char *str)
{
    unsigned long hash = 0;
    int c;
    while(c=*str++)
        hash=c+(hash<<6)+(hash<<16)-hash;
    return hash%10000;
}
class hashNode
{
    string key;
    int value;

public:
    hashNode()
    {
        key="";
        value=0;
    }
    void setter(string k,int v)
    {
        key=k;
        value=v;
    }
    string getString()
    {
        return key;
    }
    int getInt()
    {
        return value;
    }
} ;
class HashTableChaining
{
    vector<hashNode*> *table;
    int n,hf;
public:
    HashTableChaining(int);
    int insertHash(string,int);
    void deleteHash(string);
    int searchHash(string);
    void setHash(int);
    ~HashTableChaining();
};

HashTableChaining::HashTableChaining(int n)
{
    this->n=n;
    table = new vector<hashNode*>[n];
}
void HashTableChaining::setHash(int m)
{
    hf=m;
}
int HashTableChaining::insertHash(string k,int v)
{
    int index,col=0;
    char *st=const_cast<char*>(k.c_str());
    hashNode* h=new hashNode;
    h->setter(k,v);

    if(hf==1)
    {
        index=hash1(st)%n;

    }
    else
        index=hash2(st)%n;
    if(!table[index].empty())
        col++;
    table[index].push_back(h);
    return col;
}
int HashTableChaining::searchHash(string k)
{
    int index;
    int p=0;
    char *st=const_cast<char*>(k.c_str());
    if(hf==1)
    {
        index=hash1(st)%n;

    }
    else
        index=hash2(st)%n;
    for( auto ii=table[index].begin(); ii!=table[index].end(); ++ii)
    {
        if(k==(*ii)->getString())
        {
            p++;
            return p;
        }
        else
            p++;
    }
    return p;

}
void HashTableChaining::deleteHash(string k)
{
    char *st=const_cast<char*>(k.c_str());
    int index;
    if(hf==1)
    {
        index=hash1(st)%n;

    }
    else
        index=hash2(st)%n;
    for( auto ii=table[index].begin(); ii!=table[index].end(); ++ii)
    {
        if(k==(*ii)->getString())
        {
            table[index].erase(ii);
            return;
        }
    }
    return;
}
HashTableChaining::~HashTableChaining()
{
    for(int i=0; i<n; i++)

        table[i].clear();
}

class HashTableDoubleHashing
{
    hashNode** table;
    int n,hf;
public:
    HashTableDoubleHashing(int);
    int insertHash(string,int);
    void deleteHash(string);
    int searchHash(string);
    void setHash(int);
    ~HashTableDoubleHashing();
};
HashTableDoubleHashing::HashTableDoubleHashing(int n)
{
    table=new hashNode*[n];
    this->n=n;
    for(int i=0; i<n; i++)
    {
        table[i]=NULL;
    }
}
void HashTableDoubleHashing::setHash(int h)
{
    hf=h;
}
int HashTableDoubleHashing::insertHash(string k,int v)
{
    int index,col=0;
    int i=0;
    char *st=const_cast<char*>(k.c_str());
    hashNode* h=new hashNode;
    h->setter(k,v);
    for(i=0; i<n; i++)
    {
        if(hf==1)
            index=(hash1(st)+i*auxhash(st))%n;
        else
            index=(hash2(st)+i*auxhash(st))%n;
        if(table[index]==NULL)
        {
            table[index]=h;
            return col;
        }
        else
        {
            col++;
        }

    }

    return col;
}
int HashTableDoubleHashing::searchHash(string k)
{
    int index,probe=0;
    int i=0;
    char *st=const_cast<char*>(k.c_str());
    for(i=0; i<n; i++)
    {
        if(hf==1)
            index=(hash1(st)+i*auxhash(st))%n;
        else
            index=(hash2(st)+i*auxhash(st))%n;
        probe++;
        if(table[index]!=NULL)
        {
            if(table[index]->getString()==k)
                return probe;

        }
    }
    return probe;

}
void HashTableDoubleHashing::deleteHash(string k)
{
    int index;
    char *st=const_cast<char*>(k.c_str());

    for(int i=0; i<n; i++)
    {
        if(hf==1)
            index=(hash1(st)+i*auxhash(st))%n;
        else
            index=(hash2(st)+i*auxhash(st))%n;
        if(table[index]!=NULL)
        {
            if(table[index]->getString()==k)
            {
                hashNode *h=table[index];
                table[index]=NULL;
                delete h;
                return;
            }

        }

    }
    return;
}
HashTableDoubleHashing::~HashTableDoubleHashing()
{
    for(int i=0; i<n; i++)
    {
        hashNode *h=table[i];
        delete h;
    }
    delete[] table;
}
class HashTableCustomProbing
{
    hashNode** table;
    int n,hf;
public:
    HashTableCustomProbing(int);
    int insertHash(string,int);
    void deleteHash(string);
    int searchHash(string);
    void setHash(int);
    ~HashTableCustomProbing();
};
HashTableCustomProbing::HashTableCustomProbing(int n)
{
    table=new hashNode*[n];
    this->n=n;
    for(int i=0; i<n; i++)
    {
        table[i]=NULL;
    }
}
void HashTableCustomProbing::setHash(int h)
{
    hf=h;
}
int HashTableCustomProbing::insertHash(string k,int v)
{
    int index,col=0;
    int i=0;
    char *st=const_cast<char*>(k.c_str());
    hashNode* h=new hashNode;
    h->setter(k,v);
    for(i=0; i<n; i++)
    {
        if(hf==1)
            index=(hash1(st)+7*i*auxhash(st)+3*i*i)%n;
        else
            index=(hash2(st)+7*i*auxhash(st)+3*i*i)%n;
        if(table[index]==NULL)
        {
            table[index]=h;
            return col;
        }
        else
            col++;
    }

    return col;
}
int HashTableCustomProbing::searchHash(string k)
{
    int index,probe=0;
    int i=0;
    char *st=const_cast<char*>(k.c_str());
    for(i=0; i<n; i++)
    {
        if(hf==1)
            index=(hash1(st)+7*i*auxhash(st)+3*i*i)%n;
        else
            index=(hash2(st)+7*i*auxhash(st)+3*i*i)%n;
        probe++;
        if(table[index]!=NULL)
        {
            if(table[index]->getString()==k)
                return probe;

        }
    }
    return probe;

}
void HashTableCustomProbing::deleteHash(string k)
{
    int index;
    char *st=const_cast<char*>(k.c_str());

    for(int i=0; i<n; i++)
    {
        if(hf==1)
            index=(hash1(st)+7*i*auxhash(st)+3*i*i)%n;
        else
            index=(hash2(st)+7*i*auxhash(st)+3*i*i)%n;
        if(table[index]!=NULL)
        {
            if(table[index]->getString()==k)
            {
                hashNode *h=table[index];
                table[index]=NULL;
                delete h;
                return;

            }

        }
    }
    return;
}
HashTableCustomProbing::~HashTableCustomProbing()
{
    for(int i=0; i<n; i++)
    {
        hashNode *h=table[i];
        delete h;
    }
    delete[] table;
}

string randstring(int n)
{
    char letters[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q',
                        'r','s','t','u','v','w','x',
                        'y','z'
                       };
    string ran = "";
    for (int i=0; i<n; i++)
        ran=ran + letters[rand() % 26];
    return ran;
}
int main()
{
    cout<<"Enter the size of the Hash Table: "<<endl;
    int n,c,ch,choice;
    cin>>n;
    srand(time(NULL));
    string *str=new string[n];
    string s;
    for(int i=0; i<n; i++)
    {
        str[i]=randstring(7);
    }
    cout<<"chaining method:"<<endl;
    //hash1
    cout<<"Hash 1: ";
    HashTableChaining hc(n);
    int col=0;
    hc.setHash(1);
    for(int i=0; i<n; i++)
    {
        col=col+hc.insertHash(str[i],i+1);
    }
    cout<<"Number of collisions: "<<col<<endl;
    int probe=0;
    for(int i=0; i<1000; i++)
    {
        s=str[rand()%n];
        probe=probe+hc.searchHash(s);
    }
    double avg=probe/1000;
    cout<<" Average Probes :"<<avg<<endl;
    cout<<"Hash 2: ";
    HashTableChaining hc1(n);
    col=0;
    hc1.setHash(2);
    for(int i=0; i<n; i++)
    {
        col=col+hc1.insertHash(str[i],i+1);
    }
    cout<<"Number of collisions: "<<col<<endl;
    probe=0;
    for(int i=0; i<1000; i++)
    {
        s=str[rand()%n];
        probe=probe+hc1.searchHash(s);
    }
    avg=probe/1000;
    cout<<" Average Probes :"<<avg<<endl;
    cout<<"Double Hashing method:"<<endl;
    //hash1
    cout<<"Hash 1: ";
    HashTableDoubleHashing hd(n);
    col=0;
    hd.setHash(1);
    for(int i=0; i<n; i++)
    {
        col=col+hd.insertHash(str[i],i+1);
    }
    cout<<"Number of collisions: "<<col<<endl;
    probe=0;
    for(int i=0; i<1000; i++)
    {
        s=str[rand()%n];
        probe=probe+hd.searchHash(s);
    }
    avg=probe/1000;
    cout<<" Average Probes :"<<avg<<endl;
    cout<<"Hash 2: ";
    HashTableDoubleHashing hd1(n);
    col=0;
    hd1.setHash(2);
    for(int i=0; i<n; i++)
    {
        col=col+hd1.insertHash(str[i],i+1);
    }
    cout<<"Number of collisions: "<<col<<endl;
    probe=0;
    for(int i=0; i<1000; i++)
    {
        s=str[rand()%n];
        probe=probe+hd1.searchHash(s);
    }
    avg=probe/1000;
    cout<<" Average Probes :"<<avg<<endl;
    cout<<"Custom Probing method:"<<endl;
    //hash1
    cout<<"Hash 1: ";
    HashTableCustomProbing hp(n);
    col=0;
    hp.setHash(1);
    for(int i=0; i<n; i++)
    {
        col=col+hp.insertHash(str[i],i+1);
    }
    cout<<"Number of collisions: "<<col<<endl;
    probe=0;
    for(int i=0; i<1000; i++)
    {
        s=str[rand()%n];
        probe=probe+hp.searchHash(s);
    }
    avg=probe/1000;
    cout<<" Average Probes :"<<avg<<endl;
    cout<<"Hash 2: ";
    HashTableCustomProbing hp1(n);
    col=0;
    hp1.setHash(2);
    for(int i=0; i<n; i++)
    {
        col=col+hp1.insertHash(str[i],i+1);
    }
    cout<<"Number of collisions: "<<col<<endl;
    probe=0;
    for(int i=0; i<1000; i++)
    {
        s=str[rand()%n];
        probe=probe+hp1.searchHash(s);
    }
    avg=probe/1000;
    cout<<" Average Probes :"<<avg<<endl;



}

