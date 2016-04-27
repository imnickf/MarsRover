import java.awt.Dimension;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFormattedTextField;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.ScrollPaneConstants;
import javax.swing.text.DefaultCaret;

import com.fazecast.jSerialComm.*;

public class Evan {

	public static void main(String[] args) 
	{	
		SerialPort port = SerialPort.getCommPort("COM8");
		port.setComPortParameters(38400, 8, 2, SerialPort.NO_PARITY);
		port.setComPortTimeouts(SerialPort.TIMEOUT_WRITE_SEMI_BLOCKING, 0, 0);
		System.out.println(port.openPort());
		
		// Create and configure window
		JFrame window = new JFrame();
		window.setTitle("The Amazing GUI of Evan");
		window.setSize(500, 400);
		window.setLayout(null);
		window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		JLabel moveLabel = new JLabel("Move (cm):");
		JLabel rotateLabel = new JLabel("Rotate (degrees):");
		JLabel scanLabel = new JLabel("Scan for objects");
		JLabel objectsLabel = new JLabel("Found objects and Sensor Values");
		
		JButton moveButton = new JButton("Move!");
		JButton rotateButton = new JButton("Rotate!");
		JButton scanButton = new JButton("Scan!");
		JButton playSongButton = new JButton("WE MADE IT!");
		JButton sensorValueButtons = new JButton("Get Sensor Values");
		
		JFormattedTextField moveField = new JFormattedTextField();
		JFormattedTextField rotateField = new JFormattedTextField();
		
		JTextArea objectDisplay = new JTextArea();
		
		JScrollPane scrollDisplay = new JScrollPane(objectDisplay);
		scrollDisplay.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS);
		
		DefaultCaret caret = (DefaultCaret)objectDisplay.getCaret();
		caret.setUpdatePolicy(DefaultCaret.ALWAYS_UPDATE);
		
		moveField.setValue(new Integer(90));
		moveField.setColumns(5);
		rotateField.setValue(50);
		rotateField.setColumns(5);
		
		moveButton.addActionListener(new ActionListener(){
			@Override public void actionPerformed(ActionEvent arg0) {
				String outputString = "m" + moveField.getValue();
				System.out.println(outputString);
				byte toSend[] = outputString.getBytes();
				port.writeBytes(toSend, toSend.length);
			}
		});
		
		rotateButton.addActionListener(new ActionListener() {
			@Override public void actionPerformed(ActionEvent arg0) {
				
				String rotateValue = "" + rotateField.getValue();
				String outputString = "r";
				if (rotateValue.length() == 2) {
					outputString += "0";
				}
				outputString += rotateField.getValue();
				System.out.println(outputString);
				byte toSend[] = outputString.getBytes();
				port.writeBytes(toSend, toSend.length);

			}
		});
		
		scanButton.addActionListener(new ActionListener() {
			@Override public void actionPerformed(ActionEvent arg0) {
				String outputString = "s";
				System.out.println(outputString);
				byte toSend[] = outputString.getBytes();
				port.writeBytes(toSend, toSend.length);
			}
		});
		
		playSongButton.addActionListener(new ActionListener() {
			@Override public void actionPerformed(ActionEvent arg0) {
				String outputString = "p";
				System.out.println(outputString);
				byte toSend[] = outputString.getBytes();
				port.writeBytes(toSend, toSend.length);
			}
		});
		
		sensorValueButtons.addActionListener(new ActionListener() {
			@Override public void actionPerformed(ActionEvent arg0) {
				String outputString = "v";
				System.out.println(outputString);
				byte toSend[] = outputString.getBytes();
				port.writeBytes(toSend, toSend.length);
			}
		});
	
		// Add all the things to the window
		window.add(rotateLabel);
		window.add(rotateField);
		window.add(rotateButton);
		window.add(moveLabel);
		window.add(moveField);
		window.add(moveButton);
		window.add(scanLabel);
		window.add(scanButton);
		window.add(objectsLabel);
		window.add(scrollDisplay);
		window.add(playSongButton);
		window.add(sensorValueButtons);
	
		Insets insets = window.getInsets();
		Dimension size = rotateLabel.getPreferredSize();
		
		rotateLabel.setBounds(10 + insets.left, 10 + insets.top, size.width, size.height);
		size = rotateField.getPreferredSize();
		rotateField.setBounds(10 + rotateLabel.getX() + rotateLabel.getWidth(), 10 + insets.top, size.width, size.height);
		size = rotateButton.getPreferredSize();
		rotateButton.setBounds(10 + rotateField.getX() + rotateField.getWidth(), 10 + insets.top, size.width, size.height);
		size = playSongButton.getPreferredSize();
		playSongButton.setBounds(10 + rotateButton.getX() + rotateButton.getWidth(), 10 + insets.top, size.width, size.height);
		
		size = moveLabel.getPreferredSize();
		moveLabel.setBounds(10 + insets.left, 20 + insets.top + rotateButton.getHeight(), size.width, size.height);
		size = moveField.getPreferredSize();
		moveField.setBounds(10 + rotateLabel.getX() + rotateLabel.getWidth(), 20 + insets.top + rotateButton.getHeight(), size.width, size.height);
		size = moveButton.getPreferredSize();
		moveButton.setBounds(10 + rotateField.getX() + rotateField.getWidth(), 20 + insets.top + rotateButton.getHeight(), size.width, size.height);
		size = sensorValueButtons.getPreferredSize();
		sensorValueButtons.setBounds(10 + moveButton.getX() + moveButton.getWidth(), 20 + insets.top + rotateButton.getHeight(), size.width, size.height);
		
		size = scanLabel.getPreferredSize();
		scanLabel.setBounds(10 + insets.left, 10 + insets.top + moveButton.getY() + moveButton.getHeight(), size.width, size.height);
		size = scanButton.getPreferredSize();
		scanButton.setBounds(10 + rotateLabel.getX() + rotateLabel.getWidth(), 10 + insets.top + moveButton.getY() + moveButton.getHeight(), size.width, size.height);
		
		size = objectsLabel.getPreferredSize();
		objectsLabel.setBounds(10 + insets.left, 10 + insets.top + scanButton.getY() + scanButton.getHeight(), size.width, size.height);
		scrollDisplay.setBounds(10 + insets.left, 10 + insets.top + objectsLabel.getY() + objectsLabel.getHeight(), 400, 200);
		
		window.setVisible(true);
		
		
		port.addDataListener(new SerialPortDataListener() {
			@Override public int getListeningEvents() {
				return SerialPort.LISTENING_EVENT_DATA_AVAILABLE;
			}
			@Override public void serialEvent(SerialPortEvent event) {
				if (event.getEventType() != SerialPort.LISTENING_EVENT_DATA_AVAILABLE) {
					return;
				}
				
				byte[] newData = new byte[port.bytesAvailable()];
				int numRead = port.readBytes(newData, newData.length);
				System.out.println("Read " + numRead + " bytes.");
				objectDisplay.append(new String(newData));
			}
		});
	}
}
