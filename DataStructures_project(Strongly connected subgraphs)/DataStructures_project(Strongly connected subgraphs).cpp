/*Zorbey Gokyýldýz 230702040 
  Strongly connected subgraph program*/

#include <list>
#include <queue>
#include <iostream>
using namespace std;

/*Node of the graph*/
template<class T>class node {
public:
	node<T> *next[100];
	T data;
	T data2;

	node() {
		this->next[100]=0;
		this->data=0;
	    this->data2=0;
	}
};


template<class T> class graph:public node<T> {
public:

        void set_graphmatrix(T data,T data1,T data2,int counter);
        bool find_BFS(node<T> *start);
	void visualgraph();
	void order();
	void compressvector();
	void print_SSG();
	void find_SSG(node<T> *check);
	vector<node<T> *> myvector;
	vector<node<T> *> newvector;
        vector<node<T> *> tmpvector;
        vector<node<T> *> deneme;

	
        node<T> *k[100];
        int count;
	int nodecounter;
	int global_counter;
	int m;
        int clock;
	int size;

	graph() {
	 this->count=0;
	 this->clock=0;
	 this->nodecounter=0;
	 this->global_counter=0;
	 this->m=0;
	 this->size=0;
	 node<T> *A=new node<T>;
         node<T> *B=new node<T>;
         node<T> *C=new node<T>;
         node<T> *D=new node<T>;
         node<T> *E=new node<T>;
         node<T> *F=new node<T>;
         node<T> *G=new node<T>;
         node<T> *H=new node<T>;
         node<T> *I=new node<T>;
         node<T> *J=new node<T>;
         node<T> *K=new node<T>;
	 node<T> *L=new node<T>;
         node<T> *M=new node<T>;
         node<T> *N=new node<T>;
         node<T> *O=new node<T>;
         k[0]=A; k[1]=B; k[2]=C; k[3]=D; k[4]=E; k[5]=F; k[6]=G; k[7]=H; 
         k[8]=I; k[9]=J; k[10]=K; k[11]=L; k[12]=M; k[13]=N; k[14]=O;
	}
};

/*This function compresses the given vector found by BFS search, 
so we can get the graph size*/
template<class T> void graph<T>::compressvector() {

int z=0;
int m=0;
int flag=0;

     newvector.push_back(myvector[0]);
     while(myvector[z])
	 {
                 m=0;
		 while(newvector[m])
		 {
			 if(myvector[z]==newvector[m])
			 {
				 flag=1;
			 }
			 m++;
		 }
		 if(flag==0)
		 {
		   newvector.push_back(myvector[z]);
		 }
		 flag=0;
		 z++;
         }
    //m=0;
    //while(newvector[m])
    //{
    //	printf("%c ", newvector[m]->data);
    //	m++;
    //}
}
/*This function prints the subgraphs in a given graph which is represented by a graph sequence*/
template<class T> void graph<T>::print_SSG() {

	
        list<char> deneme;
	list<char>::iterator iterator;
        list<char>::iterator iterator2;
        list<char>::iterator iterator3;
        int point=1;
        int point2=0;
	int flag;
printf("In the given graph sequence: ");

while(tmpvector[point2])
{
     printf("%c  ", tmpvector[point2]->data);
     point2++;
}
printf("\n\n");


deneme.push_back(tmpvector[0]->data);

    
    while(tmpvector[point])
    {
      flag=0;
      iterator=deneme.begin();
      while(iterator!=deneme.end())
      { 
        if(tmpvector[point]->data==*iterator)
        {
         flag=1;

            iterator2=iterator;
            printf("This is a strongly connected subgraph: ");
            while(iterator2!=deneme.end())
            {
              printf("%c ", *iterator2); iterator2++;
            }
             printf("\n\n");
          
              deneme.erase(iterator);          
              deneme.push_back(tmpvector[point]->data);
         }
       iterator++;
      }
      if(flag==0)
      {
       deneme.push_back(tmpvector[point]->data);
       }
      point++;
    }
}
/*This function forms the graph sequence by using a unique DFT algorithm*/
template<class T> void graph<T>::find_SSG(node<T> *check) {
	
	int tut=0;
	int m=0;
	int i;
	int k=0;
	node<T> *temp;
	int temp2=1;
	temp=check;
	
        temp->data2='V';
	
	if(check==newvector[0] && clock==0)
	{
	tmpvector.push_back(temp);
	clock=1;
	}

	for(i=0; i<=newvector.size(); i++)
	{
            if(temp->next[i])
	    {
		 if(temp->next[i]->data2)
		 { 
                         temp->next[i]->data2='H';
			 tmpvector.push_back(temp->next[i]);
		 }
	    }
	}
	
	
	for(tut=0; tut<=newvector.size(); tut++)
	{
		if(temp->next[tut] && !temp->next[tut]->data2)
		{
		temp->next[tut]->data2='V';
		tmpvector.push_back(temp->next[tut]);
		find_SSG(temp->next[tut]);
		}
		i++;
	}
}


template<class T> void graph<T>::visualgraph() {

int m=newvector.size();
int i=0;
	
   printf(" ---------------\n");
   
   while(m>0)
   {i=0;
	printf(" %c    ",newvector[m-1]->data);
	
	while(newvector[m-1]->next[i])
	{
		if(i!=0)
		{
    printf("    |\n");
		}
	printf("     --> %c \n",newvector[m-1]->next[i]->data);
	i++;
	}
	  printf("    \n");
	m--;
   }
}

/*This function finds all the nodes resperented in the graph structure*/
template<class T> bool graph<T>::find_BFS(node<T> *start) {

	
	int i=0;
	int j=0;
	int z=0;
	int help;

node<T> *tmp;
node<T> *temp;
queue<node<T>*> myqueue;

if(start==k[0])
{
	myvector.push_back(start);
}

    while(start->next[i])
	{
		tmp=start;
	    start=start->next[i];
		myqueue.push(start);
		myvector.push_back(start);
	
	start=tmp;
	i++;
	help=0;
	}
		
if(myqueue.empty())
{
  
	graph<T>::compressvector();
	graph<T>::visualgraph();
        graph<T>::find_SSG(newvector[0]);
	return true;
}
//printf("%c ", myqueue.front()->data);
temp=myqueue.front();
myqueue.pop();
nodecounter++;
find_BFS(k[nodecounter]);
}


/*Form the graph*/
template<class T> void graph<T>::set_graphmatrix(T data, T data1, T data2, int counter) {

	const char L[15]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O'};
	int i,j,m;

	
   if(count!=1)
   {
	   for(i=0; i<15; i++)
	   {
		k[i]->data=L[i];
	   }
       count=1;
   }

    if(data2=='X')
	{
		for(i=0; i<15; i++)
		{
			if(data==L[i])
			{
				m=0;
					while(k[i]->next[m])
					{
						m++;
					}
				for(j=0; j<15; j++)
				{
					if(data1==L[j])
					{
						k[i]->next[m]=k[j];
					}
				}
			
			}
		}
	}

	global_counter++;

	if(global_counter==counter)
	{
		//printf("%c ", k[4]->next[0]->data);
		graph<T>::find_BFS(k[0]);
	}
}



int main()
{
  graph<char> mygraph;

  char check;
  char check1;
  char check2;
  char str;
  int counter=0;
  FILE *pFile;
  FILE *deneme;
  
  if((pFile=fopen("proje.txt","r"))==NULL)
  { 
	  printf("error");
  }
  else
  {      
          deneme=fopen("proje.txt","r");
          fscanf(deneme, "%c %c %c", &check,&check1,&check2);
          counter++; 
          while(!feof(deneme))
          {
                  str=fgetc(deneme);
                  if(str=='\n')
                  {
          fscanf(deneme, "%c %c %c", &check,&check1,&check2);
          counter++;
                  }
           }
            fclose(deneme);

          fscanf(pFile, "%c %c %c", &check,&check1,&check2);
	  mygraph.set_graphmatrix(check,check1,check2,counter);

	  while(!feof(pFile))
	  {
		  str=fgetc(pFile);
		  if(str=='\n')
		  {
          fscanf(pFile, "%c %c %c", &check,&check1,&check2);
          mygraph.set_graphmatrix(check,check1,check2,counter);
		  }
	  }
 }
 mygraph.print_SSG();
 fclose(pFile);
 
  return 0;
}




