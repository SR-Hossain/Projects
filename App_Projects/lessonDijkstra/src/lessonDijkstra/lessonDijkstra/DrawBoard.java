package lessonDijkstra;

import javax.swing.JPanel;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.util.ArrayList;
import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Point;

public class DrawBoard extends JPanel implements MouseListener{
        private String str="ami ke";
        private int x1 = 0;
        private int y1 = 0;
        private int x2 = 0;
        private int y2 = 0;
        private boolean drawing = false;
        private ArrayList<Point> points = new ArrayList<Point>();
    public DrawBoard(){

        addMouseListener(this);
    }

    public void paint(Graphics g){
        g.setColor(Color.BLACK);
        g.fillRect(0, 0, 1280, 700);
        g.setColor(Color.orange);
        g.setFont(new Font("serif", Font.BOLD, 20));
        g.drawString(str, 50,50);

        if(points.size()==0)return;
        int i=1;
        x1 = (int) points.get(i-1).getX();
        y1 = (int) points.get(i-1).getY();
        
        g.drawLine(x1, y1, x1, y1);
        drawing = true;

        for(; i<points.size(); i++){
            
            x2 = (int) points.get(i).getX();
            y2 = (int) points.get(i).getY();

            g.drawLine(x2, y2, x2, y2);

            if(x2==x1 && y2==y1){
                drawing = false;
                continue;
            }

            System.out.print(x1 + " " + y1 + " " + x2 + " "+ y2 +"\n");
            if(drawing)
                g.drawLine(x1, y1, x2, y2);
            else drawing = true;
            x1 = x2;
            y1 = y2;

        }
    }

    @Override
    public void mouseClicked(MouseEvent e) {
        // TODO Auto-generated method stub
            // str = "tmi ke";
            // repaint();
        // System.out.print(e.getY()+ " "+e.getX()+" jno\n");
        // repaint();

        
    }

    @Override
    public void mousePressed(MouseEvent e) {
        str = "taraa ke";
        // System.out.print(e.getY()+" "+e.getX()+"\n");
        repaint();
        // TODO Auto-generated method stub
        
    }

    @Override
    public void mouseReleased(MouseEvent e) {
        str = "tmra ke";
        
        points.add(new Point(e.getX(), e.getY()));
        
         
        repaint();
        // TODO Auto-generated method stub
        
    }

    @Override
    public void mouseEntered(MouseEvent e) {
        // TODO Auto-generated method stub
        // System.out.print(e.getY()+ " "+e.getX()+" kjo\n");
        
    }

    @Override
    public void mouseExited(MouseEvent e) {
        // TODO Auto-generated method stub
        
    }
    
}


