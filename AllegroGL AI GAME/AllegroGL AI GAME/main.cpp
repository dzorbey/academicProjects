#include <allegro.h>
#include <alleggl.h>
#include "cube.h"
//#include "CameraMan.cpp"
#include "mycamera.cpp"
#include "sphere.h"
#include <vector>
#include <string.h>
#include <stack>
#include <pthread.h>
#include <semaphore.h>
#include <windows.h>

#include	<gl\gl.h>							// Header File For The OpenGL32 Library
#include	<gl\glu.h>							// Header File For The GLu32 Library


using namespace std;

GLuint SlateTex;
    
BITMAP *myImage;

HANDLE hmutex;
HANDLE hproducer,hconsumer;

int globalhold[4];
int zorbey=0;
int globalinitial1,globalinitial2;
int myglobalinitial1,myglobalinitial2;


GLuint		texture[1];	



class list1
{
public:
	list1();
	~list1();
	int emptylist1();
	void insertend1(int);
	void printlist1();
	void addFront1(int);
	void deleteFront1();
	void deletespecific1(int);
private:
	//NODEPTR1 listptr1;
};



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

                          if(start->right==NULL) {
                                    start->right=new Node<T>;
                                    start->right->parent=start;
                                    start->right->x=(start->x)+2;            
                                    start->right->y=(start->y)+2;               
                                                }


		start->right->back=insert(start->right->back,x,y,data);
              insert(start->right->back,x,y,data)->parent=start->right;
	}
	else if(x<start->x && y>start->y)
	{
         if(start->right==NULL) {
                                    start->right=new Node<T>;
                                    start->right->parent=start;
                                    start->right->x=(start->x)-2;            
                                    start->right->y=(start->y)+2;               
                                                }
                            
         
         
		start->right->forward=insert(start->right->forward,x,y,data);            
        insert(start->right->forward,x,y,data)->parent=start->right;
	}
	else if(x>start->x && y<start->y)
	{
         
         if(start->left==NULL) {
                                    start->left=new Node<T>;
                                    start->left->parent=start;
                                    start->left->x=(start->x)+2;            
                                    start->left->y=(start->y)-2;               
                                                }
                            
         
         
         
		start->left->back=insert(start->left->back,x,y,data);
               insert(start->left->back,x,y,data)->parent=start->left;
	}
	else if(x<start->x && y<start->y)
	{
         
                        
        if(start->left==NULL) {
                                    start->left=new Node<T>;
                                    start->left->parent=start;
                                    start->left->x=(start->x)-2;            
                                    start->left->y=(start->y)-2;               
                                                }
         
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

void randommove(int gameboard[32][32],int x,int y);
void tree1_update(int contain1,int contain2, int gameboard[32][32]);
void tree2_update(int contain1,int contain2, int gameboard[32][32]);
void tree3_update(int contain1,int contain2, int gameboard[32][32]);
void tree4_update(int contain1,int contain2, int gameboard[32][32]);
void goodAgent1Move(int myglobalhold,int gameboard[32][32],int x,int y);
void BadAgent1Move(int myglobalhold,int gameboard[32][32],int x,int y);
void game_print(int gameboard[32][32]);
void mysleep(); 
    
void tree1_update(int contain1,int contain2, int gameboard[32][32]) {

	int i,j;
	for(i=contain1; i>=0; i=i-2)
	{
		for(j=contain2; j<32; j=j+2)
		{
		MysearchTree1.insertTree(i,j,gameboard[i][j]);
		}
	}
	for(i=contain1; i<32; i=i+2)
	{
		for(j=contain2; j<32; j=j+2)
		{
		MysearchTree1.insertTree(i,j,gameboard[i][j]);
		}
	}
	for(i=contain1; i>=0; i=i-2)
	{
		for(j=contain2; j>=0; j=j-2)
		{
		MysearchTree1.insertTree(i,j,gameboard[i][j]);
		}
	}
	for(i=contain1; i<32; i=i+2)
	{
		for(j=contain2; j>=0; j=j-2)
		{
		MysearchTree1.insertTree(i,j,gameboard[i][j]);
		}
	}
}





void tree2_update(int contain1,int contain2, int gameboard[32][32]) {

	int i,j;
	for(i=contain1; i>=0; i=i-2)
	{
		for(j=contain2; j<32; j=j+2)
		{
		MysearchTree2.insertTree(i,j,gameboard[i][j]);
		}
	}
	for(i=contain1; i<32; i=i+2)
	{
		for(j=contain2; j<32; j=j+2)
		{
		MysearchTree2.insertTree(i,j,gameboard[i][j]);
		}
	}
	for(i=contain1; i>=0; i=i-2)
	{
		for(j=contain2; j>=0; j=j-2)
		{
		MysearchTree2.insertTree(i,j,gameboard[i][j]);
		}
	}
	for(i=contain1; i<32; i=i+2)
	{
		for(j=contain2; j>=0; j=j-2)
		{
		MysearchTree2.insertTree(i,j,gameboard[i][j]);
		}
	}
}


void tree3_update(int contain1,int contain2, int gameboard[32][32]) {

	int i,j;
	for(i=contain1; i>=0; i=i-2)
	{
		for(j=contain2; j<32; j=j+2)
		{
		MysearchTree3.insertTree(i,j,gameboard[i][j]);
		}
	}
	for(i=contain1; i<32; i=i+2)
	{
		for(j=contain2; j<32; j=j+2)
		{
		MysearchTree3.insertTree(i,j,gameboard[i][j]);
		}
	}
	for(i=contain1; i>=0; i=i-2)
	{
		for(j=contain2; j>=0; j=j-2)
		{
		MysearchTree3.insertTree(i,j,gameboard[i][j]);
		}
	}
	for(i=contain1; i<32; i=i+2)
	{
		for(j=contain2; j>=0; j=j-2)
		{
		MysearchTree3.insertTree(i,j,gameboard[i][j]);
		}
	}
}

void tree4_update(int contain1,int contain2, int gameboard[32][32]) {

	int i,j;
	for(i=contain1; i>=0; i=i-2)
	{
		for(j=contain2; j<32; j=j+2)
		{
		MysearchTree4.insertTree(i,j,gameboard[i][j]);
		}
	}
	for(i=contain1; i<32; i=i+2)
	{
		for(j=contain2; j<32; j=j+2)
		{
		MysearchTree4.insertTree(i,j,gameboard[i][j]);
		}
	}
	for(i=contain1; i>=0; i=i-2)
	{
		for(j=contain2; j>=0; j=j-2)
		{
		MysearchTree4.insertTree(i,j,gameboard[i][j]);
		}
	}
	for(i=contain1; i<32; i=i+2)
	{
		for(j=contain2; j>=0; j=j-2)
		{
		MysearchTree4.insertTree(i,j,gameboard[i][j]);
		}
	}
}    
    
    
void goodAgent1Move(int myglobalhold,int gameboard[32][32],int x,int y) {


        if(myglobalhold==4 && gameboard[x][(y)+2]==0)
        {
                globalinitial1=x;
                globalinitial2=(y)+2;}
        else if(myglobalhold==3 && gameboard[x][(y)-2]==0)
        {
                globalinitial1=x;
                globalinitial2=(y)-2;}
        else if(myglobalhold==2 && gameboard[(x)-2][y]==0)
        {
                globalinitial1=(x)-2;
                globalinitial2=y;}
        else if(myglobalhold==1 && gameboard[(x)+2][y]==0)
        {
                globalinitial1=(x)+2;
                globalinitial2=y;}
        else{
		
		globalinitial1=x;
		globalinitial2=y;
		}
}


//THIS FUNCTION IS FOR THE BAD AGENT IN THE SECOND CHOISE
void BadAgent1Move(int myglobalhold,int gameboard[32][32],int x,int y) {


	if(myglobalhold==2  && gameboard[x][(y)+2]==0)
        {
                myglobalinitial1=x;
                myglobalinitial2=(y)+2;}
        else if(myglobalhold==4 && gameboard[x][(y)-2]==0)
        {
                myglobalinitial1=x;
                myglobalinitial2=(y)-2;}
        else if(myglobalhold==1 && gameboard[(x)-2][y]==0)
        {
                myglobalinitial1=(x)-2;
                myglobalinitial2=y;}
        else if(myglobalhold==3 && gameboard[(x)+2][y]==0)
        {
                myglobalinitial1=(x)+2;
                myglobalinitial2=y;}
        else{
		
		myglobalinitial1=x;
		myglobalinitial2=y;
		}
}    
    
    
void randommove(int gameboard[32][32],int x,int y) {

int k;

int m=0;
while(1) {
    k=rand()%4;
m++;

    if(k==0 && gameboard[x][(y)-2]==0)
	{
             if(y-2==-2){ continue;}  
            
		globalinitial1=x;
		globalinitial2=(y)-2;
		break;
	} 
	else
	if(k==1 && gameboard[(x)+2][y]==0)
	{
            if(x+2==32){ continue;}  
            
		globalinitial1=(x)+2;
		globalinitial2=y;
		break;
	}
	else
	if(k==2 &&  gameboard[(x)-2][y]==0)
	{
                if(x-2==-2){ continue;}    
            
		globalinitial1=(x)-2;
		globalinitial2=y;
		break;
	}
	else 
        if(k==3 && gameboard[x][(y)+2]==0)
	{
          
        if(y+2==32){ continue;}
        
		globalinitial1=x;
		globalinitial2=(y)+2;
		break;
	}
	else{
		
	}
//	if(m==5000) {
//		globalinitial1=x;
//		globalinitial2=y;
//		break;
//	}
	}
}    
    
    
    
    
    
    
    
    
    
    
    
volatile int Time = 0;
void TimerFunc()
{
    Time++;
}
END_OF_FUNCTION(TimerFunc);

void Init()
{
    allegro_init();
    install_allegro_gl();
    install_timer();
    install_keyboard();
    install_mouse();
    
    
     enable_hardware_cursor();
     
     
    select_mouse_cursor(MOUSE_CURSOR_BUSY);
    show_mouse(screen);
    select_mouse_cursor(MOUSE_CURSOR_ARROW);
 
 
    allegro_gl_set(AGL_DOUBLEBUFFER, true);
    allegro_gl_set(AGL_COLOR_DEPTH, 16);
    allegro_gl_set(AGL_RENDERMETHOD, true);
    allegro_gl_set(AGL_Z_DEPTH, 16);
    allegro_gl_set(AGL_SUGGEST, AGL_DOUBLEBUFFER | AGL_COLOR_DEPTH | AGL_RENDERMETHOD);
    
    
    //	allegro_gl_set(AGL_Z_DEPTH, 8);
//	allegro_gl_set(AGL_COLOR_DEPTH, 16);
//	allegro_gl_set(AGL_SUGGEST, AGL_Z_DEPTH | AGL_COLOR_DEPTH);
    
//    allegro_gl_set(AGL_DOUBLEBUFFER, true);
 //   allegro_gl_set(AGL_SUGGEST, AGL_DOUBLEBUFFER);

    set_color_depth(16);
    set_gfx_mode(GFX_OPENGL_WINDOWED, 640, 480, 0, 0);
      // Enable texturing
    glEnable(GL_TEXTURE_2D);
   
    // Set up culling
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_COLOR); 
    
   // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();  
    glMatrixMode(GL_PROJECTION);
    //glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 1000.0);
    glFrustum(-1.0, 1.0, -1.0, 1.0, 1, 60.0);  
    glMatrixMode(GL_MODELVIEW);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    
    
    
    
    
    
}

void game();
void camera();
void display();
CameraMan cm;
float speed = 0.1, rspeed = 1.0;


void camera() {
     
         //install_keyboard();
     // Init();
    // CameraMan cm;
      //float speed = 0.1, rspeed = 1.0;
     while(!key[KEY_ESC])
    { 
    
             if(key[KEY_LEFT])       cm.Yaw(rspeed); 
             if(key[KEY_RIGHT])      cm.Yaw(-rspeed);
             if(key[KEY_UP])         cm.Pitch(rspeed);
             if(key[KEY_DOWN])       cm.Pitch(-rspeed);
             if(key[KEY_Z])          cm.Roll(rspeed);
             if(key[KEY_X])          cm.Roll(-rspeed);
 
             if(key[KEY_W])          cm.Walk(speed);
             if(key[KEY_S])          cm.Walk(-speed);
             if(key[KEY_D])          cm.Sidestep(speed);
             if(key[KEY_A])          cm.Sidestep(-speed);
             if(key[KEY_LCONTROL])   cm.Crouch(speed);
             
              cm.Update();
              rest(5);
              
             
     }
  
     
     
     
     }
     
     
void display() {
     }

Cube cube5(-2,0, 5, 1.5);


int main()
{
    
    //FONT *tmp;
   // Init();
    
    int pid;
	char ch;
    HANDLE hth[2];
	DWORD thid;
	//hmutex=CreateMutex(NULL,FALSE,NULL);

    
    //hproducer=CreateEvent(NULL,TRUE,FALSE,NULL);
//	hconsumer=CreateEvent(NULL,TRUE,FALSE,NULL);

     
	hth[0]=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)game,NULL,0,&thid);
	hth[1]=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)camera,NULL,0,&thid);
	WaitForMultipleObjects(1,hth,TRUE,INFINITE);
	
	//game();
	
	
    
    return 0;
}
END_OF_MAIN();










void game() {
     
     Init();
     
//AUX_RGBImageRec *TextureImage[1];		
     FONT *tmp;
     
       srand((unsigned)time(NULL));

	int i=0,j=0;
	int k=0;
	int l=0;
    int globcount;
	int time=0;
	int flag=0;
	int former1=0;
	int former2=14;

   int x1,x2;
int x3,x4;int x5,x6;
int x7,x8;
	initial1=6; initial2=4;
    x1=good1_initial1=14;  x2=good1_initial2=2;
    x3=good2_initial1=24;  x4=good2_initial2=4;
    x5=good3_initial1=20;  x6=good3_initial2=6;
    x7=good4_initial1=0;  x8=good4_initial2=24;
    int gameboard[32][32];
    
    
    LOCK_VARIABLE(Time);
    LOCK_FUNCTION(TimerFunc);
    
    install_int_ex(TimerFunc, BPS_TO_TIMER(60));
    
    //Cube cube(0.0, 0.0, -2.0, 1.0);
    //Cube cube2(12, 0, -2, 1.2);
    
     Sphere sphere[1] =
    {
        Sphere(0.8, 16, 20, 0, 0, 14, -2),
       // Sphere(4.0, 16, 20, 0.7, -9.0, 6.0, -16.0),
       // Sphere(3.0, 16, 20, 0.6, -8.0, -7.0, -18.0),
       // Sphere(2.0, 16, 20, 0.5, 7.0, 7.0, -10.0),
       // Sphere(1.0, 16, 20, 0.4, 6.0, -6.0, -8.0)
    };
    
    
    
    for(int i = 0; i < 1; i++)
    {
        sphere[i].dxr = float(rand() % 1000) / 1000;
        sphere[i].dyr = float(rand() % 1000) / 1000;
        sphere[i].dzr = float(rand() % 1000) / 1000;
    }


    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    
 
    Cube cube(30, 2, -2,  1.2);
    Cube cube2(24, 4, -2, 1.2);
    Cube cube3(20, 6, -2, 1.2);
    Cube cube4(0, 24, -2, 1.2);
    
    
  
    
     for(i=0; i<32; i=i+2)
	{
	      // gameboard[i-2][j]=4;
		for(j=0; j<32; j=j+2)
		{
			gameboard[i][j]=0;
		}
         //gameboard[i][j+2]=4;

	}
    
    
   // float speed = 0.1, rspeed = 1.0;

   // CameraMan cm;//= new mycamera;
    
   tmp = allegro_gl_load_system_font_ex("Arial", AGL_FONT_TYPE_OUTLINE,
                                              AGL_FONT_STYLE_BOLD, 0, 0, 0.1, 0, 200);

    while(!key[KEY_ESC])
    { 
                        
    




if(flag==0)
	{
        gameboard[6][4]=1;
        	sphere[0].xp=6; sphere[0].yp=4;//printf("O");
	    gameboard[14][2]=2;
		gameboard[24][4]=3;
		gameboard[20][6]=4;
		gameboard[0][24]=5;

	    flag=1;
	}




/*
             if(key[KEY_LEFT])       cm.Yaw(rspeed); 
             if(key[KEY_RIGHT])      cm.Yaw(-rspeed);
             if(key[KEY_UP])         cm.Pitch(rspeed);
             if(key[KEY_DOWN])       cm.Pitch(-rspeed);
             if(key[KEY_Z])          cm.Roll(rspeed);
             if(key[KEY_X])          cm.Roll(-rspeed);
 
             if(key[KEY_W])          cm.Walk(speed);
             if(key[KEY_S])          cm.Walk(-speed);
             if(key[KEY_D])          cm.Sidestep(speed);
             if(key[KEY_A])          cm.Sidestep(-speed);
             if(key[KEY_LCONTROL])   cm.Crouch(speed);
 */
                    //  rest(10);   
                    
                    //cm.Update();
             glClear(GL_COLOR_BUFFER_BIT);
             
             //
             cm.Update();
             glLoadIdentity();
             cm.ApplyTransformations(); 
          
          
          
      //sphere[0].Update();                    
   // cube.Update2();    
	//cube.Render();
                                                 
	int i,j;

        
        
  //for(int i = 0; i < 5; i++)
   //         {
     //           sphere[0].Render();
     //       }      
        
        
        // sphere[0].Update2();
          sphere[0].Render();
         // cube.Render();
          //:  cube.Update2();
          //  cube2.Update2();
           // cube3.Update2();
           // cube4.Update2();
        
        
 

        
        cube5.Update2();
        cube.Render();
        cube2.Render();
        cube3.Render();
        cube4.Render();
        cube5.Render();
        
        
      /*
        glBegin(GL_LINES);
		glColor3ub(255, 255, 255);
		glVertex3f(cube3.x, cube3.y, cube3.z);
		glVertex3f(sphere[0].xp, sphere[0].yp, sphere[0].zp);
	glEnd();
        */
        
        if(flag==1) {
        
            if(gameboard[good1_initial1][good1_initial2]==0)
		 {
                            gameboard[x1][x2]=0;
			 gameboard[good1_initial1][good1_initial2]=2;
			  //gameboard[x1][x2]=0;

		 }else {
		 
       
       //gameboard[x1][x2]=0;
      
		/*     randommove(gameboard,good1_initial1,good1_initial2);
	         good1_initial1=globalinitial1;
		     good1_initial2=globalinitial2;
	  	     gameboard[good1_initial1][good1_initial2]=2;    //gameboard[x1][x2]=0;
	   */
	    gameboard[x1][x2]=2;
	   	good1_initial1=x1;
	    good1_initial2=x2;
       
      }




 if(gameboard[good2_initial1][good2_initial2]==0)
		 {
                                                     gameboard[x3][x4]=0;
			 gameboard[good2_initial1][good2_initial2]=3;
			//   gameboard[x3][x4]=0;
	
		 }
		 else { 
			//	 gameboard[x3][x4]=0;
/*		 randommove(gameboard,good2_initial1,good2_initial2);
	     good2_initial1=globalinitial1;
    	 good2_initial2=globalinitial2;
        gameboard[good2_initial1][good2_initial2]=3; //gameboard[x3][x4]=0;
	*/	
        gameboard[x3][x4]=3;
	   	good2_initial1=x3;
		good2_initial2=x4;
        
        
       }


if(gameboard[good3_initial1][good3_initial2]==0)
	   {
                                               	 gameboard[x5][x6]=0;
				 gameboard[good3_initial1][good3_initial2]=4;
	 	  //gameboard[x5][x6]=0;
	   }
       	   else{
                
                //	 gameboard[x5][x6]=0;
                
	/*	 randommove(gameboard,good3_initial1,good3_initial2);
	      good3_initial1=globalinitial1;
		  good3_initial2=globalinitial2;
          gameboard[good3_initial1][good3_initial2]=4;
        */        //	 gameboard[x5][x6]=0;
          
         gameboard[x5][x6]=4;
	   	good3_initial1=x5;
		good3_initial2=x6;
          
             }


	   if(gameboard[good4_initial1][good4_initial2]==0)
	   {
                                                       gameboard[x7][x8]=0;
			   gameboard[good4_initial1][good4_initial2]=5;
			    //gameboard[x5][x6]=0;
	   }
	   else { 		
        //     gameboard[x7][x8]=0;
       	// randommove(gameboard,good4_initial1,good4_initial2);
	     //    good4_initial1=globalinitial1;
	     //    good4_initial2=globalinitial2;
          //  gameboard[good4_initial1][good4_initial2]=5;// gameboard[x7][x8]=0;
              gameboard[x7][x8]=5;
	   	good4_initial1=x7;
		good4_initial2=x8;
	   }
}

   
  
     for(i=0; i<32; i=i+2)
	{
		for(j=0; j<32; j=j+2)
		{
			if(gameboard[i][j]==1) {
				sphere[0].xp=i; sphere[0].yp=j;//printf("O");
             }
			if(gameboard[i][j]==2) {
				cube.x=i; cube.y=j;//printf("X");
            }
            if(gameboard[i][j]==3) {
				cube2.x=i; cube2.y=j;//printf("X");
            }
             if(gameboard[i][j]==4) {
				cube3.x=i; cube3.y=j;//printf("X");
            }
              if(gameboard[i][j]==5) {
				cube4.x=i; cube4.y=j;//printf("X");
            }
		//	else{ } 
				//printf("*");
		}
	//	printf("\n");
	}
        
        
        
        
        
        
        
       
      
        tree1_update(good1_initial1,good1_initial2,gameboard);
		MysearchTree1.DFS_Search(MysearchTree1.root);
        MysearchTree1.goodAgentsdecide();
		goodAgent1Move(globalhold[0],gameboard,good1_initial1,good1_initial2);
        MysearchTree1.emptystacks();
        MysearchTree1.deleteTree(MysearchTree1.root);
		MysearchTree1.root=NULL;
		
		x1=good1_initial1;
		x2=good1_initial2;
		//gameboard[x1][x2]=0;
        good1_initial1=globalinitial1;
		good1_initial2=globalinitial2;
		
	
		
		
		
		
   
   
		tree2_update(good2_initial1,good2_initial2,gameboard);
		MysearchTree2.DFS_Search(MysearchTree2.root);
        MysearchTree2.goodAgentsdecide();
        goodAgent1Move(globalhold[1],gameboard,good2_initial1,good2_initial2);
		MysearchTree2.emptystacks();
		MysearchTree2.deleteTree(MysearchTree2.root);
		MysearchTree2.root=NULL;
		
		x3=good2_initial1;
		x4=good2_initial2;
		//gameboard[x3][x4]=0;
        good2_initial1=globalinitial1;
		good2_initial2=globalinitial2;
     

		tree3_update(good3_initial1,good3_initial2,gameboard);
		MysearchTree3.DFS_Search(MysearchTree3.root);
        MysearchTree3.goodAgentsdecide();
        goodAgent1Move(globalhold[2],gameboard,good3_initial1,good3_initial2);
		MysearchTree3.emptystacks();
		MysearchTree3.deleteTree(MysearchTree3.root);
		MysearchTree3.root=NULL;
		
			x5=good3_initial1;
		x6=good3_initial2;
		//gameboard[x5][x6]=0;
        good3_initial1=globalinitial1;
		good3_initial2=globalinitial2;


        tree4_update(good4_initial1,good4_initial2,gameboard);
		MysearchTree4.DFS_Search(MysearchTree4.root);
        MysearchTree4.goodAgentsdecide();
        goodAgent1Move(globalhold[3],gameboard,good4_initial1,good4_initial2);
		MysearchTree4.emptystacks();
		MysearchTree4.deleteTree(MysearchTree4.root);
		MysearchTree4.root=NULL;
			x7=good4_initial1;
		x8=good4_initial2;
		//gameboard[x7][x8]=0;
        good4_initial1=globalinitial1;
		good4_initial2=globalinitial2;





        if(flag==1){
       former1=initial1;
	   former2=initial2;

           randommove(gameboard,initial1,initial2);
           initial1=globalinitial1;
           initial2=globalinitial2;
	  if(gameboard[initial1][initial2]==0)
	   {
		   gameboard[initial1][initial2]=1;
		   gameboard[former1][former2]=0;
	   }
	   else {
		   gameboard[former1][former2]=1;
                   initial1=former1;
                   initial2=former2;
	   }

}



        zorbey=0;

        
        
        
        
         glFlush();

        
        allegro_gl_flip();
    }
       //     allegro_gl_flip();
     
     }








