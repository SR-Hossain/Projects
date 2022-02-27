import javax.swing.JLayeredPane;
import java.awt.Font;

import javax.swing.JButton;

import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

import javax.swing.ImageIcon;
import javax.swing.JLabel;


public class MainMenu extends JLayeredPane {
    public JLabel setJlabel( JLabel label, int pos, String str, int posX, int posY) {
        label = new JLabel(new ImageIcon(str));
        label.setBounds( posX, posY, label.getPreferredSize().width, label.getPreferredSize().height );
        
        label.setOpaque( false );
        setLayer( label, 50 );

        add( label );

        return label;
    }
    public MainMenu() {
        setSize( 1500, 1000 );
        setJlabel(null, 0, "Resources/Background.png", 0, 0);
        getButton("New Game", 100, 300);
        getButton("Exit", 100, 500);

        setVisible(true);
    }
    public JButton getButton(String buttonStr, int x, int y){
        JButton b = new JButton(buttonStr);
        b.setOpaque(false);
        b.setVisible(true);
        b.setFocusPainted(false);
        b.setFont(new Font("Arial", Font.ITALIC, 60));
        b.setBounds(x,y, 600, 200);
        b.addMouseListener(new ButtonClicker());
        add(b);
        setLayer(b, 100);
        return b;
    }

    public class ButtonClicker implements MouseListener{

        public void mouseClicked(MouseEvent e) {
            JButton b = (JButton)e.getSource();
            String name = b.getText();
            if(name.equals("New Game")){
                getRootPane().setContentPane(new Chess());
            }
            else{
                System.exit(0);
            }

            
        }

        public void mousePressed(MouseEvent e) { } 
        public void mouseReleased(MouseEvent e) { } 
        public void mouseEntered(MouseEvent e) { } 
        public void mouseExited(MouseEvent e) { }

    }



}
