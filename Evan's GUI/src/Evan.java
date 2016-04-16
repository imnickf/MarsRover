import java.awt.Dimension;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFormattedTextField;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JTextField;

import com.fazecast.jSerialComm.*;

public class Evan {

	public static void main(String[] args) 
	{
		// Create and configure window
		JFrame window = new JFrame();
		//GridLayout layout = new GridLayout(2,3);
		window.setTitle("The Amazing GUI of Evan");
		window.setSize(700, 400);
		window.setLayout(null);
		window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		JLabel moveLabel = new JLabel("Move (cm):");
		JLabel rotateLabel = new JLabel("Rotate (degrees):");
		JLabel scanLabel = new JLabel("Scan for objects");
		JLabel objectsLabel = new JLabel("Found objects");
		
		JLabel bumpSensorsLabel = new JLabel("Bump Sensor (r, l) values:");
		JLabel cliffSensorsLabel = new JLabel("Cliff Sensor (l, fl, fr, r) values:");
		JLabel cliffSignalsLabel = new JLabel ("Cliff Sensor (l, fl, fr, r) values:");
		
		JLabel bumpSensorValues = new JLabel("R: 0, L: 0");
		JLabel cliffSensorsValues = new JLabel("L: 0, FL: 0, FR: 0, R: 0");
		JLabel cliffSignalsValues = new JLabel ("L: 0, FL: 0, FR: 0, R: 0");
		
		JButton moveButton = new JButton("Move!");
		JButton rotateButton = new JButton("Rotate!");
		JButton scanButton = new JButton("Scan!");
		
		JFormattedTextField moveField = new JFormattedTextField();
		JFormattedTextField rotateField = new JFormattedTextField();
		
		JTextField objectDisplay = new JTextField();
		
		objectDisplay.setEnabled(false);
		moveField.setValue(new Integer(90));
		moveField.setColumns(5);
		rotateField.setValue(50);
		rotateField.setColumns(5);
		
		moveButton.addActionListener(new ActionListener(){
			@Override public void actionPerformed(ActionEvent arg0) {
				SerialPort port = SerialPort.getCommPort("COM8");
				port.setComPortParameters(38400, 8, 2, SerialPort.NO_PARITY);
				port.setComPortTimeouts(SerialPort.TIMEOUT_WRITE_SEMI_BLOCKING, 0, 0);
				if (port.openPort()) {
					
					String outputString = "m" + moveField.getValue();
					System.out.println(outputString);
					byte toSend[] = outputString.getBytes();
					port.writeBytes(toSend, toSend.length);
				} 
			}
		});
		
		rotateButton.addActionListener(new ActionListener() {
			@Override public void actionPerformed(ActionEvent arg0) {
				SerialPort port = SerialPort.getCommPort("COM8");
				port.setComPortParameters(38400, 8, 2, SerialPort.NO_PARITY);
				port.setComPortTimeouts(SerialPort.TIMEOUT_WRITE_SEMI_BLOCKING, 0, 0);
				if (port.openPort()) {
					
					String outputString = "r" + rotateField.getValue();
					System.out.println(outputString);
					byte toSend[] = outputString.getBytes();
					port.writeBytes(toSend, toSend.length);
				} 
			}
		});
		
		scanButton.addActionListener(new ActionListener() {
			@Override public void actionPerformed(ActionEvent arg0) {
				SerialPort port = SerialPort.getCommPort("COM8");
				port.setComPortParameters(38400, 8, 2, SerialPort.NO_PARITY);
				port.setComPortTimeouts(SerialPort.TIMEOUT_WRITE_SEMI_BLOCKING, 0, 0);
				if (port.openPort()) {
					
					String outputString = "s";
					System.out.println(outputString);
					byte toSend[] = outputString.getBytes();
					port.writeBytes(toSend, toSend.length);
				} 
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
		window.add(objectDisplay);
		
		window.add(bumpSensorsLabel);
		window.add(cliffSensorsLabel);
		window.add(cliffSignalsLabel);
		
		window.add(bumpSensorValues);
		window.add(cliffSensorsValues);
		window.add(cliffSignalsValues);
		
		Insets insets = window.getInsets();
		Dimension size = rotateLabel.getPreferredSize();
		
		rotateLabel.setBounds(10 + insets.left, 10 + insets.top, size.width, size.height);
		size = rotateField.getPreferredSize();
		rotateField.setBounds(10 + rotateLabel.getX() + rotateLabel.getWidth(), 10 + insets.top, size.width, size.height);
		size = rotateButton.getPreferredSize();
		rotateButton.setBounds(10 + rotateField.getX() + rotateField.getWidth(), 10 + insets.top, size.width, size.height);
		
		size = moveLabel.getPreferredSize();
		moveLabel.setBounds(10 + insets.left, 20 + insets.top + rotateButton.getHeight(), size.width, size.height);
		size = moveField.getPreferredSize();
		moveField.setBounds(10 + rotateLabel.getX() + rotateLabel.getWidth(), 20 + insets.top + rotateButton.getHeight(), size.width, size.height);
		size = moveButton.getPreferredSize();
		moveButton.setBounds(10 + rotateField.getX() + rotateField.getWidth(), 20 + insets.top + rotateButton.getHeight(), size.width, size.height);
		
		size = scanLabel.getPreferredSize();
		scanLabel.setBounds(10 + insets.left, 10 + insets.top + moveButton.getY() + moveButton.getHeight(), size.width, size.height);
		size = scanButton.getPreferredSize();
		scanButton.setBounds(10 + rotateLabel.getX() + rotateLabel.getWidth(), 10 + insets.top + moveButton.getY() + moveButton.getHeight(), size.width, size.height);
		
		size = objectsLabel.getPreferredSize();
		objectsLabel.setBounds(10 + insets.left, 10 + insets.top + scanButton.getY() + scanButton.getHeight(), size.width, size.height);
		objectDisplay.setBounds(10 + insets.left, 10 + insets.top + objectsLabel.getY() + objectsLabel.getHeight(), 400, 200);
		
		size = bumpSensorsLabel.getPreferredSize();
		bumpSensorsLabel.setBounds(30 + rotateButton.getX() + rotateButton.getWidth(), 10 + insets.top, size.width, size.height);
		
		size = cliffSensorsLabel.getPreferredSize();
		cliffSensorsLabel.setBounds(30 + rotateButton.getX() + rotateButton.getWidth(), 20 + insets.top + rotateButton.getHeight(), size.width, size.height);
		
		size = cliffSignalsLabel.getPreferredSize();
		cliffSignalsLabel.setBounds(30 + rotateButton.getX() + rotateButton.getWidth(), 10 + insets.top + moveButton.getY() + moveButton.getHeight(), size.width, size.height);
		
		bumpSensorValues.setBounds(25 + bumpSensorsLabel.getX() + bumpSensorsLabel.getWidth(), 10 + insets.top, 200, size.height);
		cliffSensorsValues.setBounds(25 + bumpSensorsLabel.getX() + bumpSensorsLabel.getWidth(), 20 + insets.top + rotateButton.getHeight(), 200, size.height);
		cliffSignalsValues.setBounds(25 + bumpSensorsLabel.getX() + bumpSensorsLabel.getWidth(), 10 + insets.top + moveButton.getY() + moveButton.getHeight(), 200, size.height);
		
		window.setVisible(true);
		
		SerialPort port8 = SerialPort.getCommPort("COM8");
		port8.openPort();
		port8.addDataListener(new SerialPortDataListener() {
			@Override public int getListeningEvents() {
				return SerialPort.LISTENING_EVENT_DATA_AVAILABLE;
			}
			@Override public void serialEvent(SerialPortEvent event) {
				if (event.getEventType() != SerialPort.LISTENING_EVENT_DATA_AVAILABLE) {
					return;
				}
				byte[] newData = new byte[port8.bytesAvailable()];
				int numRead = port8.readBytes(newData, newData.length);
				System.out.println("Read " + numRead + " bytes.");
			}
		});
		/*
		Thread readThread = new Thread() {
			@Override public void run() {
				try {readThread.sleep(100);} catch(Exception e) {}
				
				
			}
		};
		*/
	}

}
