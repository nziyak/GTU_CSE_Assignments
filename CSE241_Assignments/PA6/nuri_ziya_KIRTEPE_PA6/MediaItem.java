abstract class MediaItem implements Media
{
    private String name;
    private String other_info;

    public MediaItem(String name, String other_info)
    {
        this.name = name;
        this.other_info = other_info;
    }

    public String get_name()
    {
        return name;
    }

    public String get_other_info()
    {
        return other_info;
    }

    public abstract void info();
}