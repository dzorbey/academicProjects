
package javaapplication21;

import java.awt.*;
import java.awt.event.*;
import java.awt.geom.*; 
import java.awt.geom.GeneralPath.*;
import java.awt.image.*;
import java.io.*;
import java.net.URL;
import javax.imageio.ImageIO;
import java.applet.Applet;
import java.awt.event.MouseListener;
import javaapplication21.MYPoint;
import static java.lang.Math.*;
import javax.swing.*;







public class Example01 extends Frame {

  
  
    
 
 Image img;
 

 
 

  public Example01(String d1,String f1) {
    
 
 
 
     img = Toolkit.getDefaultToolkit().getImage("C:\\Documents and Settings\\zorbey\\Desktop\\forest.jpg");
 
    
    setSize(600,600);
    
    
    
        
        
        
        
    
    setVisible(true);
    addWindowListener(new WindowAdapter() 
      {public void windowClosing(WindowEvent e) 
         {dispose(); 
       //   System.exit(0);
       }  
      }
    );
  }


  
   
  

  
  public void paint(Graphics g) {
     
  
      
      //Graphics2D deneme = (Graphics2D)g;
      //Graphics2D deneme2 = (Graphics2D)g;
     
      g.drawImage(img,0,0,null);    
     
    }      
  }

