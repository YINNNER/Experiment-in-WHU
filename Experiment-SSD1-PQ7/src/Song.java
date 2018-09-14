/**
 * Created by yiner on 2017/1/4.
 */


class Song {
    private String title;
    private String playTime;
    private String category;
    private String albumTrack;
    private boolean selected;
    private String songID;
    private String songLink;

    public Song(String var1, String var2, String var3, String var4, boolean var5, String var6, String var7) {
        this.title = var1;
        this.playTime = var2;
        this.category = var3;
        this.albumTrack = var4;
        this.selected = var5;
        this.songID = var6;
        this.songLink = var7;
    }

    public void setTitle(String var1) {
        this.title = var1;
    }

    public String getTitle() {
        return this.title;
    }

    public void setTime(String var1) {
        this.playTime = var1;
    }

    public String getTime() {
        return this.playTime;
    }

    public void setCategory(String var1) {
        this.category = var1;
    }

    public String getCategory() {
        return this.category;
    }

    public void setAlbumTrack(String var1) {
        this.albumTrack = var1;
    }

    public String getAlbumTrack() {
        return this.albumTrack;
    }

    public void setSongID(String var1) {
        this.songID = var1;
    }

    public String getSongID() {
        return this.songID;
    }

    public void setSongLink(String var1) {
        this.songLink = var1;
    }

    public String getSongLink() {
        return this.songLink;
    }

    public void select(boolean var1) {
        this.selected = var1;
    }

    public boolean isSelected() {
        return this.selected;
    }
}

