package ZP4JV;

import java.util.ArrayList;

public class Playlist {
    private String root;
    private String tracks;
    private String name;
    private String genre;
    private ArrayList<Track> tracklist;

    public Playlist(String root, String tracks, String name, String genre, ArrayList<Track> trackslist) {
        this.root = root;
        this.tracks = tracks;
        this.name = name;
        this.genre = genre;
        this.tracklist = trackslist;
    }

    public Playlist() {

    }

    public String getRoot() {
        return root;
    }

    public void setRoot(String root) {
        this.root = root;
    }

    public String getTracks() {
        return tracks;
    }

    public void setTracks(String tracks) {
        this.tracks = tracks;
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

    @Override
    public String toString() {
        StringBuilder stringBuilder = new StringBuilder();
        stringBuilder.append("Root element: " + root + ", number of tracks " + tracks + "\n" + name + " (genre " + genre +
                ")\n");
        stringBuilder.append("Tracks: \n");
        for (Track t : tracklist) {
            stringBuilder.append("location: " + t.getLocation() + ", duration: " + t.getDuration() + ", name of " +
                    "episode: " + t.getText() + "\n");
        }
        return stringBuilder.toString();
    }
}
