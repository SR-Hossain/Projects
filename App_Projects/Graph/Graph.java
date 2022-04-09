import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.geom.*;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
/*
    buttonArray[0]->Edit Node
    buttonArray[1]->Edit Edge
*/
import java.awt.image.BufferedImage;


import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JComponent;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JLayeredPane;

public class Graph extends JFrame{
                        int headNode = 1;
                        int totalnodes = 0;
                        int totaledges = 0;
                        int node_radius = 80;
                        int layerFocus = 2;
                        JLabel[] nodeArray = new JLabel[1000];
                        Boolean isEditNodeOn = false, isEditEdgeOn = false;

    public void print(String str){System.out.print(str);}
    public void println(String str){System.out.println(str);}
    public static void main(String[] args) {
        new Graph();
    }
    public Graph(){
        super("Graph");
        setSize(1200, 800);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);
        setBackground(Color.BLACK);
        setContentPane(new DrawGraph());
        
    }

public class DrawGraph extends JLayeredPane implements MouseListener{
        public JLabel drawNewNode(int x, int y, int width, int height, int serial){
            BufferedImage node = new BufferedImage(width, height, BufferedImage.TYPE_INT_ARGB);
            Graphics2D g2d = node.createGraphics();
            


            JLabel label = new JLabel(new ImageIcon(node));
            // g2d.dispose();
            
            g2d.setFont(new Font("TimesRoman", Font.PLAIN, 50));
            g2d.setColor(new Color(34,45,90));
            g2d.fillOval(0, 0, width, height);
            if(serial == headNode) g2d.setColor(Color.RED);
            else g2d.setColor(new Color(23,33,25));
            g2d.drawString(serial+"", (int)(width/2-15.*Math.ceil(Math.log10(serial+1))), height/2+15);
            // label.setText(new Font("TimesRoman", Font.PLAIN, 50).getFontName());
            label.setName(serial+"");
            label.setBounds(x, y, width, height);
            label.setOpaque( false );
            label.setFocusable(true);
            label.addMouseListener(new MouseListener() {
                public void mouseClicked(MouseEvent e) {
                    if(buttonArray[2].getName().equals("on")){
                        
                        int prevNode = headNode;

                        headNode = 0;
                        for(int i=0; i<label.getName().length(); i++) 
                            headNode = headNode*10 + (label.getName().charAt(i)-'0');

                        if(prevNode == headNode){
                            return;
                        }
                        

                        int xx = nodeArray[prevNode].getX();
                        int yy = nodeArray[prevNode].getY();
                        
                        remove(nodeArray[prevNode]);
                        nodeArray[prevNode] = drawNewNode(xx, yy, node_radius, node_radius, prevNode);




                        remove(nodeArray[headNode]);
                        nodeArray[headNode] = drawNewNode(nodeArray[headNode].getX(), nodeArray[headNode].getY(), node_radius, node_radius, headNode);
                        
                    }

                }
                public void mousePressed(MouseEvent e) {
                    setLayer(label, ++layerFocus);
                }
                public void mouseReleased(MouseEvent e) {}
                public void mouseEntered(MouseEvent e) {}
                public void mouseExited(MouseEvent e) {}
                
            });
            label.addMouseMotionListener(new MouseMotionListener(){
                public void mouseDragged(MouseEvent e) {
                    if(buttonArray[0].getName().equals("off"))return;
                    label.setLocation(e.getX() + label.getX() - 25, e.getY() + label.getY() - 25);

                }
                public void mouseMoved(MouseEvent e) {}
            });
            add(label);
            setLayer(label, layerFocus++);

            return label;
        }
        JButton[] buttonArray = new JButton[100];
        int howmanybuttons = 0;
        public DrawGraph(){
            super();
            setSize(1200, 800);
            buttonArray[0] = getButton("Edit Nodes", 0, 0);
            buttonArray[1] = getButton("Edit Edges", buttonArray[0].getWidth(), 0);
            buttonArray[2] = getButton("Select Head/Root", buttonArray[0].getWidth() + buttonArray[1].getWidth(), 0);
            initNodeArray(100, 200);
            initNodeArray(400, 600);
            this.addMouseListener(this);
            
            setVisible(true);


            BufferedImage node = new BufferedImage(300, 400, BufferedImage.TYPE_INT_ARGB);
            Graphics2D g2d = node.createGraphics();
            g2d.setColor(new Color(34,45,90));
            g2d.drawLine(0,0,300,400);
            

            


            JLabel label = new JLabel(new ImageIcon(node));
            label.setOpaque(false);
            label.setBounds(0, 0, 300, 400);
            add(label);


            setLayer(label, 55);

            
            

            JComponent comp = new JComponent(){
                public void paintComponent(Graphics g){
                    Graphics2D gg = (Graphics2D) g;
                    gg.setColor(Color.RED);
                    gg.setStroke(new BasicStroke(10));
                    gg.drawLine(0,0,300,400);
                }
            };
        comp.addMouseListener(new MouseListener(){

            @Override
            public void mouseClicked(MouseEvent e) {
                println("ami bonoful go\n\n");
                
            }

            @Override
            public void mousePressed(MouseEvent e) {
                // TODO Auto-generated method stub
                
            }

            @Override
            public void mouseReleased(MouseEvent e) {
                // TODO Auto-generated method stub
                
            }

            @Override
            public void mouseEntered(MouseEvent e) {
                // TODO Auto-generated method stub
                
            }

            @Override
            public void mouseExited(MouseEvent e) {
                // TODO Auto-generated method stub
                
            }

        });
        comp.setBounds(0,0,300,400);
        comp.setOpaque(false);
        setLayer(comp, 1000);
        comp.setVisible(true);
        comp.setLocation(200,300);

        add(comp);
    }
        public void initNodeArray(int x, int y){
            totalnodes++;
            nodeArray[totalnodes] = drawNewNode(x, y, node_radius, node_radius, totalnodes);
        }
        public void removeNodeArray(int whichNode){
            remove(nodeArray[whichNode]);
            nodeArray[whichNode] = null;
            for(int i=whichNode; i<totalnodes; i++)
                nodeArray[i] = nodeArray[i+1];///////////////
        }
        public JButton getButton(String buttonStr, int x, int y){
            JButton b = new JButton(buttonStr);
            b.setOpaque(false);
            b.setFocusPainted(false);
            b.setFont(new Font("Arial", Font.ITALIC, 20));
            b.setForeground(Color.GRAY);
            b.setBounds(x,y,b.getPreferredSize().width, b.getPreferredSize().height);
            b.setContentAreaFilled(false);
            howmanybuttons++;
            b.setName("off");
            add(b);
            setLayer(b, 1000);
            b.setVisible(true);
            b.addMouseListener(new MouseListener() {
                public void mouseClicked(MouseEvent e) {
                    b.setName(b.getName().equals("off")?"doom":"off");
                    for(int i=0; i<howmanybuttons; i++){
                        if(buttonArray[i].getName().equals("doom"))continue;
                        buttonArray[i].setForeground(Color.GRAY); buttonArray[i].setName("off");
                    }
                    if(b.getName().equals("doom")) b.setName("on");
                    b.setForeground(b.getName().equals("on")?Color.WHITE:Color.GRAY);

                }
                public void mousePressed(MouseEvent e) {}
                public void mouseReleased(MouseEvent e) {}
                public void mouseEntered(MouseEvent e) {}
                public void mouseExited(MouseEvent e) {}
            });
            return b;
        }
        @Override
        public void mouseClicked(MouseEvent e) {
            if(buttonArray[0].getName() == "off")return;

            println(e.getX() + " " + e.getY());
            initNodeArray(e.getX()-25, e.getY()-25);
        }
        public void mousePressed(MouseEvent e) {}
        public void mouseReleased(MouseEvent e) {}
        public void mouseEntered(MouseEvent e) {}
        public void mouseExited(MouseEvent e) {}
    
    }

    public void addNewEdges(){
        
    }
    public void drawEdges(){

    }

}