import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Graphics2D;
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

public class Cry extends JFrame{
                        int headNode = 1;
                        int totalnodes = 0;
                        int selectedNode = 1;
                        int totaledges = 0;
                        int node_radius = 80;
                        int layerFocus = 2;
                        Boolean isEditNodeOn = false, isEditEdgeOn = false;
                        JLayeredPane graphLayer;
                        int[][] weightArray = new int[100][100];
                        JLabel graphBg;
                        Graphics2D bg;
                        Graphics BG;

    public void print(String str){System.out.print(str);}
    public void println(String str){System.out.println(str);}
    public static void main(String[] args) {
        new Cry();
    }
                    JButton[] buttonArray = new JButton[100];
                    int howmanybuttons = 0;
                    Node[] nodeArray = new Node[1000];
                    public ImageIcon blueIcon, redIcon;

    public Cry(){
        super("Graph");
        setSize(1200, 800);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);
        setBackground(Color.BLACK);

        for(int i=0; i<100; i++) {for(int j=0; j<100; j++) {weightArray[i][j] = 0;}}

        graphLayer =  new DrawGraph();
        setContentPane(graphLayer);
        
    }

public class DrawGraph extends JLayeredPane implements MouseListener{

   /*     public JLabel drawNewNode(int x, int y, int width, int height, int serial){
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
        } */

        public DrawGraph(){
            super();
            setSize(1200, 800);
            buttonArray[0] = getButton("Edit/Select Nodes", 0, 0);
            buttonArray[1] = getButton("Add Edges", buttonArray[0].getWidth(), 0);
            buttonArray[2] = getButton("Select Head/Root", buttonArray[0].getWidth() + buttonArray[1].getWidth(), 0);
            this.addMouseListener(this);
            
            

            BufferedImage image = new BufferedImage(node_radius, node_radius, BufferedImage.TYPE_INT_ARGB);
            Graphics2D g2d = image.createGraphics();
            g2d.setColor(new Color(34,35,90));
            g2d.fillOval(0, 0, node_radius, node_radius);
            blueIcon = new ImageIcon(image);
            // drawEdges();
            
           




            setVisible(true);


    }

        public void drawEdges(){
            JComponent bg = new JComponent(){
                public void paintComponent(Graphics gg){
                    Graphics2D g = (Graphics2D)gg;
                    g.setColor(Color.ORANGE);
                    g.setStroke(new BasicStroke(5));
                    for(int i=1; i<=totalnodes; i++){
                        for(int j=1; j<=totalnodes; j++){
                            if(weightArray[i][j] != 0){
                                g.drawLine(nodeArray[i].getX()+node_radius/2, nodeArray[i].getY()+node_radius/2, nodeArray[j].getX()+node_radius/2, nodeArray[j].getY()+node_radius/2);
                            }
                        }
                    }
                    g.dispose();
                }
            };
            bg.setBounds(0, 0, 555, 333);
            setLayer(bg, 200);
            this.add(bg);
            bg.setVisible(true);
        }
        public void initNodeArray(int x, int y){
            totalnodes++;
            nodeArray[totalnodes] = new Node(x, y, node_radius);
            setLayer(nodeArray[totalnodes], ++layerFocus);
            add(nodeArray[totalnodes]);
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

        public void paintComponent(Graphics graphics){
            BG = graphics;
            bg = (Graphics2D)graphics;
            bg.setColor(Color.ORANGE);
            bg.setStroke(new BasicStroke(3));

            for(int i=1; i<=totalnodes; i++){
                for(int j=1; j<=totalnodes; j++){
                    if(weightArray[i][j] != 0){
                        bg.drawLine(nodeArray[i].getX()+node_radius/2, nodeArray[i].getY()+node_radius/2, nodeArray[j].getX()+node_radius/2, nodeArray[j].getY()+node_radius/2);
                    }
                }
            }
        }


        



    }
    public void addEdges(int x, int y){
        if(x==y)return;
        weightArray[x][y] = 1;

        repaint();
    }


    public class Node extends JLabel implements MouseListener, MouseMotionListener{
        int posx;
        int posy;
        int size;
        int nodeSerial;

        public Node(int posx, int posy, int size){
            this.posx = posx;
            this.posy = posy;
            this.size = size;
            this.nodeSerial = totalnodes;
            this.addMouseListener(this);
            this.addMouseMotionListener(this);
            setIcon(blueIcon);
            setOpaque(false);
            setBounds(posx-size/2, posy-size/2, size, size);
            setVisible(true);
            setForeground(new Color(23,33,25));
            setFont(new Font("Arial", Font.BOLD, 30));
            setHorizontalTextPosition(JLabel.CENTER);
            setText(Integer.toString(nodeSerial));
            if(nodeSerial==1)setForeground(Color.RED);
        }


        public void mouseClicked(MouseEvent e) {
            if(buttonArray[0].getName() == "on"){
                if(selectedNode != headNode) nodeArray[selectedNode].setForeground(new Color(23,33,25));
                selectedNode = nodeSerial;
                if(selectedNode != headNode) nodeArray[selectedNode].setForeground(Color.ORANGE);
            }
            if(buttonArray[2].getName() == "on"){ // done
                nodeArray[headNode].setForeground(new Color(23,33,25));
                nodeArray[selectedNode].setForeground(new Color(23,33,25));
                selectedNode = headNode = nodeSerial;
                nodeArray[headNode].setForeground(new Color(255,0,0));
            }
            else if(buttonArray[1].getName().equals("on")){
                addEdges(selectedNode, ((Node)e.getSource()).nodeSerial);
            }
        }
        public void mouseDragged(MouseEvent e) {
            if(buttonArray[0].getName().equals("on")){ // done
                setLocation(e.getX() + getX() - size/2, e.getY() + getY() - size/2);
                graphLayer.setLayer((Node)e.getSource(), layerFocus);
                graphLayer.repaint();
            }
        }


        public void mouseMoved(MouseEvent e) {}
        public void mousePressed(MouseEvent e) {
            if(buttonArray[0].getName().equals("on")){
                if(selectedNode != headNode) nodeArray[selectedNode].setForeground(new Color(23,33,25));
                selectedNode = nodeSerial;
                if(selectedNode != headNode) nodeArray[selectedNode].setForeground(Color.ORANGE);
                graphLayer.setLayer((Node)e.getSource(), ++layerFocus);
            }
        }
        public void mouseReleased(MouseEvent e) {}
        public void mouseEntered(MouseEvent e) {}
        public void mouseExited(MouseEvent e) {}

    }
    


}