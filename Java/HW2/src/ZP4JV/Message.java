package ZP4JV;


public class Message {
    private String forUser;
    private String fromUser;
    private String text;


    public Message(String forUser, String fromUser, String text) {
        this.forUser = forUser;
        this.fromUser = fromUser;
        this.text = text;
    }

    public Message() {
    }

    public String getForUser() {
        return forUser;
    }


    public String getFromUser() {
        return fromUser;
    }


    public String getText() {
        return text;
    }

}
