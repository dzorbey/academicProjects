

package GPS;


import java.util.StringTokenizer;





public class GpsDataTokenizer {

	private String dataToPArse=null;
	private String[] parsedArray;
	private int lengthOfArray=0;
	private int MINIMUMVALIDTOKENNUMBER=10;
	private double latitude  = 0 ; //default
	private double longitude = 0 ;
	/**
	 * Constructs an object having GPS information data string set.
	 * @param theData GPS sentences sent from GPS gate's port listener .
	 */	
	public GpsDataTokenizer(String theData){
		dataToPArse=theData;
		parsedArray = new String[15]; //ENOUGH FOR GPGGA DATA
	}
	public String NullReturn (String token){
		if(token.equals(null)){
			return "null";
		}else{
			return token;
		}
	}
	/**
	 * This method is used to fill the array of latitude and longitude if the GPS sentence is GPGGA sentence.
	 * @return True if this is a valid array with minimum required information and returns false in contrast.
	 */	
	public boolean fillArray(){
		StringTokenizer st = new StringTokenizer(dataToPArse,"$,");
		int dataCounter=-1;
		if(st.nextToken().equals("GPGGA")){
			lengthOfArray = 0;
			while(st.hasMoreTokens()){
				dataCounter++;

				parsedArray[dataCounter]=st.nextToken();
				lengthOfArray=lengthOfArray+1;
					if(lengthOfArray > MINIMUMVALIDTOKENNUMBER){
						latitude = Double.parseDouble(parsedArray[1]);
						longitude =Double.parseDouble(parsedArray[3]);
					}
			}
			return true;
		}else{
			return false;
		}
	}
	/**
	 * This method's function is checking if the evaluated GPS data is valid by checking tokens in array. 
	 * @return True if the information is valid.
	 */
	public boolean isValidData(){
		if(lengthOfArray > MINIMUMVALIDTOKENNUMBER){
			System.out.println("This is a valid GPS data");
			
			return true;
		}else{
			System.out.println("This is not a valid GPS data");
			
			return false;
		}
		
	}
	/**
	 * This is a mutator function to set the GPS data for parsing. 
	 * @param newData The GPGGA sentence which includes latitude and longitude .
	 */	
	public void setDataToParse(String newData){
		this.dataToPArse=newData;
	}
	/**
	 * This is an access function to get the data which is subject to a parsing process. 
	 * @return Data that is subject to parsing process.
	 */	
	public String getDataToParse(){
		return dataToPArse;
	}
	/*public void print(){
		System.out.println(getLatitude() +": N");
		System.out.println(getLongitude() +": E");
		//Double x =getLatitude();
		//System.out.println(x.toString().substring(0,2));
	}*/
	/**
	 * This is an access function to get latitude .
	 * @return The latitude
	 */	
	public double getLatitude(){
		System.out.println("THE LATITUDE IS :" + latitude);
		return convertToDegreeMinuteSecond(latitude);
	}
	/**
	 * This is an access function to get longitude .
	 * @return The longitude
	 */	
	public double getLongitude(){
		System.out.println("THE LONGITUDE IS :" + longitude);		
		return convertToDegreeMinuteSecond(longitude);
	}
	/**
	 * This method is a formatter used to convert the given number into general degree,minute,second format.
	 * @param data Data is a double value and it is subject to a change into degree,minute,second format.
	 * @return Degree,minute,second format of data
	 */	
	public double convertToDegreeMinuteSecond(double data){
		Double theData=data;
		Integer degreeMinute ; 
		Double second;	
		StringTokenizer gpsDataTokenizer = new StringTokenizer(theData.toString(),".");
		
		degreeMinute=Integer.parseInt(gpsDataTokenizer.nextToken());
		second=Double.parseDouble(".".concat(gpsDataTokenizer.nextToken()));
		second=second *  60 ;
		
		gpsDataTokenizer = new StringTokenizer(second.toString(),".");
		
		String theRealData="";
		
		if(gpsDataTokenizer.nextToken().length()==1){
			theRealData=degreeMinute.toString()+"0"+second.toString();
		}else{
			theRealData=degreeMinute.toString()+second.toString();
		}
		//System.out.println(theRealData);		
		
		return Double.parseDouble(theRealData);
	}
		public static void main (String[] args){
			//GpsDataTokenizer parser = new GpsDataTokenizer("$GPGGA,040502.37,4059.02464,N,02905.416139,E,1,03,10.0,152.0,M,-1.728011,M,-0.62705,*7C");
			GpsDataTokenizer parser = new GpsDataTokenizer("$GPGGA,162324.49,4058.338207,N,02908.991472,E,1,04,5.0,180.0,M,0.0001999,M,0.00906,*77");
			//7tepe data
			parser.fillArray();
			System.out.println(parser.getLatitude());
			System.out.println(parser.getLongitude());
				
		}
	
}
