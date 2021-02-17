import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class Button1 implements ActionListener {
	
	JTextArea text;
	
	public static void main(String[] args) {
		Button1 gui = new Button1();
		gui.go();
	}
	public void go() {
		JFrame frame = new JFrame();
		
		//JButton button = new JButton("Click me...");
		//Font bigFont = new Font("serif", Font.BOLD, 28);
		//button.setFont(bigFont);
		//frame.getContentPane().add(BorderLayout.NORTH, button);
		
		//JButton east = new JButton("East") ;
		//JButton west = new JButton("West");
		//JButton north = new JButton("North");
		//JButton south = new JButton("South");
		//JButton center = new JButton("Center");
		
		//frame.getContentPane().add(BorderLayout.EAST, east);
		//frame.getContentPane().add(BorderLayout.WEST, west);
		//frame.getContentPane().add(BorderLayout.NORTH, north);
		//frame.getContentPane().add(BorderLayout.SOUTH, south);
		//frame.getContentPane().add(BorderLayout.CENTER, center);
		
		JPanel panel = new JPanel();
		panel.setBackground(Color.darkGray);
		
		panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));
		
		JButton button = new JButton("shock me");
		button.addActionListener(this);
		text = new JTextArea(10, 20);
		text.setLineWrap(true);
		
		JScrollPane scroller = new JScrollPane(text);
		scroller.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS);
		scroller.setHorizontalScrollBarPolicy(ScrollPaneConstants.HORIZONTAL_SCROLLBAR_NEVER);
		
		panel.add(scroller);
		
		frame.getContentPane().add(BorderLayout.CENTER, panel);
		frame.getContentPane().add(BorderLayout.SOUTH, button);

		
		frame.setSize(350, 350);
		frame.setVisible(true);
	}
	public void actionPerformed(ActionEvent ev) {
		text.append("button clicked \n ");
	}
}
