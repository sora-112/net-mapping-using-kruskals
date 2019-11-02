#include<iostream>
#include<vector>
#include<utility>
#include<algorithm>
#include<string>
#include<conio.h>
#include<windows.h>
#include<mysql.h>
#include<sstream>


using namespace std;


class node{
    int id;
    string name;
    int users;
    friend class graph;
    friend class edge;
public:
    node(int id,string name,int users){
        this->id = id;
        this->name = name;
        this->users = users;
    }
    void createnode();
    };

class edge{

    node* begin,*end;
    int weight;
    friend class graph;
public:
    edge(node *start,node *end,int weight){
        this->begin = start;
        this->end = end;
        this->weight = weight;
    void createedge();
    }

};
class disjoint{
    int *parent,*rnk;
    int n;
    friend class graph;
public:
    disjoint(int n){
        this->n = n;
        parent = new int[n+1];
        rnk = new int[n+1];

        for(int i=0;i<=n;i++){
            rnk[i] = 0;
            parent[i] = i;
        }
    }
    int find1(int u){
        if(u!=parent[u])
            parent[u] = find1(parent[u]);
        return parent[u];

    }
    void merge(int x,int y){
        x = find1(x);
        y = find1(y);
        if(rnk[x]>rnk[y])
            parent[y] = x;
        else if(rnk[x]<rnk[y])
            parent[x] = y;
        else{
            parent[y] = x;
            rnk[x]++;
        }

    }
};
class graph{

    int id;
    edge* earray[100];
    int ecount = 0;
    node* array[100];
    int count = 0;
    pair <int, pair<int, int> > p[100];
    pair <int, pair<int, int> > q[100];

     int ccount = 0;

public:
    void kruskal();
    node* getnode(int id);
    void displaynodes();
    void displayedges();
    void createGraph();
    void createPair();
    void diaplaySeq();
    void sorte();
    void createdat();
    void createdated();
    void indat();
    void indatedge();
    void checkbreak();
    void searchnode();
    void createnode();
    void createedge();

};

void graph::createnode(){
    string name;
    int id,users;
    cout<<"Enter name:"<<endl;
    cin>>name;
    cout<<"Enter id"<<endl;
    cin>>id;
    cout<<"Enter no. of users"<<endl;
    cin>>users;
    node* newnode = new node(id,name,users);
    array[count] = newnode;
    indat();
    count++;

}

node* graph::getnode(int id){
    int i;
    for(i=0;i<count;i++){
        if(array[i]->id==id){
        return array[i];
        }
    }
}

void graph::searchnode(){
    int id;
    cout<<"Enter Network id"<<endl;
    cin>>id;
    cout<<"Cabinet location name "<<getnode(id)->name<<endl;
    cout<<"No of users"<<getnode(id)->users<<endl;


}
void graph::displaynodes(){
    int it;
    for(it=0;it<count;it++){
        cout<<"Node "<<it+1<<endl;
        cout<<"Location Name: "<<array[it]->name<<endl;
        cout<<"Network ID: "<<array[it]->id<<endl;
        cout<<"Users: "<<array[it]->users<<endl;
        cout<<"\n";
        cout<<"\n";
    }
}

void graph::createdat(){
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn=mysql_init(0);
    conn=mysql_real_connect(conn,"192.168.43.217","admin","admin","trial",0,NULL,0);
    if(conn)
    {
        cout<<"loading from Database....."<<endl;
        cout<<"\n";
        cout<<"\n";
    }
    else
        cout<<"Not connected"<<endl;
    int qstate=mysql_query(conn,"select * from test");
    if(!qstate)
        {
            res=mysql_store_result(conn);
            while(row=mysql_fetch_row(res))
            {
                int id=0;
                int users = 0;
                stringstream geek(row[0]);
                geek>>id;
                stringstream geek1(row[2]);
                geek1>>users;
                string name = row[1];

                node * newnode = new node(id,name,users);
                array[count] = newnode;
                count++;

                //cout<<row[0]<<row[1]<<row[2]<<endl;
            }
        }
    else
        cout<<"Failed"<<endl;




}
void graph::createdated()
{
    MYSQL* conn1;
    MYSQL_ROW row1;
    MYSQL_RES* res1;
    conn1=mysql_init(0);
    conn1=mysql_real_connect(conn1,"192.168.43.217","admin","admin","trial",0,NULL,0);
    if(conn1)
    {
        cout<<"loading from Database....."<<endl;
    }
    else
        cout<<"Not connected"<<endl;

    int qstate1=mysql_query(conn1,"select * from edges");
    if(!qstate1)
        {
            res1=mysql_store_result(conn1);
            while(row1=mysql_fetch_row(res1))
            {
                int start=0;
                int stop = 0;
                int weight = 0;
                stringstream geek2(row1[0]);
                geek2>>start;
                stringstream geek3(row1[1]);
                geek3>>stop;
                stringstream geek4(row1[2]);
                geek4>>weight;



                edge * newedge = new edge(getnode(start),getnode(stop),weight);
                earray[ecount] = newedge;
                ecount++;


                //cout<<row[0]<<row[1]<<row[2]<<endl;
            }
        }
    else
        cout<<"Failed"<<endl;

}
void graph::createPair(){
    int i,j;
    for(i=0;i<ecount;i++){
        p[i] = make_pair(earray[i]->weight,make_pair(earray[i]->begin->id,earray[i]->end->id));
    }
    sort(p,p+ecount);



}
void graph::createedge(){
        int start,stop,weight;
        cout<<"Enter Details"<<endl;
        cout<<"From.............."<<endl;
        cin>>start;
        cout<<"To................."<<endl;
        cin>>stop;
        cout<<"Enter Distance in km"<<endl;
        cin>>weight;
        cout<<"\n"<<endl;
        edge *newedge = new edge(getnode(start),getnode(stop),weight);
        earray[ecount] = newedge;
        indatedge();

        ecount++;
}
void graph::displayedges(){
    int it;
    for(it=0;it<ecount;it++){
        cout<<"Path "<<it+1<<endl;
        cout<<"Start Location: "<<earray[it]->begin->name<<endl;
        cout<<"stop Location: "<<earray[it]->end->name<<endl;
        cout<<"Distance: "<<earray[it]->weight<<" km"<<endl;
        cout<<"\n";
        cout<<"\n";
    }
}
void graph::sorte(){
    int i;
    pair<int,pair<int,int> > temp;
    for(i=0;i<ccount;i++){
        for(int j=0;j<ecount;j++){
            if(q[i].second.first>q[j].second.first){
                temp = q[i];
                q[i] = q[j];
                q[j] = temp;
            }
        }
    }
    cout<<"SORTED PATHS"<<endl;
    for(i=0;i<ccount;i++){
        cout<<getnode(q[i].second.first)->name<<" - "<<getnode(q[i].second.second)->name<<endl;
    }
}


void graph::createGraph(){
    int start,stop,weight,id,users;
    string name;
    int it,nodes,edges;
    cout<<"Enter no of area cabinets"<<endl;
    cin>>nodes;
    cout<<"\n"<<endl;
    for(it=0;it<nodes;it++){
        cout<<"LOCATION "<<it+1<<endl;
        cout<<"Enter location name:"<<endl;
        cin>>name;
        cout<<"Enter network id"<<endl;
        cin>>id;
        cout<<"Enter no. of users"<<endl;
        cin>>users;
        cout<<"\n"<<endl;
         node *newnode = new node(id,name,users);
        array[count]=newnode;
        indat();
        count++;
    }


    cout<<"Enter no of paths"<<endl;
    cin>>edges;
    cout<<"\n"<<endl;
    for(it=0;it<edges;it++){
        cout<<"path "<<it+1<<endl;
        cout<<"From.............."<<endl;
        cin>>start;
        cout<<"To................."<<endl;
        cin>>stop;
        cout<<"Enter Distance in km"<<endl;
        cin>>weight;
        cout<<"\n"<<endl;
        edge *newedge = new edge(getnode(start),getnode(stop),weight);
        earray[ecount] = newedge;
        indatedge();

        ecount++;
    }
    indat();
}

void graph::kruskal(){
    int mst_wt = 0;
    disjoint ds(count);
    cout<<"MIN DISTANCE NETWORK SPANNING TREE"<<endl;
    for(int it=0;it<ecount;it++){
        int u = p[it].second.first;
        int v = p[it].second.second;

        int set_u = ds.find1(u);
        int set_v = ds.find1(v);

        if(set_u != set_v){
            cout<<getnode(u)->name<<" - "<<getnode(v)->name<<endl;
            mst_wt += p[it].first;
            ds.merge(set_u,set_v);
            q[ccount]=p[it];
            ccount++;


        }


    }
    cout<<"minimum total distance = "<<mst_wt<<" kms"<<endl;

}

void graph::indat(){
    int i;
   MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn=mysql_init(0);
    conn=mysql_real_connect(conn,"192.168.43.217","admin","admin","trial",0,NULL,0);


    int qstate=0;
    stringstream ss;
        int id=array[count]->id;
        int users=array[count]->users;
        string name=array[count]->name;
        ss<<"INSERT INTO test(name,id,users) VALUES('"<<name<<"','"<<id<<"','"<<users<<"')";
        string query=ss.str();
        const char* q=query.c_str();
        qstate=mysql_query(conn,q);

}

void graph::indatedge(){

   MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn=mysql_init(0);
    conn=mysql_real_connect(conn,"192.168.43.217","admin","admin","trial",0,NULL,0);

    int qstate=0;
    stringstream ss;
        int start=earray[ecount]->begin->id;
        int stop=earray[ecount]->end->id;
        int weight = earray[ecount]->weight;
        ss<<"INSERT INTO edges(start,stop,weight) VALUES('"<<start<<"','"<<stop<<"','"<<weight<<"')";
        string query=ss.str();
        const char* q=query.c_str();
        qstate=mysql_query(conn,q);


}

/*void graph::checkbreak(){

    int id1,id2,p,q;
    cout<<"Enter network id 1"<<endl;
    cin>>id1;
    cout<<"Enter network id 2"<<endl;
    cin>>id2;
    p = ds.findl(id1);
    q = ds.findl(id2);
    if(p==q){
        cout<<"Connection exits"<<endl;
    }
    else{
        cout<<"Connection does not exist"<<endl;
    }

}*/

main(){

    cout<<"************************************************************************************************************************"<<endl;
    cout<<"                                                 MIN COST FIBRE CABLE MAP                                               "<<endl;
    cout<<"************************************************************************************************************************"<<endl;
    int choice,go;
    graph g1;
    do{
        cout<<"Enter your choice"<<endl;
        cout<<"\n";
        cout<<"1.Create new network"<<endl;
        cout<<"2.Open existing network"<<endl;
        cout<<"3.Get min cost cable tree"<<endl;
        cout<<"4.Display all cabinet"<<endl;
        cout<<"5.Display all  cabel paths"<<endl;
        cout<<"6.Search cabinet location"<<endl;
        cout<<"7.Add a cabinet"<<endl;
        cout<<"8.Add a cabel path"<<endl;
        cin>>choice;
        cout<<"\n"<<endl;
        switch(choice){
            case 1:
                g1.createGraph();
                g1.createPair();
                break;
            case 2:
                g1.createdat();
                g1.createdated();
                cout<<"Data base Connected........"<<endl;
                cout<<"Network loaded......"<<endl;
                g1.createPair();
                break;
            case 3:
                g1.sorte();
                g1.kruskal();
                break;
            case 4:
                g1.displaynodes();
                break;
            case 5:
                g1.displayedges();
                break;
            case 6:
                g1.searchnode();
                break;

            case 7:
                g1.createnode();
                break;

            case 8:
                g1.createedge();
                break;


        }
        cout<<"\n"<<endl;
        cout<<"press 1 to continue...."<<endl;
        cin>>go;
    }
    while(go==1);

}


