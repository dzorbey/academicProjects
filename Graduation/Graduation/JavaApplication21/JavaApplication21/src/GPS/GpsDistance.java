

package GPS;


public class GpsDistance {
    
 
  public int oldNorth;
  public int oldEast;
  public int North;
  public int East;
  
 
  int arttir;
  int arttir2;
  
          
    public GpsDistance() {
    }
  
    
    public void calculate(double NewN,double NewE,int checkoutNorth,int checkoutEast,int secim) {
        
      //oldNorth= (int) Math.round(NewN);
      //oldEast = (int) Math.round(NewE);
        
      if(secim==1) {  
        
      NewN=60-NewN;  
      arttir=((4059-checkoutNorth)-1)*60;   
      NewN=NewN+arttir;  
        
      
      arttir2=(checkoutEast-2908)*60;   
      NewE=NewE+arttir2; 
      
       North= (int) Math.round((NewN/120)*596);
       East=  (int) Math.round((NewE/180)*708);
      
      
      }
      else if(secim==0) {
          
      NewN=60-NewN;  
      arttir=((4059-checkoutNorth)-1)*60;   
      NewN=NewN+arttir;  
        
      
      arttir2=(checkoutEast-2903)*60;   
      NewE=NewE+arttir2; 
       
      
        
        North= (int) Math.round((NewN/40)*596);
        East=  (int) Math.round((NewE/65)*708);
      }
       
    }
    
    
    
    
}
