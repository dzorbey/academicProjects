
package javaapplication21;




public class Weather {
    
    
    public double humidity;
    public double temprature;
    public double density;
    public double currenthumidity;
    double tut;
    
    
    public Weather() {
    
    humidity=0;
    temprature=0;
    density=0;
    currenthumidity=0;
    
    }
    
    
    public void SaturatedVaporDensity(double x) {

        
    density=(5.018+0.32321*x)+(8.1847*0.001*x*x)+(3.1243*0.0001*x*x*x);
 //   System.out.println("DENSITY "+ density);
    
    
    }
    
    
     public void InitialVaporDensity() {

     tut=(humidity*density)/100;
     }
    
    
    
    public void currenthumidity() {
        
    currenthumidity=(100*tut)/density;
    }
    
    
    
    
    
    
    
    
}
