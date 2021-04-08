//Akshat Singh Rathore
//19CS30003


#include <iostream>
#include <fstream>
#include <cstdint>
#include <cmath>
#include <iomanip>
using namespace std;

class NFA
{
int n, m,nf;
uint32_t Q,S,F;
uint32_t **trans;

public:
NFA(){
    n=0;
    m=0;
    Q=0;
    S=0;
    F=0;
    nf=0;
    
}


int getn()
{
    return n;
}

int getm()
{
    return m;
}

uint32_t** gettr()
{
    return trans;
} 

void readNFA(string filename)
{
    ifstream file(filename);
    file>>n;
    file>>m;
    int x=0;
    for(int i=0;i<n;i++)
    {
        double p=pow(2.0,(double)i);
        Q+=(uint32_t)p;
    }

    while(x!=-1)
    {
        file>>x;
        if(x!=-1)
        {
            double p=pow(2.0,(double)x);
            S+=(uint32_t)p;
        }
    }
    x=0;
    while(x!=-1)
    {
        file>>x;
        if(x!=-1)
        {
            double p=pow(2.0,(double)x);
            F+=(uint32_t)p;
            nf++;
        }
    }
    trans = new uint32_t*[n];
    for(int i = 0; i < n; ++i)
        trans[i] = new uint32_t[m];

    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            trans[i][j]=0;
    
    int p=0,a=0,q=0;
    while(p!=-1)
    {
        file>>p;
        file>>a;
        file>>q;
        if(p!=-1)
        {
            double pe=pow(2.0,(double)q);
            trans[p][a]+=(uint32_t)pe;
            
        }
    }
    file.close();
    
}

void printNFA(){
    cout<<"+++ Input NFA"<<endl;
    cout<<"\tNumber of states:"<<n<<endl;
    cout<<"\tInput alphabet: {";
    for(int i=0;i<m;i++){
        cout<<i;
        if(i<m-1)
        {
            cout<<",";
        }
    }
    cout<<"}"<<endl;
    cout<<"\tStart states: {";
    int *a=new int[32];
    int count=0;
    for(int i=1;i<=32;i++)
    {
        
        uint32_t temp=S;
        if ((temp >> (i - 1)) & 1)
           { a[i-1]=1;
            count++;}
        
    }
    for(int i=0;i<32;i++)
    {
        if(a[i]==1)
        {
            cout<<i;
            count--;
            if(count>=1)
                cout<<",";
        }
    }
    cout<<"}"<<endl;

    cout<<"\tFinal states: {";
    int *af=new int[32];int countf=0;
    for(int i=1;i<=32;i++)
    {
        
        uint32_t temp=F;
        if ((temp >> (i - 1)) & 1)
            {af[i-1]=1;
            countf++;}
        
    }
    for(int i=0;i<32;i++)
    {
        if(af[i]==1)
        {cout<<i;countf--;
        if(countf>=1)
        cout<<",";}

    }
    cout<<"}"<<endl;

    cout<<"\tTransition functions"<<endl;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            cout<<"\tDelta("<<i<<","<<j<<") = {";
            if(trans[i][j]!=0)
            {
                int *at=new int[32];
                int countt=0;
                for(int y=1;y<=32;y++)
                {
        
                    uint32_t temp=trans[i][j];
                    if ((temp >> (y - 1)) & 1)
                       { at[y-1]=1;
                        countt++;}
        
                }
                for(int y=0;y<32;y++)
                {
                    if(at[y]==1)
                    {cout<<y;countt--;
                    if(countt>=1)
                    cout<<",";}

                }
                    cout<<"}"<<endl;
            }
            else
            {
                cout<<"}"<<endl;
            }
        }
    }
}

uint32_t getstartstate()
    {
        return S;
    }

int getnf()
{
    return nf;
}
    
uint32_t getfstate()
    {
        return F;
    }

};

class datastate
{
    uint32_t n;
    uint32_t* state;

    public:

    datastate(){
        n=0;
    }

    void setstate(uint32_t k)
    {
        n=k;
        state=new uint32_t[n/32+1];
        for(int i=0;i<n/32+1;i++)
        {
            state[i]=0;
        }
    }
    
    void addstate(uint32_t s)
    {
        
        uint32_t mod=s%32;
        uint32_t q=s/32;
        double p=pow(2.0,(double)mod);
        state[q]+=(uint32_t)p;

    }

    void printstates()
    {
        int count=0;
        for(int i=0;i<=n/32;i++)
        {
            for(int j=1;j<=32;j++)
            {
                if((state[i] >> (j - 1)) & 1)
                {
                    count++;
                }
            }
        }
    
        for(int i=0;i<=n/32;i++)
            {
                for(int j=1;j<=32;j++)
                {
                    if((state[i] >> (j - 1)) & 1)
                    {
                        uint32_t num=32*i+j;
                        count--;
                        if(count!=0)
                            cout<<num-1<<",";
                        else
                            cout<<num-1;
                    }
                }
            }

    }

    uint32_t countstate()
    {
        uint32_t count=0;
        for(int i=0;i<=n/32;i++)
        {
            for(int j=1;j<=32;j++)
            {
                if((state[i] >> (j - 1)) & 1)
                {
                    count++;
                }
            }
        }
        return count;
    }

    uint32_t* getstates()
    {
        return state;
    }
    
    int ispresent(uint32_t s)
    {
        uint32_t mod=s%32;
        uint32_t q=s/32;
        if( (state[q] >> (mod )) & 1)
            return 1;
        else
            return 0;
        
    }

    
    

    


};

class DFA
{
    uint32_t n, m,nf,nv;
    uint32_t S;
    datastate F,Q,V;
    uint32_t **trans;

    public:

    DFA(uint32_t ns,uint32_t na,uint32_t sn,int f,uint32_t **tr,datastate fs,datastate Q2){
        n=ns;
        m=na;
        S=sn;
        nf=0;
        nv=0;
        F=fs;
        Q=Q2;
        trans = new uint32_t*[n];
        for(int i = 0; i < n; ++i)
            trans[i] = new uint32_t[m];
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
                trans[i][j]=tr[i][j];


    }

    DFA(int ns,int na,uint32_t sn,int f,uint32_t **tr,uint32_t fs){
        n=(uint32_t)pow(2.0,(double)ns);
        m=na;
        S=sn;
        nv=0;
        nf=0;
        nf=n-(uint32_t)pow(2.0,(double)(ns-f));
        V.setstate(n);
        F.setstate(n);
        Q.setstate(n);
        for(int i=0;i<n;i++)
            Q.addstate(i);
        
        trans = new uint32_t*[n];
        for(int i = 0; i < n; ++i)
            trans[i] = new uint32_t[m];
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
                trans[i][j]=0;
        
        for(int i=0;i<n;i++)
        {
            int flag=0;
            for(int j=0;j<m;j++)
            {
                
                for(int k=1;k<=ns;k++)
                {
                    if((i >> (k - 1)) & 1)
                    {
                        if(flag==0)
                        {
                            if( ((fs >> (k - 1)) & 1) )
                            {
                                F.addstate(i);
                                flag=1;
                            }
                           
                        }
                        trans[i][j]|=tr[k-1][j];
                    }
                }
            }
            
        }
        
        
        
    }

    int getn()
    {
        return n;
    }

    int getm()
    {
        return m;
    }

    uint32_t** gettr()
    {
        return trans;
    } 


    void printDFA()
    {
        
        cout<<"\tNumber of states:"<<n<<endl;
        cout<<"\tInput alphabet : {";
        for(int i=0;i<m;i++){
            cout<<i;
            if(i<m-1)
            {
                cout<<",";
            }
        }
        cout<<"}"<<endl;
        cout<<"\tStart state : "<<S<<endl;
        if(nf>=64){
            cout<<"\t"<<nf<<" Final States"<<endl;
            cout<<"\tTransition function: Skipped"<<endl;

        }
        else{
            cout<<"\tFinal States : { ";
            F.printstates();
            cout<<" }"<<endl;
            cout<<"\tTransition Function : "<<endl;
            cout<<"\ta/p|"<<setw(3);
            for(int i=0;i<n;i++)
                cout<<i<<setw(3);
            cout<<endl;
            cout<<"\t---+";
            for(int i=0;i<n;i++)
                cout<<"---";
            cout<<endl;
            for(int i=0;i<m;i++)
            {
                cout<<"\t "<<i<<" |";
                for(int j=0;j<n;j++)
                {
                    cout<<setw(3)<<trans[j][i];
                }
                cout<<endl;
            }


        }
        
    }

    datastate findreachable(DFA D)
    {
        DFS(S);
        return V;
    }

    DFA rmunreachable(DFA D,datastate visited)
    {
        uint32_t n2=nv, m2=m,nf2;
        uint32_t S2;
        datastate F2,Q2;
        F2.setstate(n2);
        Q2.setstate(n2);
        uint32_t **trans2;
        uint32_t* lastname=new uint32_t[nv];
        
        for(int i=0;i<nv;i++)
            lastname[i]=0;
        trans2 = new uint32_t*[nv];
        for(int i = 0; i < nv; ++i)
            trans2[i] = new uint32_t[m];
        for(int i=0;i<nv;i++)
            for(int j=0;j<m;j++)
                trans2[i][j]=0;
        uint32_t counter=0;

        for(uint32_t i=0;i<n;i++)    //renaming Q
        {
            if(V.ispresent(i))
            {
               
                Q2.addstate(counter);
                lastname[counter]=i;
                counter++;
            }
        }
       
        for(uint32_t i=0;i<counter;i++)  //renaming transition states
        {
            for(int j=0;j<m;j++)
            {
                trans2[i][j]=trans[lastname[i]][j];
                for(int k=0;j<counter;k++)
                {
                    if(lastname[k]==trans2[i][j])
                    {
                        trans2[i][j]=k;
                        break;   
                    }
                }
            }
        }
       
        for(uint32_t i=0;i<counter;i++)  //renaming S and F
        {
            
            if(lastname[i]==S)
                S2=i;
           
            if(F.ispresent(lastname[i])){
                F2.addstate(i);
                nf2++;
            }
        }
       

        return DFA(n2,m2,S2,nf2,trans2,F2,Q2);

    }

    void DFS(uint32_t state)
    {
        V.addstate(state);
        nv++;
        for(int i=0;i<m;i++)
        {
            uint32_t nextstate=trans[state][i];
            if(!V.ispresent(nextstate))
            {
                DFS(nextstate);
            }
        }
    }

    uint32_t** findequiv(DFA D)
    {
        uint32_t** marked;
        marked = new uint32_t*[n];
        for(int i = 0; i < n; ++i)
            marked[i] = new uint32_t[n];

        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                marked[i][j]=0;
        int flag=0,check=1;
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
                {
                    if((F.ispresent(i) && !F.ispresent(j)) || (!F.ispresent(i) && F.ispresent(j)))
                    {
                        marked[i][j]=1;
                    }
                }
        }
        while(check)
        {
            flag=0;
            for(int i=0;i<n;i++)
            {
                for(int j=0;j<n;j++)
                {
                    for(int k=0;k<m;k++)
                    {
                        
                        if( !marked[i][j] && marked[trans[i][k]][trans[j][k]])
                        {
                            marked[i][j]=1;
                            flag=1;
                            
                        }
                    }
                }
            }
            if(flag==0)
                check=0;
        }
        for(int i=0;i<n;i++)
            marked[i][i]=1;
        return marked;

    }

    DFA collapse(DFA D,uint32_t** table,uint32_t nv1)
    {
        uint32_t* group=new uint32_t[nv1];
        for(int i=0;i<nv1;i++)
            group[i]=i;
       
        uint32_t counter=0;
        for(int i=0;i<nv1;i++)
        {
            int flag=0;
            for(int j=0;j<nv1;j++)
            { 
                if(table[i][j]==0 && j>i){
                    table[j][i]=1;
                    group[j]=group[i];
                    counter++;
                    flag=1;
                }
            }
            if(flag==0)
                {
                    counter++;
                }
        }
        counter=0;
        datastate *groups= new datastate[nv1];
        datastate *groups1= new datastate[nv1];
        for(int i=0;i<nv1;i++){
        groups[i].setstate(nv1);
        groups1[i].setstate(nv1);
        }
        int *as=new int[nv1];
        for(int i=0;i<nv1;i++)
        as[i]=0;
        int flag1=0;
        int store=0;
        while(flag1<nv1)
        {
           
            for(int i=0;i<nv1;i++)
            {
                if(group[i]==counter)
                {
                    groups[counter].addstate(i);
                    as[counter]=1;
                    flag1+=1;
                }
            }
            counter++;
        }
        
        int countstate=0;
        for(int i=0;i<nv1;i++)
        {
            if(as[i]!=0)
            {
                countstate++;
            }
        }
        for(int i=0;i<counter;i++)
        {
            if(groups[i].countstate()!=0)
            {
                groups1[store++]=groups[i];
            }
        }

        cout<<"+++ Equivalent states"<<endl;
        for(int i=0;i<countstate;i++)
        {
            cout<<"\tGroup "<<i<<": {";
            groups1[i].printstates();
            cout<<"}"<<endl;

        }

        uint32_t numstate=countstate;
        uint32_t ma=m;
        uint32_t *newname= new uint32_t[nv1];
        for(int i=0;i<nv1;i++)
        {
            for(int j=0;j<numstate;j++)
            {
                if(groups1[j].ispresent(i))
                    newname[i]=j;
            }
        }
        uint32_t ss=newname[S];
        datastate ff;
        uint32_t nf2=0;
        ff.setstate(numstate);
        for(uint32_t i=0;i<nv1;i++)
        {
            if(F.ispresent(i))
            {
                uint32_t h=newname[i];
                if(!ff.ispresent(h))
                    ff.addstate(h);
                    nf2++;
            }
        }

        uint32_t **trans2;
        trans2 = new uint32_t*[numstate];
        for(int i = 0; i < numstate; ++i)
            trans2[i] = new uint32_t[m];
        for(int i=0;i<numstate;i++)
        {
            for(int j=0;j<m;j++)
            {
                for(int k=0;k<nv1;k++)
                {
                    if(newname[k]==i)
                    {
                        trans2[i][j]=newname[trans[k][j]];
                        break;
                    }
                }
            }
        }
        datastate Q2;
        Q2.setstate(numstate);
        for(int i=0;i<numstate;i++)
            Q2.addstate(i);
        
        return DFA(numstate,m,ss,nf2,trans2,ff,Q2);




    }

};






int main()
{
   NFA N;
   cout<<"Filename (without any extension) : ";
   string filename;
   cin>>filename;
   cout<<"[NOTE: Please make sure that the file is in txt format and is in the same parent folder as the source code]"<<endl;
   filename+=".txt";


   N.readNFA(filename);
   cout<<endl;
   N.printNFA();

   DFA D(N.getn(),N.getm(),N.getstartstate(),N.getnf(),N.gettr(),N.getfstate());
    cout<<endl;
   cout<<"+++ Converted DFA"<<endl;
   D.printDFA();

   datastate V= D.findreachable(D);
cout<<endl;
   cout<<"+++ Reachable states : { ";
   V.printstates();
   cout<<" }"<<endl;
   DFA d2=D.rmunreachable(D,V);
cout<<endl;
   cout<<"+++ Reduced DFA after removing unreachable states"<<endl;
   d2.printDFA();
   uint32_t n=d2.getn();
   uint32_t** k=new uint32_t*[n];
   for(int i = 0; i < n; ++i)
   k[i] = new uint32_t[n];
   k=d2.findequiv(d2);
    
    cout<<endl;
   DFA d3= d2.collapse(d2,k,n);
   cout<<endl;
   cout<<"+++ Reduced DFA after collapsing equivalent states"<<endl;
   d3.printDFA();
    
}

