import HuffmanCode.*;
import java.awt.*;
import java.awt.event.*;
/**
 *
 * @author Amey
 */
public class MorseCode extends java.awt.Frame implements ActionListener
{
    private static Morse Code;
    private Panel P1, P2, P3;
    private Label L;
    private TextArea T1, T2;
    private Button B1, B2;

    public MorseCode()
    {
        setLayout(new FlowLayout());
        T1 = new TextArea("English Text.\n(Enter only alphabets (A-Z) or <space>.)",4,40);
        T1.setEditable(true);
        T1.setVisible(true);
        
        B1 = new Button("ENCODE");
        B1.setEnabled(true);
        B1.setVisible(true);
        
        T2 = new TextArea("Morse Code.\n(Enter only <->, <.> or <space>.)",4,40);
        T2.setEditable(true);
        T2.setVisible(true);
        
        B2 = new Button("DECODE");
        B2.setEnabled(true);
        B2.setVisible(true);
        
        L = new Label();
        L.setVisible(false);
        
        P1 = new Panel();
        P1.add(T1);
        P1.add(B1);
        
        P2 = new Panel();
        P2.add(T2);
        P2.add(B2);
        
        P3 = new Panel();
        P3.add(L);
        
        add(P1);
        add(P2);
        add(P3);
        
        B1.addActionListener(this); 
        B2.addActionListener(this);
        
        this.addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent W)
        {
            dispose();
            System.exit(0);
        }
        });
        
        setTitle("Morse Code App");
        setSize(500,300);
    }
    
    public static void main(String A[])
    {
        Code = new Morse();
        new MorseCode().setVisible(true);
    }

    @Override
    public void actionPerformed(ActionEvent AE)
    {
        if(L.isVisible())
            L.setVisible(false);
        if(B1 == AE.getSource())
        {
            try
            {
                T2.setText(Code.encode(T1.getText()));
            }
            catch(InputException IE)
            {
                L.setText(IE.Message);
                L.setAlignment(Label.CENTER);
                L.setForeground(Color.RED);
                L.setVisible(true);
                P3.revalidate();
            }
        }
        
        else
        {
            try
            {
                T1.setText(Code.decode(T2.getText()));
            }
            catch(InputException IE)
            {
                L.setText(IE.Message);
                L.setAlignment(Label.CENTER);
                L.setForeground(Color.RED);
                L.setVisible(true);
                P3.revalidate();
            }
        }
    }
}