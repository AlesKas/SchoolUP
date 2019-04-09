package ZP4JV;

import java.io.*;

public class Main {

    public static void main(String[] args) throws FileNotFoundException, Exception {
    String xmlFile = "/D:/Java.xml";
    String outXmlFile = "/D:/JavaOut.xml";
        String outXmlFile2 = "/D:/JavaOut2.xml";
        String outXmlFile3 = "/D:/JavaOut3.xml";

        DataInputStream is;
        OutputStream os;

        //DOM
        is = new DataInputStream(new FileInputStream(xmlFile));
        os = new FileOutputStream(outXmlFile);
        DOMPlaylistReaderWriter dom = new DOMPlaylistReaderWriter();
        Playlist domPlaylist = dom.loadPlaylist(is);
        dom.storePlaylist(os, domPlaylist);
        System.out.println(domPlaylist);

        //SAX
        is = new DataInputStream(new FileInputStream(xmlFile));
        SAXPlaylistReaderWriter sax = new SAXPlaylistReaderWriter();
        Playlist saxPlaylist = sax.loadPlaylist(is);
        System.out.println(saxPlaylist);
        //sax.storePlaylist(os, saxPlaylist);

        //StAX
        is = new DataInputStream(new FileInputStream(xmlFile));
        os = new FileOutputStream(outXmlFile3);
        StAXPlaylistReaderWriter stax = new StAXPlaylistReaderWriter();
        Playlist staxPlaylist = stax.loadPlaylist(is);
        System.out.println(staxPlaylist);
        stax.storePlaylist(os, staxPlaylist);

    }
}
