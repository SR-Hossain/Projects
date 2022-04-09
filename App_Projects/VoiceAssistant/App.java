import java.awt.Desktop;
import java.net.URI;
import java.awt.Robot;
import java.util.Map;
import java.util.HashMap;
import org.javatuples.Triplet;
import java.awt.event.KeyEvent;
import edu.cmu.sphinx.api.Configuration;
import edu.cmu.sphinx.api.LiveSpeechRecognizer;
import edu.cmu.sphinx.api.SpeechResult;

public class App{
    String siteNames = "google facebook youtube twitter";
    Desktop desk = Desktop.getDesktop();
    Map<String, Triplet> commands = new HashMap<String,Triplet>();
    public static void main(String[] args) {
        try {
            new LmGenerator();
        } catch (Exception e1) {
            // TODO Auto-generated catch block
            e1.printStackTrace();
        }
        try{
            new App();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
    public App() throws Exception {
        inputIntoCommadStr();
        Configuration configuration = new Configuration();
        configuration.setAcousticModelPath("resource:/edu/cmu/sphinx/models/en-us/en-us");
        configuration.setDictionaryPath("Resources/dic.dic");
        configuration.setLanguageModelPath("Resources/lm.lm");
        LiveSpeechRecognizer recognizer = new LiveSpeechRecognizer(configuration);
        recognizer.startRecognition(true);
        SpeechResult result;

        while ((result = recognizer.getResult()) != null) {
            String[] words = result.getHypothesis().split(" ");
            for (String word : words) {
                if(word.length() == 0) continue;
                System.out.println(word);
                if(siteNames.contains(word))gotoSite(word);
                else{
                    Robot robot = new Robot();
                    keyPress(robot, word);
                }
            }
        }
        recognizer.stopRecognition();
    }
    void gotoSite(String word) throws Exception {
        desk.browse(new URI("http://www."+word+".com"));
    }
    void keyPress(Robot r, String word) throws Exception {
        if(word.contains("turnoff"))System.exit(0);
        int x = (int)commands.get(word).getValue0();
        int y = (int)commands.get(word).getValue1();
        int z = (int)commands.get(word).getValue2();
        System.out.print("this is "+x+" and "+y+" and "+z+"");
        r.keyPress(x);
        if(y != 0){
            r.keyPress(y);
            if(z != 0){r.keyPress(z);r.keyRelease(z);}
            r.keyRelease(y);
        }
        r.keyRelease(x);
        
      
    }
    void inputIntoCommadStr(){
        commands.put("back", new Triplet(KeyEvent.VK_ALT, KeyEvent.VK_LEFT, 0));
        //forward
        commands.put("forward", new Triplet(KeyEvent.VK_ALT, KeyEvent.VK_RIGHT, 0));
        commands.put("left", new Triplet(KeyEvent.VK_LEFT, 0, 0));
        commands.put("right", new Triplet(KeyEvent.VK_RIGHT, 0, 0));
        commands.put("enter", new Triplet(KeyEvent.VK_ENTER, 0, 0));
        commands.put("close", new Triplet(KeyEvent.VK_CONTROL, KeyEvent.VK_W, 0));
        commands.put("exit", new Triplet(KeyEvent.VK_ALT, KeyEvent.VK_F4, 0));
        commands.put("newtab", new Triplet(KeyEvent.VK_CONTROL, KeyEvent.VK_T, 0));
        commands.put("reload", new Triplet(KeyEvent.VK_CONTROL, KeyEvent.VK_R, 0));
        commands.put("refresh", new Triplet(KeyEvent.VK_CONTROL, KeyEvent.VK_R, 0));
        /*
        commands.put("", new Triplet(, 0, 0));
        commands.put("", new Triplet(, 0, 0));
        commands.put("", new Triplet(, 0, 0));
        commands.put("", new Triplet(, 0, 0));
        commands.put("", new Triplet(, 0, 0));
        commands.put("", new Triplet(, 0, 0));
        commands.put("", new Triplet(, 0, 0));
        */
    }
}