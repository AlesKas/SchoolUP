package ZP4JV;

import java.util.ArrayList;

public class Playlist {
    private String name;
    private String genre;
    private String numberOfTracks;
    private ArrayList<Track> tracklist;

    public Playlist(String name, String genre, ArrayList<Track> trackslist) {
        this.name = name;
        this.genre = genre;
        this.tracklist = trackslist;
    }

    public Playlist(String name, String genre) {
        this.name = name;
        this.genre = genre;
    }

    public Playlist() {

    }

    public Playlist(String name, String genre, String numberOfTracks, ArrayList<Track> tracklist) {
        this.name = name;
        this.genre = genre;
        this.numberOfTracks = numberOfTracks;
        this.tracklist = tracklist;
    }

    public String getNumberOfTracks() {
        return numberOfTracks;
    }

    public void setNumberOfTracks(String numberOfTracks) {
        this.numberOfTracks = numberOfTracks;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getGenre() {
        return genre;
    }

    public void setGenre(String genre) {
        this.genre = genre;
    }

    public ArrayList<Track> getTracklist() {
        return tracklist;
    }

    public void setTracklist(ArrayList<Track> tracklist) {
        this.tracklist = tracklist;
    }
}
