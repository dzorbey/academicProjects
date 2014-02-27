
package javaapplication21;


import java.awt.*;
import java.awt.geom.*;
import java.awt.event.*;
import java.awt.image.*;
import java.io.*;
import javax.imageio.ImageIO;
import java.net.URL;
import javax.swing.*;
import java.awt.Graphics2D;

import que.*;
import GPS.*;



public class Example02 extends Frame implements ActionListener, MouseListener, MouseMotionListener  {
	private static final String FILE_OPEN_COMMAND = "FILE_OPEN_COMMAND";
	private static final String EXIT_COMMAND = "EXIT_COMMAND";
	private static final String STOP = "STOP";
        
        
        
   Font exFont = new Font("TimesRoman",Font.PLAIN,15);
   Font exFont2 = new Font("TimesRoman",Font.PLAIN,15);
   int secim;
   
   double GpsDistanceNorth=0,GpsDistanceEast=0,oldnorth,oldeast;
   PortConnect myconnect; 
   int[] check2;
   int[] check3;
   int[][] check4;
   int homur1,homur2;
   int blackflag=0;
   MYPoint mypoint, yea;
   ColorProcess myColorProcess;
   int sk;
   int circledimension=2;
   boolean checkme;
    Wind CompountWind;
    ArrayQueue backwards;
    ArrayQueue kimokim,kimokim2,determine;
    ArrayQueue kimokim3;
    GpsDistance CalculateDistance;
    Weather currentweather;
    
    HelloThread mythread;
    AnotherThread gpsthread;
    long my;
    int myInt,horizontal_move,vertical_move,myoo,anothertemp;
    
    int l=0,repetation;
    public Image forest;
    
    
    
    int i=1;
    Long stoptime = 2000L;
    int cordX=100,cordY=200;
    
    
    int this1=2,signx,signy,myflag=1,myflag2,onlyforonetime=1;
     
	public Canvas canvas;
	public ScrollPane scrollPane;
        private String filename;
	public int dragStartX,dragStartY,lastX,lastY;
	double gpsx=170,gpsy=170;
        double oldhumidity;
        String forestk;    
        Ellipse2D.Double circlegps =  new Ellipse2D.Double(50, 50, 8, 8);
        
       int ben,sen;
         
         
	public Example02(String forestx,Wind myCompountWind,int time,Point fire,Point gps,Weather Climate,int baydi) {
		super("Watch Me");

        circlegps.x=gps.x;
        circlegps.y=gps.y;
        ben=fire.x;
        sen=fire.y;
        secim=baydi;
        check4=new int[400][400];
        repetation=time;
        anothertemp=repetation;
        currentweather=new Weather();
        currentweather=Climate;
        currentweather.currenthumidity=currentweather.humidity;
        oldhumidity=currentweather.humidity;
        
        
        CompountWind=new Wind();
        CompountWind=myCompountWind;
        determine=new ArrayQueue(); 
        backwards=new ArrayQueue();
        kimokim=new ArrayQueue();
        kimokim2=new ArrayQueue();
        kimokim3=new ArrayQueue();
        mythread=new HelloThread();
        gpsthread=new AnotherThread();
        myconnect=new PortConnect();
        CalculateDistance=new GpsDistance();
        
        //try {
        //myconnect.GpsPort();
       // }
        //catch(IOException e) {
        //    e.printStackTrace();
       // }
        mythread.start();
        gpsthread.start();
    
     
        mypoint=new MYPoint();  
        myColorProcess=new ColorProcess();
        
        forestk=forestx;
        forest = Toolkit.getDefaultToolkit().getImage(forestk);
        myflag2=repetation;
        
        
        
        sk=10;
                     
    
    long my=Math.round(Math.abs(CompountWind.hypotenus/CompountWind.k));
    myInt = (int)my;
    

            
       if(CompountWind.desicion==1)  {
          horizontal_move=1;
          vertical_move=1;
          signx=1;
          signy=1;
       }
       else if(CompountWind.desicion==2) {
          horizontal_move=1;
          vertical_move=-1;
          signx=1;
          signy=-1;
       }
       else if(CompountWind.desicion==3) {
          horizontal_move=-1;
          vertical_move=-1;
          signx=-1;
          signy=-1;
       }
       else if(CompountWind.desicion==4) {
          horizontal_move=-1;
          vertical_move=1;
          signx=-1;
          signy=1;
       }
       else{}
    
         
            yea=new MYPoint();
            if(myInt==1) {
                myInt=2;
            }
   
            int temp=Math.abs(vertical_move);
            
            long oo=Math.round((temp*myInt)/2);
            myoo=(int)oo;
    
            
                  
            mypoint.x=fire.x;
            mypoint.y=fire.y;
            
            determine.enqueue(mypoint.x);
            determine.enqueue(mypoint.y);
            backwards.enqueue(mypoint.x);
            backwards.enqueue(mypoint.y);
                
            
                MenuBar menuBar = new MenuBar();
		Menu menu = new Menu("Start");
		menu.addActionListener(this);
          
                Menu menu2 = new Menu("Stop");
		menu2.addActionListener(this);
                
                
            
                MenuItem mi = new MenuItem("Start");
		mi.setActionCommand(FILE_OPEN_COMMAND);
		menu.add(mi);
                
                mi=new MenuItem("Stop");
                mi.setActionCommand(STOP);
                menu2.add(mi);
                
            
            menuBar.add(menu);
	    menuBar.add(menu2);	
            setMenuBar(menuBar);
            
            
            
   
                	this.canvas = new Canvas() {
			public void update(Graphics g) {
				paint(g);
			}
			
			public Dimension getPreferredSize() {
				return getSize();
			}
                        
                        
                        public void paint(Graphics g) {
                    int width = forest.getWidth(this);
                    int height = forest.getHeight(this);
                    if (width != -1 && width != getWidth()) {
					setSize(width, getHeight());
						}
						if (height != -1 && height != getHeight()) {
							setSize(getWidth(), height);
						}
    
                    
                    

       if(currentweather.currenthumidity < oldhumidity) {
           
           circledimension=circledimension+5;
           //System.out.println("DMENSIONNNN"+circledimension);
           oldhumidity=currentweather.currenthumidity;
       }
                    
                    
                    
                    
    
                        Ellipse2D.Double circlered =  new Ellipse2D.Double(50, 50, circledimension, circledimension);
                        Ellipse2D.Double circleblack =  new Ellipse2D.Double(50, 50, circledimension, circledimension);
                       
                        int i;
     
       Graphics2D g2d = (Graphics2D)g;
       Graphics2D g3d = (Graphics2D)g;
       Graphics2D g4d = (Graphics2D)g;
       Graphics2D g5d = (Graphics2D)g;
       g.setFont(exFont);
       Graphics2D g6d = (Graphics2D)g;
       
       g6d.setFont(exFont2);
       g6d.setColor(Color.GREEN);
      
       
       
      float dash[] = {1.0f};
      g5d.setStroke(new BasicStroke(1.0f, BasicStroke.CAP_BUTT, BasicStroke.JOIN_MITER, 1.0f, dash, 0.0f));
    
            
           

    
      int flag=0;
      g.drawImage(forest,0,0,this);
                           
     
       g6d.drawString( "Temprature: "+ String.valueOf( Math.round(currentweather.temprature) ) + "C", 15, 20);
       g6d.drawString( "Humadity: " +String.valueOf( Math.round(currentweather.currenthumidity) )+ "%",15 , 40);
  
      
      
      
      
      
              if(kimokim.isEmpty()==false) {
                while(!kimokim.isEmpty()) {
                                     
                   homur1=kimokim.dequeue();
                   homur2=kimokim.dequeue();
                   kimokim2.enqueue(homur1);
                   kimokim2.enqueue(homur2);
                   circleblack.x=homur1; circleblack.y=homur2;
                   g3d.setColor(Color.RED);
                   g3d.fill(circleblack);
                   g3d.draw(circleblack);}
 }
 while(kimokim2.isEmpty()==false) {
              int homhom=kimokim2.dequeue();
              int homhom2=kimokim2.dequeue();
              kimokim.enqueue(homhom);
              kimokim.enqueue(homhom2);
 }
              
  
      
      
      if(backwards.isEmpty()==false) {
            //if(myflag>repetation/2) {
              while(!backwards.isEmpty()) {
                                         
                   int homur1=backwards.dequeue();
                   int homur2=backwards.dequeue();
                   kimokim3.enqueue(homur1);
                   kimokim3.enqueue(homur2);
                   circleblack.x=homur1; circleblack.y=homur2;
                   
                   if(myflag!=anothertemp/6) {
                   g3d.setColor(Color.BLACK);
                   g3d.fill(circleblack);
                   g3d.draw(circleblack);
                   myflag++;
                   }
                   //if(myflag>=repetation/2){
                  //     myflag=0;
                  // }
              }
              myflag=0;
      }
      
 
  while(kimokim3.isEmpty()==false) {
            
              int homhom=kimokim3.dequeue();
              int homhom2=kimokim3.dequeue();
              backwards.enqueue(homhom);
              backwards.enqueue(homhom2);
 }
      
      
      
      
      
      
      
      
      
      
    
                            
while(myflag2>0) {
 myflag2--;                  
 //myflag++;                 
 

 if(blackflag==1) {
 anothertemp=anothertemp*2;
 blackflag=0;
 }
 
 sk=10; 

 


                        
           if(determine.isEmpty()==false) {
                         mypoint.x=determine.dequeue();
                         mypoint.y=determine.dequeue();
           
                         circlered.x=mypoint.x;
                         circlered.y=mypoint.y;
           }                  
   
                         circlered.x=mypoint.x;
                         circlered.y=mypoint.y;
                         g2d.setColor(Color.YELLOW);
                         g2d.fill(circlered);
                         g2d.draw(circlered);

 
 
   
        //              if(check[mypoint.x][mypoint.y]==1) {
                           backwards.enqueue(mypoint.x);
                           backwards.enqueue(mypoint.y);
           //                check[mypoint.x][mypoint.y]=1;
             //            }
                         
                         
                         
                         
                  int tomp1=mypoint.x;
                  int tomp2=mypoint.y;
                
                  
                  
                  int  tut=  (int) Math.round((Math.cos(Math.toRadians(CompountWind.angle)))*myoo) ;
                  int tut2=  (int) Math.round((Math.sin(Math.toRadians(CompountWind.angle)))*myoo) ;

                   mypoint.x=tomp1 + (tut*signx) ;
                   mypoint.y=tomp2 + (tut2*signy);
                         
                         
                      if(check4[mypoint.x][mypoint.y]!=1) {
                      
                              determine.enqueue(mypoint.x);
                              determine.enqueue(mypoint.y);
                              kimokim.enqueue(mypoint.x);
                              kimokim.enqueue(mypoint.y);
                              backwards.enqueue(mypoint.x);
                              backwards.enqueue(mypoint.y);
                              check4[mypoint.x][mypoint.y]=1;
                             
                      }
                      
                      yea.x=tomp1;
                      yea.y=tomp2;
          
                      mypoint.x=tomp1+horizontal_move;
                      mypoint.y=tomp2;
               
                      if(check4[mypoint.x][mypoint.y]!=1) {
                       
                              determine.enqueue(mypoint.x);
                              determine.enqueue(mypoint.y);
                              kimokim.enqueue(mypoint.x);
                              kimokim.enqueue(mypoint.y);
                              backwards.enqueue(mypoint.x);
                              backwards.enqueue(mypoint.y);
                              check4[mypoint.x][mypoint.y]=1;
                              
                       
                      }
                      
                      
                      int yettibe=tomp1-horizontal_move;
                      int aynen=tomp2;
                      
                      
                       if(check4[yettibe][aynen]!=1) {
                       
                              determine.enqueue(yettibe);
                              determine.enqueue(aynen);
                              kimokim.enqueue(yettibe);
                              kimokim.enqueue(aynen);
                              backwards.enqueue(yettibe);
                              backwards.enqueue(aynen);
                              check4[yettibe][aynen]=1;
                       
                      }
                      
                      
                      yettibe=tomp1;
                      aynen=tomp2-vertical_move;
                      
                      
                       if(check4[yettibe][aynen]!=1) {
                       
                              determine.enqueue(yettibe);
                              determine.enqueue(aynen);
                              kimokim.enqueue(yettibe);
                              kimokim.enqueue(aynen);
                              backwards.enqueue(yettibe);
                              backwards.enqueue(aynen);
                              check4[yettibe][aynen]=1;
                       
                      }
                      
                      
                      
                      
                      
                      
             
                      if(myInt==1){ 
                            myInt=2;}
                      
        for(i=0; i<myInt; i++) {
                          
         int  hold1=  (int) Math.round((Math.cos(Math.toRadians(CompountWind.angle)))*vertical_move) ;
         int  hold2=  (int) Math.round((Math.sin(Math.toRadians(CompountWind.angle)))*vertical_move) ;
         yea.x=yea.x + (hold1*signx) ;
         yea.y=yea.y + (hold2*signy);
         
         circlered.x=yea.x;
         circlered.y=yea.y;
         g2d.setColor(Color.YELLOW);
         g2d.fill(circlered);
         g2d.draw(circlered);
        }
                         
        circlered.x=tomp1+horizontal_move;
        circlered.y=tomp2;
        g2d.setColor(Color.YELLOW);
        g2d.fill(circlered);
        g2d.draw(circlered);
     
        
   
}
      
          
          
          
      
          
          
          
          myColorProcess.computedistance(homur1,homur2,(int) circlegps.x, (int) circlegps.y);
          g4d.setColor(Color.MAGENTA);
          g4d.fill(circlegps);
          g4d.draw(circlegps);
          g.drawString(myColorProcess.val, (int) circlegps.x+14,(int) circlegps.y+8);
          g5d.drawLine(homur1,homur2,(int) circlegps.x, (int) circlegps.y);
              
      
      
      
                        }  

                        
                
	               
};
                
    	
		this.canvas.addMouseListener(this);
		this.canvas.addMouseMotionListener(this);
                this.scrollPane = new ScrollPane(ScrollPane.SCROLLBARS_AS_NEEDED);
		this.scrollPane.add(this.canvas);
		add(this.scrollPane, BorderLayout.CENTER);
                            
                
                
                
	
                
          addWindowListener(new WindowAdapter() {
          public void windowClosing(WindowEvent e) {
          dispose(); 
          try {
          myconnect.GpsSocket.close();
          System.out.println("PORT CLOSED");
          }
          catch(IOException a)  {
              a.printStackTrace();
          }
       //   System.exit(0);
       }  
      }
    );
        }
  
        
        
    
    public void mousePressed(MouseEvent e) {
		this.dragStartX = e.getX();
		this.dragStartY = e.getY();
		this.lastX = getX();
		this.lastY = getY();
                this.canvas.repaint();
	}
	
	public void mouseReleased(MouseEvent e) {
	}
	
	public void mouseClicked(MouseEvent e) {
	}
	
	public void mouseEntered(MouseEvent e) {
	}
	
	public void mouseExited(MouseEvent e) {
	}
	
	public void mouseMoved(MouseEvent e) {
	}
	
        
        

        
    public class HelloThread extends Thread {

       
       public void run() {
       
       while(true) {
       
try {
Thread.sleep(10*stoptime); } 
catch (InterruptedException e) {
e.printStackTrace();}

canvas.repaint();   

}
       }
}    
        
        
public class AnotherThread extends Thread {

       
  public void run() {
       
      
   
      
       while(true) {
       
           try {
Thread.sleep(stoptime*3); } 
catch (InterruptedException e) {
e.printStackTrace();}

           
            try {
        myconnect.GpsPort();
        }
        catch(IOException e) {
            e.printStackTrace();
        }
      System.out.println("GIRDI");

           
          try {
          myconnect.process();
        
          GpsDistanceNorth=myconnect.GpsDistanceNorth;
          GpsDistanceEast=myconnect.GpsDistanceEast;
             
          if(myconnect.validData==1   && (GpsDistanceNorth!=0 && GpsDistanceEast!=0) ) {
        
       
          System.out.println(GpsDistanceNorth);
          System.out.println(GpsDistanceEast);
          CalculateDistance.calculate(GpsDistanceNorth,GpsDistanceEast,myconnect.checkmeoutN,myconnect.checkmeoutE,secim);
          System.out.println(CalculateDistance.North);
          System.out.println(CalculateDistance.East);
          circlegps.x=CalculateDistance.East;
          circlegps.y=CalculateDistance.North;
          
          myColorProcess.computedistance(homur1,homur2,(int) circlegps.x, (int) circlegps.y);        
           
          myconnect.validData=0;
      
          }
          else     {
          myColorProcess.computedistance(homur1,homur2,(int) circlegps.x, (int) circlegps.y);        
              
          }
       }catch(IOException e) {
           e.printStackTrace();
       }
           
           
           
           
           
           
           
           
           
           
           
           
           
           
           
           
           
           

}
       }
}
        

        
        
	public void mouseDragged(MouseEvent e) {
		if (e.getX() != this.lastX || e.getY() != this.lastY) {
			Point p = this.scrollPane.getScrollPosition();
			p.translate(this.dragStartX - e.getX(),
		        this.dragStartY - e.getY());
			this.scrollPane.setScrollPosition(p);
		}
	}

        
        
       
                        
        
        public void actionPerformed(ActionEvent e) {
		String command = e.getActionCommand();
                
                if(command==FILE_OPEN_COMMAND) {
                    myflag2=repetation;
                    blackflag=1;
                    
               
                                        
                    currentweather.temprature=currentweather.temprature+30;
                    currentweather.SaturatedVaporDensity(currentweather.temprature);
                    currentweather.currenthumidity();
                   
                    
                    
                    this.canvas.repaint();
                }
                else if(command==STOP) {
                    
                    
                     try {
          myconnect.GpsSocket.close();
          System.out.println("PORT CLOSED");
          }
          catch(IOException a)  {
              a.printStackTrace();
          }
                    
                    
                    myflag2=0;
                }
        
        }
        
         
   


}
	



