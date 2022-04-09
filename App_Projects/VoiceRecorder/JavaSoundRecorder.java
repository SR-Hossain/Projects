import java.io.File;
import java.io.IOException;
import java.sql.Timestamp;
import java.util.Date;

import javax.sound.sampled.AudioFileFormat;
import javax.sound.sampled.AudioFormat;
import javax.sound.sampled.AudioInputStream;
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.DataLine;
import javax.sound.sampled.LineUnavailableException;
import javax.sound.sampled.TargetDataLine;
 
/**
 * A sample program is to demonstrate how to record sound in Java
 * author: www.codejava.net
 */
public class JavaSoundRecorder {
 
    // path of the wav file
    Timestamp ts=new Timestamp(new Date().getTime());
    String str= ts.toString();

    File wavFile;
 
    // format of audio file
    AudioFileFormat.Type fileType = AudioFileFormat.Type.WAVE;
 
    // the line from which audio data is captured
    TargetDataLine audioThatsBeingRecorded;
 
    /**
     * Defines an audio format
     */
        float sampleRate = 14000;
        int sampleSizeInBits = 8;
        int channels = 2;
        boolean signed = true;
        boolean bigEndian = true;
    AudioFormat getAudioFormat() {
        return  new AudioFormat(sampleRate, sampleSizeInBits,
                                             channels, signed, bigEndian);
    }
 
    /**
     * Captures the sound and record into a WAV file
     */
    void start() {
        str = str.replace(":", "");
        str = str.replace("-", "");
        str = str.replace(".", "");
        str = str.replace(" ", "_");
        str+=".wav";
        wavFile = new File(str);
        System.out.print(str+"\n");
        try {
            AudioFormat format = getAudioFormat();
            DataLine.Info info = new DataLine.Info(TargetDataLine.class, format);
 
            // checks if system supports the data line
            if (!AudioSystem.isLineSupported(info)) {
                System.out.println("Line not supported");
                System.exit(0);
            }
            audioThatsBeingRecorded = (TargetDataLine) AudioSystem.getLine(info);
            audioThatsBeingRecorded.open(format);
            audioThatsBeingRecorded.start();   // start capturing
 
            AudioInputStream ais = new AudioInputStream(audioThatsBeingRecorded);
 
            System.out.println("Start recording...");
 
            // start recording
            AudioSystem.write(ais, fileType, wavFile);
 
        } catch (LineUnavailableException ex) {
            ex.printStackTrace();
        } catch (IOException ioe) {
            ioe.printStackTrace();
        }
    }
 
    /**
     * Closes the target data line to finish capturing and recording
     */
    void finish() {
        audioThatsBeingRecorded.stop();
        audioThatsBeingRecorded.close();
        System.out.println("Finished");
    }
 
    /**
     * Entry to run the program
     */
    public static void main(String[] args) {
        final JavaSoundRecorder recorder = new JavaSoundRecorder();
 
        recorder.start();
    }
}
