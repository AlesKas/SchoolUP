package ZP4JV;

import javax.xml.stream.*;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.ArrayList;

public class StAXPlaylistReaderWriter implements PlaylistReaderWriter {
    Playlist playlist = new Playlist();
    ArrayList<Track> trackArrayList = new ArrayList<Track>();

    @Override
    public Playlist loadPlaylist(InputStream input) throws Exception {
        XMLInputFactory xmlInputFactory = XMLInputFactory.newInstance();
        XMLStreamReader reader = xmlInputFactory.createXMLStreamReader(input);

        String element = "";
        while (reader.hasNext()) {
            switch (reader.next()) {
                case XMLStreamReader.START_ELEMENT: {
                    element = reader.getName().toString();
                    if (element.equals("playlist")) {
                        playlist.setRoot(element);
                        playlist.setTracks(reader.getAttributeValue(0));
                    }
                    if (element.equals("track")) {
                        trackArrayList.add(new Track(reader.getAttributeValue(0),
                                reader.getAttributeValue(1), ""));
                    }
                    break;
                }
                case XMLStreamConstants.END_ELEMENT: {
                    reader.next();
                    break;
                }
                case XMLStreamConstants.CHARACTERS: {
                    if (element.equals("name")) {
                        playlist.setName(reader.getText());
                    } else if (element.equals("genre")) {
                        playlist.setGenre(reader.getText());
                    } else if (element.equals("track")) {
                        trackArrayList.get(trackArrayList.size() - 1).setText(reader.getText());
                    }
                    break;
                }
            }
        }
        playlist.setTracklist(trackArrayList);
        return playlist;
    }

    @Override
    public void storePlaylist(OutputStream output, Playlist playlist) throws Exception {
        XMLOutputFactory xmlOutputFactory = XMLOutputFactory.newInstance();
        XMLStreamWriter xmlWriter = xmlOutputFactory.createXMLStreamWriter(output);


        xmlWriter.writeStartDocument();
        xmlWriter.writeStartElement("playlist");
        xmlWriter.writeAttribute("tracks", playlist.getTracks());

        xmlWriter.writeStartElement("name");
        xmlWriter.writeCharacters(playlist.getName());
        xmlWriter.writeEndElement();

        xmlWriter.writeStartElement("genre");
        xmlWriter.writeCharacters(playlist.getGenre());
        xmlWriter.writeEndElement();

        xmlWriter.writeStartElement("tracklist");
        for (Track t : trackArrayList) {
            xmlWriter.writeStartElement("track");
            xmlWriter.writeAttribute("location" ,t.getLocation());
            xmlWriter.writeAttribute("duration", t.getDuration());
            xmlWriter.writeCharacters(t.getText());
            xmlWriter.writeEndElement();
        }
        xmlWriter.writeEndElement();
        xmlWriter.writeEndElement();
        xmlWriter.writeEndDocument();
    }
}
