


import javax.swing.JFrame;

public class Main{
    public static void main(String[] args) {
        
        

        JFrame obj = new JFrame();
        // GamePlay gamePlay = new GamePlay();
        DrawBoard gamePlay = new DrawBoard();



        obj.setBounds(100,100,1080,720);
        obj.setVisible(true);
        obj.setTitle("Dijkstra");
        obj.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        // obj.add(gamePlay);
        obj.add(gamePlay);
    
    }
}
