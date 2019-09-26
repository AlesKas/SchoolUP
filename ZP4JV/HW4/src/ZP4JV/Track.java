package ZP4JV;

public class Track {
    private String name;
    private String duration;
    private String location;

    public Track(String name, String duration, String location) {
        this.name = name;
        this.duration = duration;
        this.location = location;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getDuration() {
        return duration;
    }

    public void setDuration(String duration) {
        this.duration = duration;
    }

    public String getLocation() {
        return location;
    }

    public void setLocation(String location) {
        this.location = location;
    }
}
