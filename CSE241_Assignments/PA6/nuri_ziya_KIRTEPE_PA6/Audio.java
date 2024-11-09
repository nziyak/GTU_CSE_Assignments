class Audio extends MediaItem implements NonVisual, Playable
{
    private String duration;
    
    public Audio(String audio_name, String duration, String other_info)
    {
        super(audio_name, other_info);
        this.duration = duration;
    }

    @Override
    public void info()
    {
        System.out.println("audio_name: " + get_name() + ", duration: " + duration + ", info: " + get_other_info());
    }

    @Override
    public void play()
    {
        System.out.println("playing audio: " + get_name());
    }
}