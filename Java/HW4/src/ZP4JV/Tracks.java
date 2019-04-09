package ZP4JV;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.util.ArrayList;

public class Tracks extends JFrame {

    private JButton butAdd;
    private JButton butEdit;
    private JButton butDel;
    private JPanel mainPanel;
    public JTable table;
    private JScrollPane scroll;
    public DefaultTableModel model;
    private Object[] columns = {"Name", "Location", "Duration"};

    public Tracks() {
        this.setDefaultCloseOperation(DISPOSE_ON_CLOSE);
        this.setTitle("Tracks");
        mainPanel = new JPanel(new BorderLayout());
        model = new DefaultTableModel();
        model.setColumnIdentifiers(columns);
        table = new JTable(model);
        scroll = new JScrollPane(table);
        mainPanel.add(scroll, BorderLayout.CENTER);
        initBtns();

        this.setPreferredSize(new Dimension(400, 400));
        this.setContentPane(mainPanel);
        this.pack();
    }

    private void initBtns() {
        butAdd = new JButton("Add");
        butEdit = new JButton("Edit");
        butDel = new JButton("Delete");
        butAdd.setPreferredSize(new Dimension(75, 25));
        butEdit.setPreferredSize(new Dimension(75, 25));
        butDel.setPreferredSize(new Dimension(75, 25));

        var btns = new JPanel();
        btns.setLayout(new FlowLayout());

        btns.add(butAdd);
        btns.add(butEdit);
        btns.add(butDel);

        mainPanel.add(btns, BorderLayout.SOUTH);

    }
}
