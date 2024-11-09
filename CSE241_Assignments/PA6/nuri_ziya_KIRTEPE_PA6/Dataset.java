import java.util.ArrayList;
import java.util.List;

class Dataset implements Subject
{
    private List<Media> medias = new ArrayList<>();
    
    private List<Observer> players = new ArrayList<>();
    private List<Observer> viewers = new ArrayList<>();
    
    @Override 
    public void register(Observer observer)
    {
        if(observer instanceof Player) //if observer is type of Player
            players.add(observer); //add observer to players
        
        else if(observer instanceof Viewer) //if observer is type of Viewer
            viewers.add(observer); //add observer to viewers
    }

    @Override 
    public void unregister(Observer observer)
    {
        if(observer instanceof Player) //if observer is type of Player
            players.remove(observer); //remove observer from players
        
        else if(observer instanceof Viewer) //if observer is type of Viewer
            viewers.remove(observer); //remove observer from viewers
    }

    @Override 
    public void notify(Media media)
    {
        if(media instanceof Playable) //if media is Playable
        {
            for(Observer player : players) //notify just Players
            {
                player.update(media);
            }
        }
        
        else if(media instanceof NonPlayable) //if media is NonPlayable   
        {
            for(Observer viewer : viewers) //notify just Viewers
            {
                viewer.update(media);
            }
        }
    }

    public void add(Media media)
    {
        medias.add(media); 
        notify(media);
    }

    public void remove(Media media)
    {
        medias.remove(media);
        notify(media);
    }

    public List<Media> get_medias() 
    {
        return medias;
    }

    public void show_media_list()
    {
        for(Media media : medias)
        {
            media.info();
        }
    }
}