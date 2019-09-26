package ZP4JV;


import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;

public class Form extends JFrame {

    private JMenuBar menu = new JMenuBar();
    private JPanel mainPanel;
    private JTextArea inputText;
    private JTextArea outputText;
    private JTextField shift;


    public Form() {
        init();
    }

    private void init() {
        this.setTitle("Caesar Cipher");
        this.setDefaultCloseOperation(EXIT_ON_CLOSE);
        mainPanel = new JPanel(new BorderLayout());

        initMenu();
        initOutput();
        initInput();
        initShift();
        initButtons();

        this.setJMenuBar(menu);
        this.setContentPane(mainPanel);
        this.setPreferredSize(new Dimension(550, 450));
        this.pack();
    }

    private void initInput() {
        inputText = new JTextArea(10, 15);
        inputText.setLineWrap(true);
        var inputSide = new JPanel(new BorderLayout());
        var inputLabel = new Label("Decoded:");

        inputSide.add(inputLabel, BorderLayout.NORTH);
        inputSide.add(inputText);
        mainPanel.add(inputSide, BorderLayout.WEST);

    }

    private void initOutput() {
        outputText = new JTextArea(10, 15);
        var outPutLabel = new Label("Coded:");
        var outputSide = new JPanel(new BorderLayout());
        outputSide.add(outPutLabel, BorderLayout.NORTH);
        outputText.setLineWrap(true);
        outputSide.add(outputText);
        mainPanel.add(outputSide, BorderLayout.EAST);
    }

    private void initButtons() {
        var centerPanel = new JPanel();
        var btnClear = new JButton("Clear");
        var btnCode = new JButton("Code");
        var btnDecode = new JButton("Decode");

        btnClear.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                inputText.setText("");
                outputText.setText("");
                shift.setText("");
            }
        });

        btnCode.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                code();
            }
        });

        btnDecode.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                decode();
            }
        });

        centerPanel.add(btnClear);
        centerPanel.add(btnCode);
        centerPanel.add(btnDecode);

        mainPanel.add(centerPanel, BorderLayout.SOUTH);
    }

    private void initShift() {
        shift = new JTextField(5);
        var shiftPanel = new JPanel();
        var shiftLabel = new Label("Shift:");
        shiftPanel.add(shiftLabel);
        shiftPanel.add(shift);
        mainPanel.add(shiftPanel, BorderLayout.CENTER);

    }

    private void initMenu() {
        var menuFile = new JMenu("File");
        var menuCode = new JMenuItem("Code");
        var menuDecode = new JMenuItem("Decode");
        var menuClose = new JMenuItem("Close");

        menuCode.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_C, ActionEvent.CTRL_MASK));
        menuDecode.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_D, ActionEvent.CTRL_MASK));

        menuClose.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_X, ActionEvent.CTRL_MASK));
        menuClose.addActionListener((ActionEvent e) -> {
            setVisible(false);
            dispose();
        });

        menuCode.addActionListener((ActionEvent e) -> {
            code();
        });

        menuDecode.addActionListener((ActionEvent e) -> {
            decode();
        });

        menuFile.add(menuCode);
        menuFile.add(menuDecode);
        menuFile.add(menuClose);
        menu.add(menuFile);

    }

    private void code() {
        String input = inputText.getText();

        if (tryParse(this.shift.getText())) {
            var shift = Integer.valueOf(this.shift.getText());
            String result = "";
            outputText.setText("");

            for (int i = 0; i < input.length(); i++) {
                var charAt = input.charAt(i);
                if (Character.isUpperCase(charAt)) {
                    char ch = (char) (((int) charAt + shift - 65) % 26 + 65);
                    result += ch;
                } else if (charAt == '\n' || charAt == ' ' || charAt == '.') {
                    result += charAt;
                } else {
                    JOptionPane.showMessageDialog(Form.this, "Unsupported characters");
                    return;
                }

            }
            outputText.setText(result);
            inputText.setText("");
        } else {
            JOptionPane.showMessageDialog(Form.this, "Shift not in proper format");
            return;
        }
    }

    private void decode() {
        String input = outputText.getText();
        if (tryParse(this.shift.getText())) {
            String result = "";
            var shift = Integer.valueOf(this.shift.getText());
            inputText.setText("");

            for (int i = 0; i < input.length(); i++) {
                var charAt = input.charAt(i);
                if (Character.isUpperCase(charAt)) {
                    char ch = (char) (((int) charAt - shift - 65) % 26 + 65);
                    result += ch;
                } else if (charAt == '\n' || charAt == ' ' || charAt == '.') {
                    result += charAt;
                } else {
                    JOptionPane.showMessageDialog(Form.this, "Unsupported characters");
                    return;
                }

            }
            inputText.setText(result);
            outputText.setText("");
        }
        else
        {
            JOptionPane.showMessageDialog(Form.this, "Shift not in proper format");
        }
    }

    private boolean tryParse(String input)
    {
        try {
            Integer.parseInt(input);
            return true;
        }
        catch (Exception e)
        {
            System.out.println(e.getMessage());
        }
        return false;
    }
}
