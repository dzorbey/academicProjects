#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <stack>
#include <time.h>
using namespace std;

int globalhold[4];
int zorbey=0;
int globalinitial1,globalinitial2;
int myglobalinitial1,myglobalinitial2;


template <class T> class Node {
public:
  Node<T> *left;
  Node<T> *right;
  Node<T> *back;
  Node<T> *forward;


  Node<T> *parent;
  T x;
  T y;
  T data;

  Node() {
    this->parent=NULL;
	this->left=NULL;
	this->right=NULL;
	this->back=NULL;
	this->forward=NULL;
  }

};


template <class T> class SearchTree:public Node<T> {
public:

   stack<Node<T>*> mystack;
   stack<Node<T>*> mystack2;
   stack<int> mystack3;

   Node<T> *root;


   SearchTree() {
	   this->root=NULL;
   }
  

void insertTree(T x,T y,T data) {

       root=insert(root,x,y,data);
}





Node<T> *insert(Node<T> *start,T x,T y,T data) {



	if(start==NULL)
	{
		start=new Node<T>;
		start->data=data;
                start->x=x;
		start->y=y;
	}
	else if(x==(start->x) && y>start->y)
	{
		start->right=insert(start->right,x,y,data);
		insert(start->right,x,y,data)->parent=start;
	}
	else if(x==(start->x) && y<start->y)
	{
		start->left=insert(start->left,x,y,data);
                insert(start->left,x,y,data)->parent=start;
	}
        else if(y==(start->y) && x>start->x)
	{
		start->back=insert(start->back,x,y,data);
                insert(start->back,x,y,data)->parent=start;
	}
	else if (y==(start->y) && x<start->x)
	{
		start->forward=insert(start->forward,x,y,data);
                insert(start->forward,x,y,data)->parent=start;
	}
	else if(x>start->x && y>start->y)
	{
		start->right->back=insert(start->right->back,x,y,data);
              
  insert(start->right->back,x,y,data)->parent=start->right;
	}
	else if(x<start->x && y>start->y)
	{
		start->right->forward=insert(start->right->forward,x,y,data);
              
  insert(start->right->forward,x,y,data)->parent=start->right;
	}
	else if(x>start->x && y<start->y)
	{
		start->left->back=insert(start->left->back,x,y,data);
                insert(start->left->back,x,y,data)->parent=start->left;
	}
	else if(x<start->x && y<start->y)
	{
		start->left->forward=insert(start->left->forward,x,y,data);
              
  insert(start->left->forward,x,y,data)->parent=start->left;
	}
	else{}

        return start;
}



void DFS_Search(Node<T> *start) {


mystack.push(start);

if(start->data==1)
{
mystack2.push(mystack.top());
}

  if(start->left)
  {
	  DFS_Search(start->left);
  }
  if(start->right)
  {
	  DFS_Search(start->right);
  }
  if(start->back)
  {
	  DFS_Search(start->back);
  }
  if(start->forward)
  {
	  DFS_Search(start->forward);
  }
}



Node<int> *result;





void goodAgentsdecide() {


result=mystack2.top();


while(result)
{
 if(result->parent && result->parent->right==result)
 {
  //printf("-right");
  mystack3.push(4);
 }
 else if(result->parent && result->parent->left==result)
 {
  //printf("-left");
  mystack3.push(3);
 }
 else if(result->parent && result->parent->forward==result)
 {
   //printf("-forward");
   mystack3.push(2);
 }
 else if(result->parent && result->parent->back==result)
 {
   //printf("-back");
   mystack3.push(1);
 }
 else {}

result=result->parent;
}

globalhold[zorbey++]=mystack3.top();
mystack3.pop();
}



void emptystacks() {
       
        while(!mystack.empty())
        {
         mystack.pop();
        }
        while(!mystack2.empty())
        {
         mystack2.pop();
        }
        while(!mystack3.empty())
        {
         mystack3.pop();
        }
}


void deleteTree(Node<T> *start ) {
                                                                      
  if(start->left)
  {
          deleteTree(start->left);
          delete start->left;
  }
  if(start->right)
  {
          deleteTree(start->right);
          delete start->right;
  }
  if(start->back)
  {
          deleteTree(start->back);
          delete start->back;
  }
  if(start->forward)
  {
          deleteTree(start->forward);
          delete start->forward;
  }
}
};



SearchTree<int> MysearchTree1;
SearchTree<int> MysearchTree2;
SearchTree<int> MysearchTree3;
SearchTree<int> MysearchTree4;

int initial1,initial2;
int good1_initial1,good1_initial2;
int good2_initial1,good2_initial2;
int good3_initial1,good3_initial2;
int good4_initial1,good4_initial2;

void randommove(int gameboard[8][8],int x,int y);
void tree1_update(int contain1,int contain2, int gameboard[8][8]);
void tree2_update(int contain1,int contain2, int gameboard[8][8]);
void tree3_update(int contain1,int contain2, int gameboard[8][8]);
void tree4_update(int contain1,int contain2, int gameboard[8][8]);
void goodAgent1Move(int myglobalhold,int gameboard[8][8],int x,int y);
void BadAgent1Move(int myglobalhold,int gameboard[8][8],int x,int y);
void game_print(int gameboard[8][8]);
void mysleep();




void tree1_update(int contain1,int contain2, int gameboard[8][8]) {

	int i,j;
	for(i=contain1; i>=0; i--)
	{
		for(j=contain2; j<8; j++)
		{
		MysearchTree1.insertTree(i,j,gameboard[i][j]);
		}
	}
	for(i=contain1; i<8; i++)
	{
		for(j=contain2; j<8; j++)
		{
		MysearchTree1.insertTree(i,j,gameboard[i][j]);
		}
	}
	for(i=contain1; i>=0; i--)
	{
		for(j=contain2; j>=0; j--)
		{
		MysearchTree1.insertTree(i,j,gameboard[i][j]);
		}
	}
	for(i=contain1; i<8; i++)
	{
		for(j=contain2; j>=0; j--)
		{
		MysearchTree1.insertTree(i,j,gameboard[i][j]);
		}
	}
}





void tree2_update(int contain1,int contain2, int gameboard[8][8]) {

	int i,j;
	for(i=contain1; i>=0; i--)
	{
		for(j=contain2; j<8; j++)
		{
		MysearchTree2.insertTree(i,j,gameboard[i][j]);
		}
	}
	for(i=contain1; i<8; i++)
	{
		for(j=contain2; j<8; j++)
		{
		MysearchTree2.insertTree(i,j,gameboard[i][j]);
		}
	}
	for(i=contain1; i>=0; i--)
	{
		for(j=contain2; j>=0; j--)
		{
		MysearchTree2.insertTree(i,j,gameboard[i][j]);
		}
	}
	for(i=contain1; i<8; i++)
	{
		for(j=contain2; j>=0; j--)
		{
		MysearchTree2.insertTree(i,j,gameboard[i][j]);
		}
	}
}


void tree3_update(int contain1,int contain2, int gameboard[8][8]) {

	int i,j;
	for(i=contain1; i>=0; i--)
	{
		for(j=contain2; j<8; j++)
		{
		MysearchTree3.insertTree(i,j,gameboard[i][j]);
		}
	}
	for(i=contain1; i<8; i++)
	{
		for(j=contain2; j<8; j++)
		{
		MysearchTree3.insertTree(i,j,gameboard[i][j]);
		}
	}
	for(i=contain1; i>=0; i--)
	{
		for(j=contain2; j>=0; j--)
		{
		MysearchTree3.insertTree(i,j,gameboard[i][j]);
		}
	}
	for(i=contain1; i<8; i++)
	{
		for(j=contain2; j>=0; j--)
		{
		MysearchTree3.insertTree(i,j,gameboard[i][j]);
		}
	}
}

void tree4_update(int contain1,int contain2, int gameboard[8][8]) {

	int i,j;
	for(i=contain1; i>=0; i--)
	{
		for(j=contain2; j<8; j++)
		{
		MysearchTree4.insertTree(i,j,gameboard[i][j]);
		}
	}
	for(i=contain1; i<8; i++)
	{
		for(j=contain2; j<8; j++)
		{
		MysearchTree4.insertTree(i,j,gameboard[i][j]);
		}
	}
	for(i=contain1; i>=0; i--)
	{
		for(j=contain2; j>=0; j--)
		{
		MysearchTree4.insertTree(i,j,gameboard[i][j]);
		}
	}
	for(i=contain1; i<8; i++)
	{
		for(j=contain2; j>=0; j--)
		{
		MysearchTree4.insertTree(i,j,gameboard[i][j]);
		}
	}
}



void goodAgent1Move(int myglobalhold,int gameboard[8][8],int x,int y) {


        if(myglobalhold==4 && gameboard[x][(y)+1]==0)
        {
                globalinitial1=x;
                globalinitial2=(y)+1;}
        else if(myglobalhold==3 && gameboard[x][(y)-1]==0)
        {
                globalinitial1=x;
                globalinitial2=(y)-1;}
        else if(myglobalhold==2 && gameboard[(x)-1][y]==0)
        {
                globalinitial1=(x)-1;
                globalinitial2=y;}
        else if(myglobalhold==1 && gameboard[(x)+1][y]==0)
        {
                globalinitial1=(x)+1;
                globalinitial2=y;}
        else{
		
		globalinitial1=x;
		globalinitial2=y;
		}
}

void BadAgent1Move(int myglobalhold,int gameboard[8][8],int x,int y) {


	if(myglobalhold==2  && gameboard[x][(y)+1]==0)
        {
                myglobalinitial1=x;
                myglobalinitial2=(y)+1;}
        else if(myglobalhold==4 && gameboard[x][(y)-1]==0)
        {
                myglobalinitial1=x;
                myglobalinitial2=(y)-1;}
        else if(myglobalhold==1 && gameboard[(x)-1][y]==0)
        {
                myglobalinitial1=(x)-1;
                myglobalinitial2=y;}
        else if(myglobalhold==3 && gameboard[(x)+1][y]==0)
        {
                myglobalinitial1=(x)+1;
                myglobalinitial2=y;}
        else{
		
		myglobalinitial1=x;
		myglobalinitial2=y;
		}
}



void game_print(int gameboard[8][8]) {

	int i,j;
	for(i=0; i<8; i++)
	{
		for(j=0; j<8; j++)
		{
			if(gameboard[i][j]==1)
				printf("O");
		
			else if(gameboard[i][j]==2)
				printf("X");
		
			else 
				printf("*");
		}
		printf("\n");
	}
}



void mysleep(int k) {
int i;
for(i=0; i<100000000; i++)
{}
}




void randommove(int gameboard[8][8],int x,int y) {

int k;

int m=0;
while(1) {
    k=rand()%4;
m++;

    if(k==0 && gameboard[x][(y)-1]==0)
	{
		globalinitial1=x;
		globalinitial2=(y)-1;
		break;
	} 
	else
	if(k==1 && gameboard[(x)+1][y]==0)
	{
		globalinitial1=(x)+1;
		globalinitial2=y;
		break;
	}
	else
	if(k==2 &&  gameboard[(x)-1][y]==0)
	{
		globalinitial1=(x)-1;
		globalinitial2=y;
		break;
	}
	else 
        if(k==3 && gameboard[x][(y)+1]==0)
	{
		globalinitial1=x;
		globalinitial2=(y)+1;
		break;
	}
	else{
		
	}
	if(m==5000) {
		globalinitial1=x;
		globalinitial2=y;
		break;
	}
	}
}




int main()
{

    srand((unsigned)time(NULL));

	int i=0,j=0;
	int k=0;
	int l=0;
        int globcount;
	int flag=0;
	int former1=0;
	int former2=7;
	int former11=6,former12=1;
        int former21=6,former22=0,former31=7;
        int former32=0,former41=7,former42=1;


	initial1=0; initial2=7;
        good1_initial1=6;  good1_initial2=1;
        good2_initial1=6;  good2_initial2=0;
        good3_initial1=7;  good3_initial2=0;
        good4_initial1=7;  good4_initial2=1;
        int gameboard[8][8];

        int choose;
        printf("Welcome to the game!\nFor random agent select 1!\n");
        printf("For predefined path select 2!(Remember to fill in the input.txt file first).\n");
	printf("The file should be written into as..\n");
        printf("1\n2\n3\n4\n2\n1\n3\n2\n.\n.\n.\n\n\n");
        scanf("%d" , &choose); 


if(choose==1)
{
	while(1) { 
   

for(i=0; i<8; i++)
	{
		for(j=0; j<8; j++)
		{
			gameboard[i][j]=0;
		}
	}

globcount=0;

gameboard[former11][former12]==2;
gameboard[former21][former22]==2;
gameboard[former31][former32]==2;
gameboard[former41][former42]==2;
gameboard[initial1][initial2]==1;





if(flag==1){
       former1=initial1;
       former2=initial2;

           randommove(gameboard,initial1,initial2);
           initial1=globalinitial1;
	   initial2=globalinitial2;
           gameboard[initial1][initial2]=1;
           gameboard[former1][former2]=0;
}

  
       if(gameboard[good1_initial1][good1_initial2]==0)
	   {
			   gameboard[good1_initial1][good1_initial2]=2;
		      
              if(gameboard[former11][former12]!=gameboard[good1_initial1][good1_initial2])
			   {
			       gameboard[former11][former12]==0;
			   }
		   }
	   else { 
		     randommove(gameboard,good1_initial1,good1_initial2);
	             good1_initial1=globalinitial1;
		     good1_initial2=globalinitial2;
	  	     gameboard[good1_initial1][good1_initial2]=2;

   if(gameboard[former11][former12]!=gameboard[good1_initial1][good1_initial2])
                           {
                               gameboard[former11][former12]==0;
                           }

   }
       
	   
	   
	     if(gameboard[good2_initial1][good2_initial2]==0)
		 {
				 gameboard[good2_initial1][good2_initial2]=2;
                
                          if(gameboard[former21][former22]!=gameboard[good2_initial1][good2_initial2])
	        	 {
				 gameboard[former21][former22]==0;
			 }
			 }
		
	    else { 
			
		 randommove(gameboard,good2_initial1,good2_initial2);
	         good2_initial1=globalinitial1;
    	         good2_initial2=globalinitial2;
                 gameboard[good2_initial1][good2_initial2]=2;

   if(gameboard[former21][former22]!=gameboard[good2_initial1][good2_initial2])
                         {
                                 gameboard[former21][former22]==0;
                         }




		}


       if(gameboard[good3_initial1][good3_initial2]==0)
	   {
				 gameboard[good3_initial1][good3_initial2]=2;
                
                        if(gameboard[former31][former32]!=gameboard[good3_initial1][good3_initial2])
			{
				 gameboard[former31][former32]==0;
	  	        }
		  }
	   else{
		   
 		   randommove(gameboard,good3_initial1,good3_initial2);
	           good3_initial1=globalinitial1;
		   good3_initial2=globalinitial2;
                   gameboard[good3_initial1][good3_initial2]=2;


if(gameboard[former31][former32]!=gameboard[good3_initial1][good3_initial2])
                        {
                                 gameboard[former31][former32]==0;
                        }






             }


	   if(gameboard[good4_initial1][good4_initial2]==0)
	   {
			   gameboard[good4_initial1][good4_initial2]=2;
	 if(gameboard[former41][former42]!=gameboard[good4_initial1][good4_initial2])
         {
			  gameboard[former41][former42]==0;
	 }
		   }
	   	   else { 		
      	  	     randommove(gameboard,good4_initial1,good4_initial2);
	             good4_initial1=globalinitial1;
	             good4_initial2=globalinitial2;
                     gameboard[good4_initial1][good4_initial2]=2;

 if(gameboard[former41][former42]!=gameboard[good4_initial1][good4_initial2])
     {
                         gameboard[former41][former42]==0;
     }
	   }


	if(flag==0)
	{
                gameboard[0][7]=1;
	        gameboard[6][1]=2;
		gameboard[6][0]=2;
		gameboard[7][0]=2;
		gameboard[7][1]=2;

	    flag=1;
	}



        game_print(gameboard);

        printf("\n\n");
//	   mysleep(3);

		
		tree1_update(good1_initial1,good1_initial2,gameboard);
		MysearchTree1.DFS_Search(MysearchTree1.root);
                MysearchTree1.goodAgentsdecide(); 
	        goodAgent1Move(globalhold[0],gameboard,good1_initial1,good1_initial2);
		former11=good1_initial1;
		former12=good1_initial2;
                MysearchTree1.emptystacks();
                MysearchTree1.deleteTree(MysearchTree1.root);
		MysearchTree1.root=NULL;
                good1_initial1=globalinitial1;
		good1_initial2=globalinitial2;
   

		tree2_update(good2_initial1,good2_initial2,gameboard);
		MysearchTree2.DFS_Search(MysearchTree2.root);
                MysearchTree2.goodAgentsdecide();
                goodAgent1Move(globalhold[1],gameboard,good2_initial1,good2_initial2);
		MysearchTree2.emptystacks();
	        former21=good2_initial1;
		former22=good2_initial2;
		MysearchTree2.deleteTree(MysearchTree2.root);
		MysearchTree2.root=NULL;
                good2_initial1=globalinitial1;
		good2_initial2=globalinitial2;
      

		tree3_update(good3_initial1,good3_initial2,gameboard);
		MysearchTree3.DFS_Search(MysearchTree3.root);
                MysearchTree3.goodAgentsdecide();
                goodAgent1Move(globalhold[2],gameboard,good3_initial1,good3_initial2);
		former31=good3_initial1;
		former32=good3_initial2;
		MysearchTree3.emptystacks();
		MysearchTree3.deleteTree(MysearchTree3.root);
		MysearchTree3.root=NULL;
                good3_initial1=globalinitial1;
		good3_initial2=globalinitial2;


                tree4_update(good4_initial1,good4_initial2,gameboard);
		MysearchTree4.DFS_Search(MysearchTree4.root);
                MysearchTree4.goodAgentsdecide();
                goodAgent1Move(globalhold[3],gameboard,good4_initial1,good4_initial2);
		former41=good4_initial1;
		former42=good4_initial2;
		MysearchTree4.emptystacks();
		MysearchTree4.deleteTree(MysearchTree4.root);
		MysearchTree4.root=NULL;
                good4_initial1=globalinitial1;
		good4_initial2=globalinitial2;



        zorbey=0;
     


if(gameboard[initial1+1][initial2]!=0 &&
 gameboard[initial1-1][initial2]!=0 
   && gameboard[initial1][initial2-1]!=0 &&
 gameboard[initial1][initial2+1]!=0)
		 {
	         printf("------------GAME OVER--------------");
			 break;
		 }
}
}



if(choose==2)
 {
	 FILE *fileptr;

	 fileptr=fopen("input.txt", "r");
         int hold;

	 while(!feof(fileptr))
	 {
		 for(i=0; i<8; i++)
		 {
		   for(j=0; j<8; j++)
		   {
		    	gameboard[i][j]=0;
		   }
		 }



gameboard[former11][former12]==2;
gameboard[former21][former22]==2;
gameboard[former31][former32]==2;
gameboard[former41][former42]==2;
gameboard[initial1][initial2]==1;



if(flag==1){
           former1=initial1;
	   former2=initial2;

        fscanf(fileptr, "%d", &hold);
	BadAgent1Move(hold,gameboard,initial1,initial2);
	initial1=myglobalinitial1;
	initial2=myglobalinitial2;
	while(former1==initial1 && former2==initial2)
	{
		fscanf(fileptr, "%d", &hold);
		BadAgent1Move(hold,gameboard,initial1,initial2);
                initial1=myglobalinitial1;
	        initial2=myglobalinitial2;
	}

	  
		   gameboard[initial1][initial2]=1;
		   gameboard[former1][former2]=0;
}



  
       if(gameboard[good1_initial1][good1_initial2]==0)
	   {
		      gameboard[good1_initial1][good1_initial2]=2;
		      if(gameboard[former11][former12]!=gameboard[good1_initial1][good1_initial2])
			   {
			       gameboard[former11][former12]==0;
			   }
		   }
	   else { 
		 randommove(gameboard,good1_initial1,good1_initial2);
	         good1_initial1=globalinitial1;
		 good1_initial2=globalinitial2;
	         gameboard[good1_initial1][good1_initial2]=2;
             if(gameboard[former11][former12]!=gameboard[good1_initial1][good1_initial2])
                           {
                               gameboard[former11][former12]==0;
                           }
               }
       
	   
	   
	     if(gameboard[good2_initial1][good2_initial2]==0)
		 {
		      gameboard[good2_initial1][good2_initial2]=2;
                      if(gameboard[former21][former22]!=gameboard[good2_initial1][good2_initial2])
				 {
					 gameboard[former21][former22]==0;
				 }
			 }
		
	    else { 
	         randommove(gameboard,good2_initial1,good2_initial2);
	         good2_initial1=globalinitial1;
    	         good2_initial2=globalinitial2;
                 gameboard[good2_initial1][good2_initial2]=2;
	
      if(gameboard[former21][former22]!=gameboard[good2_initial1][good2_initial2])
                                 {
                                         gameboard[former21][former22]==0;
                                 }

	}


       if(gameboard[good3_initial1][good3_initial2]==0)
	  {
                gameboard[good3_initial1][good3_initial2]=2;
                if(gameboard[former31][former32]!=gameboard[good3_initial1][good3_initial2])
				 {
					 gameboard[former31][former32]==0;
				 }
		  }
	   else{
	       randommove(gameboard,good3_initial1,good3_initial2);
	       good3_initial1=globalinitial1;
	       good3_initial2=globalinitial2;
               gameboard[good3_initial1][good3_initial2]=2;

 if(gameboard[former31][former32]!=gameboard[good3_initial1][good3_initial2])
                                 {
                                         gameboard[former31][former32]==0;
                                 }
             }


	   if(gameboard[good4_initial1][good4_initial2]==0)
	   {
	        gameboard[good4_initial1][good4_initial2]=2;
		if(gameboard[former41][former42]!=gameboard[good4_initial1][good4_initial2])
			   {
			       gameboard[former41][former42]==0;
			   }
		   }
	   	   else { 		
		     randommove(gameboard,good4_initial1,good4_initial2);
	             good4_initial1=globalinitial1;
	             good4_initial2=globalinitial2;
                     gameboard[good4_initial1][good4_initial2]=2;

  if(gameboard[former41][former42]!=gameboard[good4_initial1][good4_initial2])
                           {
                               gameboard[former41][former42]==0;
                           }

                }


        if(flag==0)
	{
                gameboard[0][7]=1;
	        gameboard[6][1]=2;
		gameboard[6][0]=2;
		gameboard[7][0]=2;
		gameboard[7][1]=2;

	    flag=1;
	}


        game_print(gameboard);

        printf("\n\n");
	    mysleep(3);

		
		tree1_update(good1_initial1,good1_initial2,gameboard);
		MysearchTree1.DFS_Search(MysearchTree1.root);
                MysearchTree1.goodAgentsdecide(); 
                goodAgent1Move(globalhold[0],gameboard,good1_initial1,good1_initial2);
		former11=good1_initial1;
		former12=good1_initial2;
                MysearchTree1.emptystacks();
                MysearchTree1.deleteTree(MysearchTree1.root);
		MysearchTree1.root=NULL;
                good1_initial1=globalinitial1;
		good1_initial2=globalinitial2;
   

		tree2_update(good2_initial1,good2_initial2,gameboard);
		MysearchTree2.DFS_Search(MysearchTree2.root);
                MysearchTree2.goodAgentsdecide();
                goodAgent1Move(globalhold[1],gameboard,good2_initial1,good2_initial2);
		MysearchTree2.emptystacks();
      	        former21=good2_initial1;
		former22=good2_initial2;
		MysearchTree2.deleteTree(MysearchTree2.root);
		MysearchTree2.root=NULL;
                good2_initial1=globalinitial1;
		good2_initial2=globalinitial2;
      

		tree3_update(good3_initial1,good3_initial2,gameboard);
		MysearchTree3.DFS_Search(MysearchTree3.root);
                MysearchTree3.goodAgentsdecide();
                goodAgent1Move(globalhold[2],gameboard,good3_initial1,good3_initial2);
		former31=good3_initial1;
		former32=good3_initial2;
		MysearchTree3.emptystacks();
		MysearchTree3.deleteTree(MysearchTree3.root);
		MysearchTree3.root=NULL;
                good3_initial1=globalinitial1;
		good3_initial2=globalinitial2;


                tree4_update(good4_initial1,good4_initial2,gameboard);
		MysearchTree4.DFS_Search(MysearchTree4.root);
                MysearchTree4.goodAgentsdecide();
                goodAgent1Move(globalhold[3],gameboard,good4_initial1,good4_initial2);
		former41=good4_initial1;
		former42=good4_initial2;
		MysearchTree4.emptystacks();
		MysearchTree4.deleteTree(MysearchTree4.root);
		MysearchTree4.root=NULL;
                good4_initial1=globalinitial1;
		good4_initial2=globalinitial2;


        zorbey=0;
     
if(gameboard[initial1+1][initial2]!=0 &&
 gameboard[initial1-1][initial2]!=0 
   && gameboard[initial1][initial2-1]!=0 &&
 gameboard[initial1][initial2+1]!=0)
		 {
	         printf("------------GAME OVER--------------");
			 break;
		 }
}
}


return 0;
}
