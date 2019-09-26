package ZP4JV;

import com.sun.security.auth.module.Krb5LoginModule;

import javax.swing.*;
import javax.swing.table.AbstractTableModel;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.awt.event.*;
import java.util.ArrayList;
import java.util.Arrays;

public class MainForm extends JFrame {

    private JPanel mainPanel;
    private JButton butAdd;
    private JButton butEdit;
    private JButton butDel;
    private JMenuBar menuBar;
    public JTable table;
    private JScrollPane scroll;
    public DefaultTableModel model;
    private Object[] columns = {"Name", "Genre", "Tracks"};
    private ArrayList<Playlist> playlist = new ArrayList<>();


    public MainForm() {
        this.setDefaultCloseOperation(EXIT_ON_CLOSE);
        this.setTitle("Playlist browser");
        mainPanel = new JPanel();
        mainPanel.setPreferredSize(new Dimension(400, 400));
        mainPanel.setLayout(new BorderLayout());


        menuBar = new JMenuBar();
        initBtns();
        initMenu();

        model = new DefaultTableModel();
        model.setColumnIdentifiers(columns);
        table = new JTable();
        table.setModel(model);
        scroll = new JScrollPane(table);
        mainPanel.add(scroll, BorderLayout.CENTER);
        table.setDefaultEditor(Object.class, null);

        butAdd.addActionListener((ActionEvent e) -> {
            add();
        });

        butEdit.addActionListener((ActionEvent e) -> {
            edit();
        });


        butDel.addActionListener((ActionEvent e) -> {
            try {
                var index = table.getSelectedRow();
                playlist.remove(index);
                var row = table.getSelectedRow();
                model.removeRow(row);
            } catch (Exception ex) {
                System.out.println(ex.getMessage());
            }
        });

        table.addMouseListener(new MouseListener() {
            @Override
            public void mouseClicked(MouseEvent e) {
                if (e.getClickCount() == 2) {
                    Tracks track = new Tracks();
                    track.setVisible(true);

                }
            }

            @Override
            public void mousePressed(MouseEvent e) {

            }

            @Override
            public void mouseReleased(MouseEvent e) {

            }

            @Override
            public void mouseEntered(MouseEvent e) {

            }

            @Override
            public void mouseExited(MouseEvent e) {

            }
        });

        this.setJMenuBar(menuBar);

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

    private void initMenu() {
        var menuFile = new JMenu("File");

        var close = new JMenuItem("Exit");


        var menuActions = new JMenu("Actions");
        var add = new JMenuItem("Add");
        var edit = new JMenuItem("Edit");


        close.addActionListener((ActionEvent e) -> {
            this.setVisible(false);
            dispose();
        });

        close.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_X, ActionEvent.CTRL_MASK));
        add.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_A, ActionEvent.CTRL_MASK));
        edit.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_E, ActionEvent.CTRL_MASK));

        add.addActionListener((ActionEvent e) -> {
            add();
        });

        edit.addActionListener((ActionEvent e) ->
        {
            edit();
        });

        menuFile.add(close);

        menuActions.add(add);
        menuActions.add(edit);

        menuBar.add(menuFile);
        menuBar.add(menuActions);
    }

    private void add() {
        AddForm af = new AddForm();
        af.setVisible(true);
        af.add.addActionListener((ActionEvent ev) ->
        {
            if ((!af.name.getText().equals("")) && (!af.genre.getText().equals("")) && (!af.tracks.getText().equals(
                    ""))) {
                Object[] arr = {af.name.getText(), af.genre.getText(), af.tracks.getText()};
                model.addRow(arr);

                Playlist pt = new Playlist();

                pt.setName(af.name.getText());
                pt.setGenre(af.genre.getText());
                pt.setNumberOfTracks(af.tracks.getText());

                JOptionPane.showMessageDialog(af, "Added");
                af.dispose();
            } else {
                JOptionPane.showMessageDialog(af, "Entered informations can not be empty!");
                af.dispose();
            }
        });
    }

    private void edit() {
        try {
            int row = table.getSelectedRow();
            int col = 0;
            Object[] arr = {table.getModel().getValueAt(row, col), table.getModel().getValueAt(row, col + 1),
                    table.getModel().getValueAt(row, col + 2)};
            AddForm af = new AddForm(arr);
            af.setVisible(true);
            af.add.addActionListener((ActionEvent ev) ->
            {
                if ((!af.name.getText().equals("")) && (!af.genre.getText().equals("")) && (!af.tracks.getText().equals(
                        ""))) {
                    model.setValueAt(af.name.getText(), row, col);
                    model.setValueAt(af.genre.getText(), row, col + 1);
                    model.setValueAt(af.tracks.getText(), row, col + 2);

                    playlist.get(row).setName(af.name.getText());
                    playlist.get(row).setGenre(af.genre.getText());
                    playlist.get(row).setNumberOfTracks(af.tracks.getText());

                    JOptionPane.showMessageDialog(af, "Edited");
                    af.dispose();
                } else {
                    JOptionPane.showMessageDialog(af, "Entered informations can not be empty!");
                    af.dispose();
                }
            });
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }


}
