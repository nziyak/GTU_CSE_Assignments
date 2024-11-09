class Video extends MediaItem implements Visual, Playable
{
    private String duration;
    
    public Video(String audio_name, String duration, String other_info)
    {
        super(audio_name, other_info);
        this.duration = duration;
    }

    @Override
    public void info()
    {
        System.out.println("video_name: " + get_name() + ", duration: " + duration + ", info: " + get_other_info());
    }

    @Override
    public void play()
    {
        System.out.println("playing video: " + get_name());
    }
}