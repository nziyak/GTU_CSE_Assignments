import java.util.ArrayList;
import java.util.List;

class Player implements Observer
{
    private List<Playable> play_list = new ArrayList<>();
    private int currentIndex = 0;

    @Override
    public void update(Media media)
    {
        if(play_list.contains((Playable) media)) //if Player already knows the notified media, notification is because of removing media from database
        {
            if(media == play_list.get(currentIndex)) //if the to be deleted media was the currently played 
            {
                try 
                {
                    if(play_list.size() == 1) //if no medias will be left after the deletion, throw an exception
                    {
                        throw new Exception("no next media to play!");
                    }

                    else // if there are still elements in play_list, play next media
                    {
                        if(media instanceof Audio)
                        {
                            next("audio");
                        }
                        
                        else if(media instanceof Video)
                        {
                            next("video");
                        }

                        --currentIndex;
                    }
                } 
                catch (Exception n) 
                {
                    System.out.println("NO_NEXT_MEDIA_EXCPT: " + n.getMessage());
                }
            }

            play_list.remove((Playable) media); //remove media from play list of the player
        }   
            
        else  //if player does not know about media, it means notification is for adding media
            play_list.add((Playable) media); //then add media to play list of the player
    }

    public void show_list()
    {
        for(Playable p : play_list)
        {
            p.info();
        }
    }

    public Playable currently_playing()
    {
        return play_list.get(currentIndex); //return the current object
    }

    public void next(String type)
    {
        try 
        {
            if (play_list.size() == 1) //if there is just one element in play_list throw an exception
            {
                throw new Exception("there is only one media in play list!");
            }
        } 
        catch (Exception o) 
        {
            System.out.println("ONE_MEDIA_EXCPT: " + o.getMessage());
            return; //do not execute playing next element lines
        }

        try 
        {
            if (currentIndex == play_list.size() - 1) //if currently played element is the last element in play_list throw an exception
            {
                throw new Exception("currently played media is the last media of play list!");
            }
        } 
        catch (Exception l) 
        {
            System.out.println("LAST_MEDIA_EXCPT: " + l.getMessage());
            return; //do not execute playing next element lines
        }

        int i;
        boolean isCurrentLast; //is the currently played element is the last element

        type = type.toLowerCase();

        if(type.equals("audio"))
        {
            isCurrentLast = true;

            try 
            {
                for(i = currentIndex+1; i < play_list.size(); i++) //start from the next media and search for the next audio 
                {
                    if(play_list.get(i) instanceof Audio) //if playable at i is instance of Audio
                    {
                        currentIndex = i; //assign current index as that index and break
                        isCurrentLast = false; //currently played is not the last audio
                        break;
                    } 
                }

                if(isCurrentLast) //if the currently played audio is the last audio
                {
                    throw new Exception("no next audio to play!");
                }
            } 
            catch (Exception n) 
            {
                System.out.println("NO_NEXT_AUDIO_EXCPT: " + n.getMessage());
                return; //do not execute playing next element lines
            }
        }

        else if(type.equals("video"))
        {
            isCurrentLast = true;
            
            try 
            {
                for(i = currentIndex+1; i < play_list.size(); i++) //start from the next media and search for the next video 
                {
                    if(play_list.get(i) instanceof Video) //if playable at i is instance of Video
                    {
                        currentIndex = i; //assign current index as that index and break
                        isCurrentLast = false; //currently played is not the last video
                        break;
                    } 
                }

                if(isCurrentLast)//if the currently played audio is the last audio
                {
                    throw new Exception("no next video to play!");
                }
            } 
            catch (Exception n) 
            {
                System.out.println("NO_NEXT_VIDEO_EXCPT: " + n.getMessage());
                return; //do not execute playing next element lines
            }
        }
    }

    public void previous(String type)
    {
        try 
        {
            if (play_list.size() == 1) //if there is just one element in play_list throw an exception
            {
                throw new Exception("there is only one media in play list!");
            }
        } 
        catch (Exception o) 
        {
            System.out.println("ONE_MEDIA_EXCPT: " + o.getMessage());
            return; //do not execute playing next element lines
        }
        
        try 
        {
            if (currentIndex == 0) //if currently played element is the first element in play_list throw an exception
            {
                throw new Exception("currently played media is the first media of play list!");
            }
        } 
        catch (Exception f) 
        {
            System.out.println("FIRST_MEDIA_EXCPT: " + f.getMessage());
        }
        
        int i;

        type = type.toLowerCase();
        System.out.println("prev for:" + i);
        if(type.equals("audio"))
        {
            for(i = currentIndex-1; i > -1; i--) //search for the previous audio object 
            {
                if(play_list.get(i) instanceof Audio) //if playable at i is instance of Audio
                {
                    currentIndex = i; //assign current index as that index and break
                    System.out.println(i);
                    break;
                } 
            }
        }

        else if(type.equals("video"))
        {
            for(i = currentIndex-1; i > -1; i--) //search for the previous video object 
            {
                if(play_list.get(i) instanceof Video) //if playable at i is instance of Video 
                {
                    currentIndex = i; //assign current index as that index and break
                    System.out.println(i);
                    break;
                } 
            }
        }
        System.out.println("after for:" + i);
    }
}
