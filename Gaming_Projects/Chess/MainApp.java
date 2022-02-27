import javax.swing.JFrame;



public class MainApp extends JFrame{
    public static void main(String[] args) {
        new MainApp();
    }
    public MainApp() {
        super( "Chess" );
        setSize( 1500, 1000 );
        setDefaultCloseOperation( EXIT_ON_CLOSE );
        setVisible(true);
        setContentPane(new MainMenu());
        
    }
 


    
}
