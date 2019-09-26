package ZP4JV;

public class Track {
    private String location;
    private String duration;
    private String text;

    public Track(String location, String duration, String text) {
        this.location = location;
        this.duration = duration;
        this.text = text;
    }

    public String getLocation() {
        return location;
    }

    public String getDuration() {
        return duration;
    }

    public String getText() {
        return text;
    }

    public void setLocation(String location) {
        this.location = location;
    }

    public void setDuration(String duration) {
        this.duration = duration;
    }

    public void setText(String text) {
        this.text = text;
    }
}
