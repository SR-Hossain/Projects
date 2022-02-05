import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import java.io.File;
import java.util.Scanner;


import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JLayeredPane;
import javax.swing.SwingUtilities;

public class Chess extends JFrame{

    private JLayeredPane content;

    int[] prime = {3, 5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131, 137};
    public String firstplayer = "black", initposStr;
    public Rectangle[][] board = new Rectangle[10][10];
    public int focus = 20, prevRow, prevCol, newRow, newCol, whitemoves, blackmoves;
    public Boolean isDragging = false, whiteturn;
    int cur_row; int cur_col, wag = 0, totalMoves = 0, voldemort = 1;
    public char king = 'K';
    JLabel bg;

    public void takeString(){
        try{
            Scanner sc = new Scanner(new File("Resources/initPosString.txt"));
            initposStr = sc.nextLine(); sc.close();
            } catch (Exception e){ System.out.println("Piece data input error"); }
    }


    public static void main(String[] args) {
        new Chess();
    }
    public Chess() {
        super( "Chess" );
        takeString();
        firstplayer = "black";
        whitemoves = blackmoves = 0;
        whiteturn = true;
        content = new JLayeredPane();
        content.setOpaque( true );
        setContentPane( content );
        setSize( 1500, 1000 );
        setDefaultCloseOperation( EXIT_ON_CLOSE );
        setRectangle();

        // Background
        if(firstplayer == "white")
        bg = this.setJlabel(null, 0, "Resources/white.png", 0, 0);
        else bg = this.setJlabel(null, 0, "Resources/black.png", 0, 0);

        setVisible(true);

        refreshBoard();
    
    }
    /*
        jar turn, tar raja ki check e ache kina ta dekha lagbe
        so suppose white ekhn chaal dibe,
            tahole black er shob guti gulor moves count kora lagbe (check)
            
            then white er guti gular kongula moves dite parbe ta count kora lagbe

        mane shob e count kora lagbe


        jar moves 0, tar upor press korle kichu hobe na
        jar moves ache, se jdi thik jaygay release hoy tahole move hobe
    */

    public void directGoYX(int uu, int vv) {
        int r = cur_row + uu;
        int c = cur_col + vv;
        if(r<1 || r>8 || c<1 || c>8)return;
        if(whiteturn)king = 'K';
        else king = 'k';


        board[r][c].check = 'c';
        if(board[r][c].iconChar == king){wag++;voldemort*=board[r][c].iconSerial;}
    }

    public void goYX(int r, int c, int i, int j, int num) {
        if(board[r][c].iconChar <= 'Z')king='k';
        else king='K';

        char c1='x',c2='x';
        int kr = r, kc = c;

        for( ;c1=='x'; ){
            r+=i; c+=j;
            if(r<1 || r>8 || c<1 || c>8)break;
            c1 = board[r][c].iconChar;
            board[r][c].check = 'c';
            if(c1 == king){kr=r;kc=c;wag++;voldemort*=board[cur_row][cur_col].iconSerial;}
            else if(c1 != 'x' && board[r][c].iconSerial%2 == board[cur_row][cur_col].iconSerial%2){
                r=9; c=9;
            }
        }
        for( ;c2=='x'; ){
            r+=i; c+=j;
            if(r<1 || r>8 || c<1 || c>8)break;
            c2 = board[r][c].iconChar;
            if(c1 == king) board[r][c].check = 'c';
            else if(c2 == king){kr=r-i; kc=c-j;}

        }
        for( ; kr!=cur_row&&kc!=cur_col; kr-=i, kc-=j){
            if(kr<1 || kr>8 || kc<1 || kc>8)continue;
            if(board[kr][kc].members%board[cur_row][cur_col].iconSerial != 0)
                board[kr][kc].members *= board[cur_row][cur_col].iconSerial;
        }
        
    }



    public void refreshBoard() {

        eraseBoard();


        // board[5][8].iconChar = 'b'; board[5][8].iconSerial = board[5][8].members = 86;
        // board[2][5].iconChar = 'x'; board[2][5].iconSerial = board[2][5].members = 1;
        // board[3][6].iconChar = 'P'; board[3][6].iconSerial = board[3][6].members = 71;
        // // board[1][4].iconChar = 'x'; board[1][4].iconSerial = board[1][4].members = 1;
        // // board[5][8].iconSerial = 86;
        

        // whose turn is not now, we should see where they can check the king
        for(cur_row = 1; cur_row<=8; cur_row++) {
            for(cur_col = 1; cur_col<=8; cur_col++) {

                char ch = board[cur_row][cur_col].iconChar;
                if(ch == 'x')continue;
                if(!(whiteturn ^ (ch<'Z')))continue;

                if(board[cur_row][cur_col].check != 'c')board[cur_row][cur_col].check = 'C';

                if(ch == 'k' || ch == 'K'){
                    for(int i=-1; i<=1; i++){
                        for(int j=-1; j<=1; j++){
                            if(i==0 && j==0)continue;
                            directGoYX(i, j);
                        }
                    }
                }

                if(ch == 'b' || ch == 'B' || ch == 'q' || ch == 'Q'){
                    goYX(cur_row, cur_col, 1, 1, 0);
                    goYX(cur_row, cur_col, 1, -1, 0);
                    goYX(cur_row, cur_col, -1, 1, 0);
                    goYX(cur_row, cur_col, -1, -1, 0);
                }
                if(ch == 'r' || ch == 'R' || ch == 'q' || ch == 'Q'){
                    goYX(cur_row, cur_col, 0, 1, 0);
                    goYX(cur_row, cur_col, 0, -1, 0);
                    goYX(cur_row, cur_col, 1, 0, 0);
                    goYX(cur_row, cur_col, -1, 0, 0);
                }
                if(ch == 'h' || ch == 'H'){
                    for(int uu=-2; uu<=2; uu+=4)
                        for(int vv = -1; vv<=1; vv+=2){
                            directGoYX(uu, vv);
                            directGoYX(vv, uu);
                        }
                }
                if(ch == 'p'){
                    directGoYX(-1, 1); directGoYX(-1, -1);
                }
                if(ch == 'P'){
                    directGoYX(1, 1); directGoYX(1, -1);
                }

            }
        }

        // whose turn is now, we should count their moves
        for(cur_row = 1; cur_row<=8; cur_row++) {
            for(cur_col = 1; cur_col<=8; cur_col++) {

                char ch = board[cur_row][cur_col].iconChar;
                if(ch == 'x')continue;
                if(whiteturn ^ (ch<'Z'))continue;

                if(ch == 'k' || ch == 'K')board[cur_row][cur_col].countMoves(0,0);

                if(ch == 'b' || ch == 'B' || ch == 'q' || ch == 'Q'){
                    board[cur_row][cur_col].countMoves(1, 1);
                    board[cur_row][cur_col].countMoves(1, -1);
                    board[cur_row][cur_col].countMoves(-1, 1);
                    board[cur_row][cur_col].countMoves(-1, -1);
                }
                if(ch == 'r' || ch == 'R' || ch == 'q' || ch == 'Q'){
                    board[cur_row][cur_col].countMoves(0, 1);
                    board[cur_row][cur_col].countMoves(0, -1);
                    board[cur_row][cur_col].countMoves(1, 0);
                    board[cur_row][cur_col].countMoves(-1, 0);
                }
                if(ch == 'h' || ch == 'H'){
                    for(int uu=-2; uu<=2; uu+=4)
                        for(int vv = -1; vv<=1; vv+=2){
                            board[cur_row][cur_col].countMoves(uu, vv);
                            board[cur_row][cur_col].countMoves(vv, uu);
                        }
                }
                if(ch == 'p'){
                    if(cur_row==1)continue;
                    if(board[cur_row-1][cur_col].iconChar == 'x'){board[cur_row][cur_col].countMoves(-1, 0);
                    if(cur_row == 7 && board[cur_row-2][cur_col].iconChar == 'x')board[cur_row][cur_col].countMoves(-2, 0);}
                    if(cur_col-1>=1 && board[cur_row-1][cur_col-1].iconChar != 'x'){
                        board[cur_row][cur_col].countMoves(-1, -1);}
                    if(cur_col+1<=8 && board[cur_row-1][cur_col+1].iconChar != 'x'){
                        board[cur_row][cur_col].countMoves(-1, 1);}
                }
                if(ch == 'P'){
                    if(cur_row==8)continue;
                    if(board[cur_row+1][cur_col].iconChar == 'x'){board[cur_row][cur_col].countMoves(1, 0);
                    if(cur_row == 2 && board[cur_row+2][cur_col].iconChar == 'x')board[cur_row][cur_col].countMoves(2, 0);}
                    if(cur_col-1>=1 && board[cur_row+1][cur_col-1].iconChar != 'x'){
                        board[cur_row][cur_col].countMoves(1, -1);}
                    if(cur_col+1<=8 && board[cur_row+1][cur_col+1].iconChar != 'x'){
                        board[cur_row][cur_col].countMoves(1, 1);}
                }


            }
        }
        
        // drawBoard();
    }

    public class LabelDragger implements MouseListener, MouseMotionListener {

        public void mousePressed(MouseEvent e) {
            // drawBoard();
            isDragging = true;
            JLabel label = (JLabel) e.getSource();
            content.setLayer(label, ++focus);
            int x = label.getX() + e.getX(), y = label.getY() + e.getY();
            prevRow = getrowy(y); prevCol = x/100;
            if(board[prevRow][prevCol].moves == 0)isDragging = false;
            if(whiteturn && (board[prevRow][prevCol].iconChar>'Z'))isDragging = false;
        }
        public void mouseDragged(MouseEvent e) {
            JLabel label = (JLabel)e.getSource();
            int x = label.getX() + e.getX();
            int y = label.getY() + e.getY();

            if(!isDragging)
            {
                int ttx = board[prevRow][prevCol].posx, tty = board[prevRow][prevCol].posy;
                if(x<=ttx)x = ttx; else if(x>=ttx+100)x = ttx+100;
                if(y<=tty)y = tty; else if(y>=tty+100)y = tty+100;
            }
            else{ 
                if(x<=100)x = 100; else if(x>=900)x = 900;
                if(y<=100)y = 100; else if(y>=900)y = 900;     
            }

            label.setLocation(x - 40, y - 40);
            SwingUtilities.invokeLater( new RefreshThread() );      

        }
        public void mouseReleased(MouseEvent e) {
            JLabel label = (JLabel) e.getSource();
            content.setLayer(label, focus++);
            int x = label.getX() + e.getX(), y = label.getY() + e.getY();
            newRow = getrowy(y); newCol = x/100;
            Boolean setToPrevPosition = false;

            if(!isDragging || newRow <1 || newRow >= 8 || newCol <1 || newCol >8)setToPrevPosition = true;
            else if(board[newRow][newCol].members % board[prevRow][prevCol].iconSerial != 0)setToPrevPosition = true;
            else if(prevRow==newRow && prevCol==newCol)setToPrevPosition = true;
            if(setToPrevPosition){
                label.setLocation(board[prevRow][prevCol].posx+10, board[prevRow][prevCol].posy+10);
            }
            else{
                if(board[newRow][newCol].icon != null)
                    content.remove(board[newRow][newCol].icon);
                content.setLayer(label, --focus);
                board[newRow][newCol].icon = board[prevRow][prevCol].icon;
                board[newRow][newCol].iconChar = board[prevRow][prevCol].iconChar;
                board[newRow][newCol].iconSerial = board[prevRow][prevCol].iconSerial;
                board[newRow][newCol].icon = board[prevRow][prevCol].icon;
                
                board[prevRow][prevCol].iconChar = 'x';
                board[prevRow][prevCol].iconSerial = 1;
                board[prevRow][prevCol].icon = null;
                label.setLocation(board[newRow][newCol].posx+10, board[newRow][newCol].posy+10);
                whiteturn = !whiteturn;
            }

            refreshBoard();


            if(totalMoves == 0) {
                if(whiteturn) 
                {print("Black wins!!!!!!!!!!!!!!!\n\n");}
                else {print("White wins!!!!!!!!!!!!\n\n");}
            }


            

        }


        public void mouseMoved(MouseEvent e) {}
        public void mouseClicked(MouseEvent e) {}
        public void mouseEntered(MouseEvent e) {}
        public void mouseExited(MouseEvent e) {}
    
    }

    public JLabel setJlabel( JLabel label, int pos, String str, int posX, int posY) {
        label = new JLabel(new ImageIcon(str));
        label.setBounds( posX, posY, label.getPreferredSize().width, label.getPreferredSize().height );
        if(str != "Resources/black.png" && str != "Resources/white.png" && str != "Resources/Chessboard.png")
            {
                LabelDragger labelDragger = new LabelDragger();
                label.addMouseMotionListener(labelDragger);
                label.addMouseListener(labelDragger);
            }

        label.setOpaque( false );
        content.setLayer( label, pos );

        getContentPane().add( label );

        return label;
    }
 
    public int getrowy(int y){ if(firstplayer == "black")return y/100; else return 9-y/100; }

    private class RefreshThread extends Thread { public void run() { content.revalidate(); content.repaint();  } }


    public void setRectangle(){
        for(int i=1; i<=8; i++){
            for(int j=1; j<=8; j++){
                board[i][j] = new Rectangle(i, j, 100*j, 100*i);
                if(firstplayer == "white"){
                    board[i][j].posy = 100*(9-i);
                }
            }
        }
        String str = initposStr;
        for(int i=0; i<str.length(); i+=3){
            int x = str.charAt(i+1)-'A'+1, y = str.charAt(i+2)-'0';
            board[y][x].iconChar = str.charAt(i);
            String iconStr = "Resources/ChessPieces/"+board[y][x].iconChar+".png";
            board[y][x].icon = setJlabel(null, i/3+1, iconStr ,board[y][x].posx+10, board[y][x].posy+10);
            
            if(str.charAt(i) > 'Z')board[y][x].iconSerial = board[y][x].members = prime[i/3]*2;
            else board[y][x].iconSerial = board[y][x].members = prime[i/3];

        }
    }


    public class Rectangle{
        int moves = 0, members = 1, iconSerial = 1, posx=1, posy = 1, row=1, col=1;
        JLabel icon = null;
        char iconChar='x', check='x';
        int checkMembers=1;



        public Rectangle(int r, int c, int pX, int pY){ row = r;col = c; posx = pX; posy = pY; }

        public void countMoves(int i, int j){
            int r = row;
            int c = col;
            if(whiteturn)king = 'K';
            else king = 'k';
            if(iconChar == king){
                for(i=-1; i<=1; i++){
                    for(j=-1; j<=1; j++){
                        if(i==0 && j==0)continue;

                        if(row+i < 1 || row+i > 8 || col+j < 1 || col+j > 8)continue;

                        if(board[row+i][col+j].check == 'c')continue;

                        if(board[row+i][col+j].iconChar == 'x' || board[row+i][col+j].iconSerial%2 != iconSerial%2){
                            moves++; totalMoves++;
                            board[row+i][col+j].members *= iconSerial;
                        }
                    }
                }


                return;
            }
            if(wag >= 2){moves=0;return;}

            int res = voldemort*(members/iconSerial); //////// check if res = 0
            if(res == 0){res=1;}

            if(iconChar == 'p' || iconChar == 'P' || iconChar == 'h' || iconChar == 'H'){
                if(r+i < 1 || r+i > 8 || c+j < 1 || c+j > 8)return;
                if(board[r+i][c+j].iconChar=='x' || iconSerial%2!=board[r+i][c+j].iconSerial%2){
                    if(board[r+i][c+j].members % res == 0){
                        if(board[r+i][c+j].members % iconSerial != 0){
                            board[r+i][c+j].members *= iconSerial; moves++; totalMoves++;
                        }
                    }
                }
                return;
            }



            for(;;){
                r+=i; c+=j;
                if(r<1 || r>8 || c<1 || c>8)return;

                if(board[r][c].iconChar=='x' || iconSerial%2!=board[r][c].iconSerial%2){
                    if(board[r][c].members % res == 0){
                        if(board[r][c].members % iconSerial != 0){
                            board[r][c].members *= iconSerial; moves++; totalMoves++;
                        }
                    }

                    if(board[r][c].iconChar != 'x')return;
                }
                else return;
            }
            
            

        }

    }

    public void print(String str){ System.out.print(str); }

    public void eraseBoard() {
        wag = 0;
        totalMoves = 0;
        voldemort = 1;
        for(int i=1; i<=8; i++){
            for(int j=1; j<=8; j++){
                board[i][j].check = 'x';
                board[i][j].moves = 0;
                board[i][j].members = board[i][j].iconSerial;
            }
        }
    }

    public void drawBoard(){
        System.out.print("new instance: "+whiteturn+"\n\n");
        for(int i=1; i<=8; i++){
            for(int j=1; j<=8; j++){
                print(board[i][j].iconSerial+"\t");
            }
            System.out.print("\n");
        }
        print("\n\n");
        for(int i=1; i<=8; i++){
            for(int j=1; j<=8; j++){
                print(board[i][j].members+"\t");
            }
            System.out.print("\n");
        }
        print("\n\n");
        for(int i=1; i<=8; i++){
            for(int j=1; j<=8; j++){
                print(board[i][j].moves+"\t");
            }
            System.out.print("\n");
        }
        print("\n\n");
        for(int i=1; i<=8; i++){
            for(int j=1; j<=8; j++){
                print(board[i][j].iconChar+"\t");
            }
            System.out.print("\n");
        }
        print("\n\n");
        for(int i=1; i<=8; i++){
            for(int j=1; j<=8; j++){
                print(board[i][j].check+"\t");
            }
            System.out.print("\n");
        }
        print("\n\n\n\n\n\n");
    }




}
