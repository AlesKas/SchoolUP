package ZP4JV;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.util.ArrayList;

public class AddForm extends JFrame{

    public JTextField name;
    public JTextField genre;
    public JTextField tracks;
    private JPanel mainPanel;
    public JButton add;
    private JButton cancel;
    public JTextField nameS;
    public JTextField len;
    public JTextField lan;

    public AddForm() {
        this.setDefaultCloseOperation(DISPOSE_ON_CLOSE);
        this.setTitle("Add");
        init();

        this.setPreferredSize(new Dimension(400,150));
        this.setContentPane(mainPanel);
        this.pack();
    }

    public AddForm(int priznak)
    {
        this.setDefaultCloseOperation(DISPOSE_ON_CLOSE);
        this.setTitle("Add");
        mainPanel = new JPanel();
        nameS = new JTextField(10);
        len = new JTextField(10);
        lan = new JTextField(10);
        add = new JButton("Add");
        cancel = new JButton("Cancel");

        var nameLabel = new JLabel("Name:");
        var lengLabel = new JLabel("Length:");
        var langLabel = new JLabel("Language:");

        var names = new JPanel(new FlowLayout(FlowLayout.RIGHT));
        names.add(nameLabel);
        names.add(nameS);
        names.setAlignmentX(Component.CENTER_ALIGNMENT);
        mainPanel.add(names);

        var lens = new JPanel(new FlowLayout(FlowLayout.RIGHT));
        names.add(lengLabel);
        names.add(len);
        names.setAlignmentX(Component.CENTER_ALIGNMENT);
        mainPanel.add(lens);

        var dur = new JPanel(new FlowLayout(FlowLayout.RIGHT));
        names.add(langLabel);
        names.add(lan);
        names.setAlignmentX(Component.CENTER_ALIGNMENT);
        mainPanel.add(lan);

        this.setPreferredSize(new Dimension(400,150));
        this.setContentPane(mainPanel);
        this.pack();
    }

    private void init()
    {
        mainPanel = new JPanel();
        mainPanel.setLayout(new FlowLayout());
        var nameLabel = new JLabel("Name:");
        var genreLabel = new JLabel("Genre:");
        var tracksLabel = new JLabel("Number of tracks:");
        name = new JTextField(10);
        genre = new JTextField(10);
        add = new JButton("Add");
        cancel = new JButton("Cancel");
        tracks = new JTextField(5);

        var names = new JPanel(new FlowLayout(FlowLayout.RIGHT));
        names.add(nameLabel);
        names.add(name);
        names.setAlignmentX(Component.CENTER_ALIGNMENT);
        mainPanel.add(names);

        var genres = new JPanel(new FlowLayout(FlowLayout.RIGHT));
        genres.add(genreLabel);
        genres.add(genre);
        genres.setAlignmentX(Component.CENTER_ALIGNMENT);
        mainPanel.add(genres);

        var tracksPanel = new JPanel(new FlowLayout(FlowLayout.RIGHT));
        tracksPanel.add(tracksLabel);
        tracksPanel.add(tracks);
        tracksPanel.setAlignmentX(Component.CENTER_ALIGNMENT);
        mainPanel.add(tracksPanel);


        var buttons = new JPanel(new FlowLayout(FlowLayout.RIGHT));
        buttons.add(add);
        buttons.add(cancel);
        mainPanel.add(buttons);

        cancel.addActionListener((ActionEvent e) ->
        {
            int res = JOptionPane.showConfirmDialog(AddForm.this, "Do you want to exit?", "Exit" ,
                JOptionPane.YES_NO_OPTION);
            if(res == 0)
                this.dispose();

        });
    }

    public AddForm(Object[] row)
    {
        this.setDefaultCloseOperation(DISPOSE_ON_CLOSE);
        this.setTitle("Edit");
        String nameO = (String)row[0];
        String genreO = (String)row[1];
        String trackO = (String)row[2];


        init();
        this.name.setText(nameO);
        this.genre.setText(genreO);
        this.tracks.setText(trackO);


        this.setPreferredSize(new Dimension(300,300));
        this.setContentPane(mainPanel);
        this.pack();
    }
}
