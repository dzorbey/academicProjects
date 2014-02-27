



package javaapplication21;

import java.awt.*;
import java.awt.event.*;
import java.awt.image.*;
import java.io.*;
import java.awt.event.MouseListener;
import javax.swing.*;
import javax.imageio.ImageIO;
import java.net.URL;


public class ImageViewer extends Frame implements ActionListener, MouseListener, MouseMotionListener  {
	private static final String FOREST_IMAGE = "FOREST_IMAGE";
	private static final String EXIT_COMMAN = "EXIT_COMMAN";
	private static final String RED_IMAGE = "RED_IMAGE";
        private static final String YELLOW_IMAGE = "YELLOW_IMAGE";
        private static final String SEND_INFO = "SEND_INFO";
        private static final String NWSPEED = "NWSPEED";
        private static final String NWANGLE = "NWANGLE";
        private static final String SWSPEED = "SWSPEED";
        private static final String SWANGLE = "SWANGLE";
        private static final String NESPEED = "NESPEED";
        private static final String NEANGLE = "NEANGLE";
        private static final String SESPEED = "SESPEED";
        private static final String SEANGLE = "SEANGLE";
        private static final String SEND_ME = "SEND_ME";
        private static final String PINE = "PINE";
        private static final String BUSH = "BUSH";
        private static final String OAKEN = "OAKEN";
        private static final String BEECH = "BEECH";
        private static final String TEN_MIN = "TEN_MIN";
        private static final String THIRTY_MIN = "THIRTY_MIN";
        private static final String HOUR = "HOUR";
        private static final String CURRENT_L = "CURRENT_L";
        private static final String CURRENT_F = "CURRENT_F";
        private static final String TEMP = "TEMP";
        private static final String HUMIDITY = "HUMIDITY";
        
        int secim;
        Point pointfire;
        Point pointgps;
        private ScrollPane scrollPane;
	private Canvas canvas;
	private String filename1;
        
	private int dragStartX;
	private int dragStartY;
	private int lastX;
	private int lastY;
        
        
        int time;
        double weight=1;

        
        
         String d1;
         String f1;
         String d;
         String f;
         int cordX;
         int cordY;
        
        Wind NorthEast;
        Wind NorthWest;
        Wind SouthEast;
        Wind SouthWest;
        Wind CompountWind;
        ColorProcess myColorProcess;
        Weather Climate;
        
 public ImageViewer() {
	super("FIRE SIMULATION");
		
        NorthEast=new Wind();
        NorthWest=new Wind();
        SouthEast=new Wind();
        SouthWest=new Wind();
        Climate=new Weather();
        NorthEast.angle=30;
        NorthEast.speed=10;
        NorthWest.angle=30;
        NorthWest.speed=30;
        SouthWest.angle=12;
        SouthWest.speed=0;
        SouthEast.angle=12;
        SouthEast.speed=0;
        pointfire=new Point();
        pointgps=new Point();
        
      
           myColorProcess=new ColorProcess();
           this.canvas = new Canvas() {
			public void update(Graphics g) {
				paint(g);
			}
			
			public Dimension getPreferredSize() {
				return getSize();
			}
           
                       
			public void paint(Graphics g) {
                            
                            
       
                            
                            
                            
                            
                            
				if (filename1 != null) {
					Image img = Toolkit.getDefaultToolkit().getImage(filename1);
                             
                                       
     //                           File outputFile = new File(d1+"eimageForest.png");
                            
       //                       try {
                                 
         //                    ImageIO.write(forest, "PNG", outputFile);
  
// }
// catch(IOException e) {}
  //String filenamekac = outputFile.getAbsolutePath();
                                        
   //img = Toolkit.getDefaultToolkit().getImage(filenamekac);
   
   
					if (img != null) {
						g.drawImage(img, 0, 0, this);
						int width = img.getWidth(this);
						int height = img.getHeight(this);
						if (width != -1 && width != getWidth()) {
							setSize(width, getHeight());
						}
						if (height != -1 && height != getHeight()) {
							setSize(getWidth(), height);
						}
					} else {
						final Dialog d = new Dialog(ImageViewer.this);
						d.add(new Label("Faild to load " + filename1));
						Button b = new Button("OK");
						b.addActionListener(new ActionListener() {
							public void actionPerformed(ActionEvent e) {
								d.dispose();
							}
						});
						d.setModal(true);
						d.setVisible(true);
					}
				} else {
					g.setColor(new Color(0, 100, 200));
					g.fillRect(0, 0, getWidth(), getHeight());
				}
			}
			
                
		};
		
		this.canvas.addMouseListener(this);
		this.canvas.addMouseMotionListener(this);
		
		this.scrollPane = new ScrollPane(ScrollPane.SCROLLBARS_AS_NEEDED);
		this.scrollPane.add(this.canvas);
		
		add(this.scrollPane, BorderLayout.CENTER);

		MenuBar menuBar = new MenuBar();
		Menu menu = new Menu("Image");
		menu.addActionListener(this);
                
           
		Menu mymenu = new Menu("Weather");
		mymenu.addActionListener(this);
                
                Menu mymenu2=new Menu("Plant");
                mymenu2.addActionListener(this);
                
                
                
                Menu submitmenu= new Menu("Submit");
                submitmenu.addActionListener(this);
                
                Menu timeinterval=new Menu("Time");
                timeinterval.addActionListener(this);
                
                
                
                MenuItem cx= new MenuItem("Send Data");
                cx.setActionCommand(SEND_ME);
                submitmenu.add(cx);
                
                
                
                cx=new MenuItem("Current Location");
                cx.setActionCommand(CURRENT_L);
                submitmenu.add(cx);
                
                cx=new MenuItem("Fire Point");
                cx.setActionCommand(CURRENT_F);
                submitmenu.add(cx);
                
                
		
                Menu submenu1= new Menu("NorthWest");
                submenu1.addActionListener(this);
                
                    MenuItem NW=new MenuItem("Angle");
                    NW.setActionCommand(NWANGLE);
                    submenu1.add(NW);                   
                    MenuItem NW2=new MenuItem("Speed");
                    
                    NW2.setActionCommand(NWSPEED);
                    submenu1.add(NW2);
                mymenu.add(submenu1);    
                    
                
                
              
                
                Menu submenu2= new Menu("NorthEast");
                submenu2.addActionListener(this);
                
                    MenuItem NE=new MenuItem("Angle");
                    NE.setActionCommand(NEANGLE);
                    submenu2.add(NE);
                    NE=new MenuItem("Speed");
                    NE.setActionCommand(NESPEED);
                    submenu2.add(NE);
                    mymenu.add(submenu2);    
                
                
                
                Menu submenu3= new Menu("SouthWest");
                submenu3.addActionListener(this);
                
                    MenuItem SW=new MenuItem("Angle");
                    SW.setActionCommand(SWANGLE);
                    submenu3.add(SW);
                    SW=new MenuItem("Speed");
                    SW.setActionCommand(SWSPEED);
                    submenu3.add(SW);
                mymenu.add(submenu3);    
                
         
                Menu submenu4= new Menu("SouthEast");
                submenu4.addActionListener(this);
                
                    MenuItem SE=new MenuItem("Angle");
                    SE.setActionCommand(SEANGLE);
                    submenu4.add(SE);
                    SE=new MenuItem("Speed");
                    SE.setActionCommand(SESPEED);
                    submenu4.add(SE);
                mymenu.add(submenu4);    
                
                
                 Menu submenu5= new Menu("Temp/Humidity");
                submenu5.addActionListener(this);
                
                    MenuItem ka=new MenuItem("Temprature");
                    ka.setActionCommand(TEMP);
                    submenu5.add(ka);
                    ka=new MenuItem("Humidity");
                    ka.setActionCommand(HUMIDITY);
                    submenu5.add(ka);
                mymenu.add(submenu5);   
                
                
                
                
		MenuItem mi = new MenuItem("Open Forest Image");
		mi.setActionCommand(FOREST_IMAGE);
		menu.add(mi);
                menu.addSeparator();
                
                mi=new MenuItem("s/10-min");
                mi.setActionCommand(TEN_MIN);
                timeinterval.add(mi);
                
                mi=new MenuItem("s/30-min");
                mi.setActionCommand(THIRTY_MIN);
                timeinterval.add(mi);
                
                mi=new MenuItem("s/hour");
                mi.setActionCommand(HOUR);
                timeinterval.add(mi);
                
		
		mi = new MenuItem("Exit");
		mi.setActionCommand(EXIT_COMMAN);
		menu.add(mi);
                
                
                mi=new MenuItem("Pine");
                mi.setActionCommand(PINE);
                mymenu2.add(mi);
                
                mi=new MenuItem("Bush");
                mi.setActionCommand(BUSH);
                mymenu2.add(mi);
                
                mi=new MenuItem("Oaken");
                mi.setActionCommand(OAKEN);
                mymenu2.add(mi);
                
                
                mi=new MenuItem("Beech");
                mi.setActionCommand(BEECH);
                mymenu2.add(mi);
                
                
		
		menuBar.add(menu);
                menuBar.add(mymenu);
                menuBar.add(mymenu2);
                menuBar.add(submitmenu);
		menuBar.add(timeinterval);
                
		setMenuBar(menuBar);
	}
	
        
        
                
        
        
	public void actionPerformed(ActionEvent e) {
		String command = e.getActionCommand();
                
                FileDialog dialog = new FileDialog(this, "Open file", FileDialog.LOAD);
                
                
                
		if (FOREST_IMAGE == command) {
			dialog.setVisible(true);
			d1 = dialog.getDirectory();
                        
			f1 = dialog.getFile();
			System.out.println(d1+f1);
                        if (d1 != null && f1 != null) {
				File file = new File(d1, f1);
				this.filename1 = file.getAbsolutePath();
                               // img_forest = Toolkit.getDefaultToolkit().getImage(filename1);
				System.out.println(getWidth());
                                //setSize(getWidth(),getHeight());
                                this.canvas.repaint();
			}
                }
                else if (EXIT_COMMAN == command) {	
                    System.exit(0);
                        
		}
                
                else if(TEMP == command) {
                JOptionPane pane = new JOptionPane("Temprature/Celcius");
                String s = (String)pane.showInputDialog(new JFrame(),
                "ENTER\n","Temprature/C",JOptionPane.PLAIN_MESSAGE);
                Climate.temprature=Double.valueOf(s);
                Climate.SaturatedVaporDensity(Climate.temprature);
                }
                else if(HUMIDITY == command) {
                JOptionPane pane = new JOptionPane("Humidity/%Percantage");
                String s = (String)pane.showInputDialog(new JFrame(),
                "ENTER\n","% Humidity",JOptionPane.PLAIN_MESSAGE);
                Climate.humidity=Double.valueOf(s);
                Climate.InitialVaporDensity();
                }
                
                else if(NWSPEED == command) {
                JOptionPane pane = new JOptionPane("SPEED");
                String s = (String)pane.showInputDialog(new JFrame(),
                "ENTER\n","NORTHWEST SPEED",JOptionPane.PLAIN_MESSAGE);
                NorthWest.speed=Double.valueOf(s);
                }
                else if(NWANGLE == command) {
                JOptionPane pane = new JOptionPane("SPEED");
                String s = (String)pane.showInputDialog(new JFrame(),
                "ENTER\n","NORTHWEST ANGLE",JOptionPane.PLAIN_MESSAGE);
                NorthWest.angle=Double.valueOf(s);
                }
                else if(NESPEED == command) {
                JOptionPane pane = new JOptionPane("SPEED");
                String s = (String)pane.showInputDialog(new JFrame(),
                "ENTER\n","NORTHEAST SPEED",JOptionPane.PLAIN_MESSAGE);
                NorthEast.speed=Double.valueOf(s);
                }
                else if(NEANGLE == command) {
                JOptionPane pane = new JOptionPane("SPEED");
                String s = (String)pane.showInputDialog(new JFrame(),
                "ENTER\n","NORTHEAST ANGLE",JOptionPane.PLAIN_MESSAGE);
                NorthEast.angle=Double.valueOf(s);
                }
                else if(SWSPEED == command) {
                JOptionPane pane = new JOptionPane("SPEED");
                String s = (String)pane.showInputDialog(new JFrame(),
                "ENTER\n","SOUTHWEST SPEED",JOptionPane.PLAIN_MESSAGE);
                SouthWest.speed=Double.valueOf(s);
                }
                else if(SWANGLE == command) {
                JOptionPane pane = new JOptionPane("SPEED");
                String s = (String)pane.showInputDialog(new JFrame(),
                "ENTER\n","SOUTHWEST ANGLE",JOptionPane.PLAIN_MESSAGE);
                SouthWest.angle=Double.valueOf(s);
                }
                else if(SESPEED == command) {
                JOptionPane pane = new JOptionPane("SPEED");
                String s = (String)pane.showInputDialog(new JFrame(),
                "ENTER\n","SOUTHEAST SPEED",JOptionPane.PLAIN_MESSAGE);
                SouthEast.speed=Double.valueOf(s);
                }
                else if(SEANGLE == command) {
                JOptionPane pane = new JOptionPane("SPEED");
                String s = (String)pane.showInputDialog(new JFrame(),
                "ENTER\n","SOUTHEAST ANGLE",JOptionPane.PLAIN_MESSAGE);
                SouthEast.angle=Double.valueOf(s);
                }
                else if(TEN_MIN==command) {
                 
                NorthWest.Xcoordinate=(NorthWest.speed)*Math.cos(Math.toRadians(NorthWest.angle));
                NorthWest.Ycoordinate=(NorthWest.speed)*Math.sin(Math.toRadians(NorthWest.angle));
                NorthEast.Xcoordinate=(NorthEast.speed)*Math.cos(Math.toRadians(NorthEast.angle));
                NorthEast.Ycoordinate=(NorthEast.speed)*Math.sin(Math.toRadians(NorthEast.angle));
                SouthWest.Xcoordinate=(SouthWest.speed)*Math.cos(Math.toRadians(SouthWest.angle));
                SouthWest.Ycoordinate=(SouthWest.speed)*Math.sin(Math.toRadians(SouthWest.angle));
                SouthEast.Xcoordinate=(SouthEast.speed)*Math.cos(Math.toRadians(SouthEast.angle));
                SouthEast.Ycoordinate=(SouthEast.speed)*Math.sin(Math.toRadians(SouthEast.angle));
                CompountWind=myColorProcess.Compute(NorthWest,NorthEast,SouthWest,SouthEast);
                
               // Climate.SaturatedVaporDensity()
                
                
                System.out.println(CompountWind.realspeed);
                CompountWind.realspeed=CompountWind.realspeed*weight;
                double meter_per_second=(CompountWind.realspeed*1000)/3600;
                double meter_per_10min=600*meter_per_second;
                time=(int) Math.round( (meter_per_10min)/ 9);
                System.out.println(time);
                }else if(THIRTY_MIN==command) {
                    
                NorthWest.Xcoordinate=(NorthWest.speed)*Math.cos(Math.toRadians(NorthWest.angle));
                NorthWest.Ycoordinate=(NorthWest.speed)*Math.sin(Math.toRadians(NorthWest.angle));
                NorthEast.Xcoordinate=(NorthEast.speed)*Math.cos(Math.toRadians(NorthEast.angle));
                NorthEast.Ycoordinate=(NorthEast.speed)*Math.sin(Math.toRadians(NorthEast.angle));
                SouthWest.Xcoordinate=(SouthWest.speed)*Math.cos(Math.toRadians(SouthWest.angle));
                SouthWest.Ycoordinate=(SouthWest.speed)*Math.sin(Math.toRadians(SouthWest.angle));
                SouthEast.Xcoordinate=(SouthEast.speed)*Math.cos(Math.toRadians(SouthEast.angle));
                SouthEast.Ycoordinate=(SouthEast.speed)*Math.sin(Math.toRadians(SouthEast.angle));
                CompountWind=myColorProcess.Compute(NorthWest,NorthEast,SouthWest,SouthEast);          
                System.out.println(CompountWind.realspeed);
                CompountWind.realspeed=CompountWind.realspeed*weight;
                double meter_per_second=(CompountWind.realspeed*1000)/3600;
                double meter_per_30min=1800*meter_per_second;
                time=(int) Math.round( (meter_per_30min)/ 9 );
                }else if(SEND_ME == command) {
                    
                int i=0;    
                Example02 viewer1 = new Example02(filename1,CompountWind,time,pointfire,pointgps,Climate,secim);
	        viewer1.pack();
                viewer1.setVisible(true);
                }
                else if(BUSH== command) {
                    secim=1;   
                    weight=1.5;
                }
                else if(PINE == command) {
                    weight=1;
                    secim=0;
                }
                else if(CURRENT_F == command) {
                    pointfire.x=cordX;
                    pointfire.y=cordY;
                }
                else if( CURRENT_L == command) {
                    pointgps.x=cordX;
                    pointgps.y=cordY;
                }
        
}
	
	public void mousePressed(MouseEvent e) {
		this.dragStartX = e.getX();
		this.dragStartY = e.getY();
		this.lastX = getX();
		this.lastY = getY();
	}
	
	public void mouseReleased(MouseEvent e) {
	}
	
	public void mouseClicked(MouseEvent e) {
            
          cordX=e.getX();
          cordY=e.getY();
          System.out.println(cordX + "," +cordY);
        }
	
	public void mouseEntered(MouseEvent e) {
	}
	
	public void mouseExited(MouseEvent e) {
	}
	
	public void mouseMoved(MouseEvent e) {
	}
	
        
        
        
        
        
        
        
   
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
	public void mouseDragged(MouseEvent e) {
		if (e.getX() != this.lastX || e.getY() != this.lastY) {
			Point p = this.scrollPane.getScrollPosition();
			p.translate(this.dragStartX - e.getX(),
						this.dragStartY - e.getY());
			this.scrollPane.setScrollPosition(p);
		}
	}
	
}