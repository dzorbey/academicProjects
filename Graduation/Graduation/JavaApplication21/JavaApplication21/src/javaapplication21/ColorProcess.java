

package javaapplication21;


import static java.lang.Math.*;

public class ColorProcess {
    
  
    
    double k,m;
    Wind resultWind;
    public int result;
    public String val;
    
    public ColorProcess() {
        val="";
        resultWind=new Wind();
    }
    
  
    
    
    
    
    public Wind Compute(Wind NorthWest,Wind NorthEast,Wind SouthWest,Wind SouthEast) {
        
       
        
   // System.out.println(NorthWest.Xcoordinate);    
   // System.out.println(NorthEast.Xcoordinate);    
        
   // System.out.println(SouthWest.Xcoordinate);    
   // System.out.println(SouthEast.Xcoordinate);    
    
    
    k=(NorthWest.Xcoordinate+SouthWest.Xcoordinate)-(NorthEast.Xcoordinate+SouthEast.Xcoordinate);
    m=(NorthWest.Ycoordinate+NorthEast.Ycoordinate)-(SouthWest.Ycoordinate+SouthEast.Ycoordinate);
    
    
    resultWind.hypotenus=Math.sqrt((k*k)+(m*m));
    resultWind.k=k;
    resultWind.m=m;
    resultWind.angle=Math.toDegrees(Math.atan(Math.abs(m/k)));
    
    resultWind.finalangle=(resultWind.angle/2);
    
    resultWind.finalspeed=Math.sqrt(   (k*k)+ (m/2)*(m/2) ); 
    
  
    resultWind.realspeed=(resultWind.finalspeed*6)/60;
    
    
    
    //System.out.println("Heyaaaaaaaa" + resultWind.angle);
        //System.out.println(k);
          //  System.out.println(m);
   
    
      
    //System.out.println((resultWind.hypotenus/resultWind.k));
    //System.out.println(resultWind.k);
    
    
    if(k >= 0 && m >= 0) {
        resultWind.desicion=1;
    }
    else if(k >= 0 && m <= 0) {
        resultWind.desicion=2;
    }
    else if(k <= 0 && m <= 0 ){
        resultWind.desicion=3;
    }
    else if(k <= 0 && m >= 0) {
        resultWind.desicion=4;
    }
    else {
        resultWind.desicion=5; 
    }
    
    
    if(m==0) {
        resultWind.hypotenus=0;
    }
    if(k==0) {
        resultWind.hypotenus=0;
        
    }
         return resultWind;
    }
    

    
    public void computedistance(int x1,int y1,int x2, int y2) {
        
    int d=Math.abs(y1-y2);
    int f=Math.abs(x2-x1);
        
    double returndistance= Math.sqrt((d*d)+(f*f));
    result= (int) Math.round(returndistance*6.25);
   
    val = String.valueOf(result);
    
    
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
}
