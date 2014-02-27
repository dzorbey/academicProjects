

package GPS;

import java.util.StringTokenizer;

public class DataSeperator {
    
   
    String tmp2;
    int tmp=0;
    int tmppo=0;
    int tmpp=0;
    
    int checkout;
    public int checkoutN;
    public int checkoutE;
    
    
    
    double North;
    double East;
    String N;
    String E;
    String StringToParse;
    StringTokenizer st;
    public double GpsDistanceNorthclass=0;
    public double GpsDistanceEastclass=0;
    
    
    public DataSeperator() {
   
      
    }
    
    

    
    
    public void seperate(String Sentence) {
      StringToParse=Sentence;  
      st = new StringTokenizer(StringToParse,"$,");
   
        StringTokenizer myoo = new StringTokenizer(StringToParse,"$,");
        StringTokenizer dene = new StringTokenizer(StringToParse,"$,");
        
      
       
            
      
   while(st.hasMoreTokens()) {
       tmp2=st.nextToken();
       if(tmp==2) {
           N=tmp2;
       }
       if(tmp==4) {
           E=tmp2;
       }
       tmp++;
       
       
       
   }
       
    
      //else if(tmppo==11) { 
            
            
            
        //     while(st.hasMoreTokens()) {
       //tmp2=st.nextToken();
       //if(tmp==3) {
     //      N=tmp2;
       //}
    //   if(tmp==5) {
      //     E=tmp2;
     //  }
     //  tmp++;
  // }
            
            
            
           
        
   North=Double.parseDouble(N);
   East=Double.parseDouble(E);
  //System.out.println("Latitude:   " + North);
  //System.out.println("Longtitude: " + East); 
  
  //System.out.println("North seconds: " + GpsSeconds(North));
  GpsDistanceNorthclass=GpsSeconds(North);
  checkoutN=checkout;
  //System.out.println("East seconds: " + GpsSeconds(East));
  GpsDistanceEastclass=GpsSeconds(East);
  checkoutE=checkout;
        tmp=0;
    } 
    
    
    public boolean isValidData(String Sentence){
        StringToParse=Sentence;
        
        
        StringTokenizer my = new StringTokenizer(StringToParse,"$,");
        StringTokenizer myo = new StringTokenizer(StringToParse,"$,");
        
        
        
         while(my.hasMoreTokens()) {
         my.nextToken();
         tmpp++;
         }
        
        
      
        
              if(tmpp >10 && myo.nextToken().equals("GPGGA")){
            
            
                    tmpp=0;
                    System.out.println("VALID GPS data");
		    return true;
             
                 }
                 else{
                 //tmpp=0;
                 System.out.println("NOOO GPS data");		
	         return false;}
        }
    
    
    
    
    
    public double GpsSeconds(double coordinate) {
        
                Double temp=coordinate;
		Integer degreeMinute ; 
		Double second;	
		StringTokenizer gpsDataTokenizer = new StringTokenizer(temp.toString(),".");
		
		degreeMinute=Integer.parseInt(gpsDataTokenizer.nextToken());
                checkout=degreeMinute;
		second=Double.parseDouble(".".concat(gpsDataTokenizer.nextToken()));
		second=second *  60 ;
		
                System.out.println("DEGREE DEGERI" + checkout);
                return second;
        
        
        
    }
    
    
  }
