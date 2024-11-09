class Image extends MediaItem implements Visual, NonPlayable
{
    private String dimension;
    
    public Image(String image_name, String dimension, String other_info)
    {
        super(image_name, other_info);
        this.dimension = dimension;
    }

    @Override
    public void info()
    {
        System.out.println("image_name: " + get_name() + ", dimension: " + dimension + ", info: " + get_other_info());
    }

    @Override
    public void view()
    {
        System.out.println("viewing text: " + get_name());
    }
}