
package GPS;



import java.io.*;
import java.net.*;
import java.util.StringTokenizer;


public class PortConnect {
    
        public Socket GpsSocket;
	private PrintWriter out;
	private BufferedReader in;
        public String Sentence;
    
        private int ready=0;
        int tmp;
        public int checkmeoutN;
        public int checkmeoutE;
        
        String tmp2;
        String N,E;
        public double GpsDistanceNorth=0;
        public double GpsDistanceEast=0;
        public int validData=0;
        DataSeperator newS;
        String oldsentence;
    
    
   
    public PortConnect() {
   
     GpsSocket=null;
     newS=new DataSeperator();
    
    
    }
   
    
    
    
    
    public void GpsPort() throws IOException {
            GpsSocket = new Socket("",   20175);
            out = new PrintWriter(GpsSocket.getOutputStream(), true);
            in = new BufferedReader(new InputStreamReader(GpsSocket.getInputStream()));  
      
          
    }  

    
    
    public void process() throws IOException {
    
    oldsentence=Sentence;    
    Sentence=in.readLine();
    
    if(oldsentence!=Sentence) {
        System.out.println("FARKLI GELDIII");
    }
    
    System.out.println(Sentence);
    
  
   
    if(newS.isValidData(Sentence)) {
        newS.seperate(Sentence);
    
    
    GpsDistanceNorth=newS.GpsDistanceNorthclass;
    GpsDistanceEast=newS.GpsDistanceEastclass;
    checkmeoutN=newS.checkoutN;
    checkmeoutE=newS.checkoutE;
    validData=1;
    }
    
   
       GpsSocket.close(); 
        
        
        
    } 
    
    
    
    
    
    
    
    
    
    
}
