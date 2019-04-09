package ZP4JV;

import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.ArrayList;

public class SAXPlaylistReaderWriter implements PlaylistReaderWriter {

    @Override
    public Playlist loadPlaylist(InputStream input) throws Exception {
        Playlist playlist = new Playlist();
        ArrayList<Track> trackArrayList = new ArrayList<Track>();


        SAXParserFactory parserFactory = SAXParserFactory.newInstance();
        SAXParser parser = parserFactory.newSAXParser();

        parser.parse(input, new DefaultHandler() {
                    private String element;

                    @Override
                    public void startDocument() throws SAXException {
                        System.out.println("Zahajeno cteni dokumentu");
                    }

                    @Override
                    public void startElement(String uri, String localName,
                                             String qName, Attributes attributes) throws SAXException {
                        element = qName;

                        if (element.equals("playlist")) {
                            playlist.setRoot(qName);
                            playlist.setTracks(attributes.getValue(0));
                        }
                        if (element.equals("track")) {
                            trackArrayList.add(new Track(attributes.getValue("location"), attributes.getValue(
                                    "duration"), ""));
                        }




                    }

                    @Override
                    public void characters(char[] ch, int start, int length)
                            throws SAXException {
                        if (element.equals("name")) {
                            playlist.setName(new String(ch, start, length));
                        } else if (element.equals("genre")) {
                            playlist.setGenre(new String(ch, start, length));
                        } else if (element.equals("track")) {
                            trackArrayList.get(trackArrayList.size() - 1).setText(new String(ch, start, length));
                        }
                        element = "";
                    }
                }
        );
        playlist.setTracklist(trackArrayList);
        return playlist;
    }

    @Override
    public void storePlaylist(OutputStream output, Playlist playlist) throws Exception {
        throw new SAXWriteExeption("SAX does not support writing");
    }
}
