class Text extends MediaItem implements NonVisual, NonPlayable
{
    public Text(String text_name, String other_info)
    {
        super(text_name, other_info);
    }

    @Override
    public void info()
    {
        System.out.println("text_name: " + get_name() + ", info: " + get_other_info());
    }

    @Override
    public void view()
    {
        System.out.println("viewing text: " + get_name());
    }
}