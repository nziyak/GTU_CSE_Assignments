import java.util.ArrayList;
import java.util.List;

class Viewer implements Observer
{
    private List<NonPlayable> view_list = new ArrayList<>();
    private int currentIndex = 0;

    @Override
    public void update(Media media)
    {
        if(view_list.contains((NonPlayable) media)) //if Viewer already knows the notified media, notification is because of removing media from database
        {    
            if(media == view_list.get(currentIndex)) //if the to be deleted media was the currently viewed 
            {
                try 
                {
                    if(view_list.size() == 1) //if no medias will be left after the deletion, throw an exception
                    {
                        throw new Exception("no next media to play!");
                    }

                    else // if there are still elements in view_list, view next media
                    {
                        if(media instanceof Text) //TODO: WRITE AN SECOND NEXT FUNC TO HANDLE DONT CHANGING CURRENT INDEX
                        {
                            next("text");
                        }
                        
                        else if(media instanceof Image)
                        {
                            next("image");
                        }

                        --currentIndex;
                    }
                } 
                catch (Exception n) 
                {
                    System.out.println("NO_NEXT_MEDIA_EXCPT: " + n.getMessage());
                }
            }

            view_list.remove((NonPlayable) media); //remove media from play list of the player
        }
            
        else  //if viewer does not know about media, it means notification is for adding media
            view_list.add((NonPlayable) media); //then add media to play list of the player
    }

    public void show_list()
    {
        for(NonPlayable p : view_list)
        {
            p.info();
        }
    }

    public NonPlayable currently_viewing()
    {
        return view_list.get(currentIndex); //return the current object
    }

    public void next(String type)
    {
        try 
        {
            if (view_list.size() == 1) //if there is just one element in view_list throw an exception
            {
                throw new Exception("there is only one media in view list!");
            }
        } 
        catch (Exception o) 
        {
            System.out.println("ONE_MEDIA_EXCPT: " + o.getMessage());
            return; //do not execute viewing next element lines
        }

        try 
        {
            if (currentIndex == view_list.size() - 1) //if currently viewed element is the last element in view_list throw an exception
            {
                throw new Exception("currently viewed media is the last media of view list!");
            }
        } 
        catch (Exception l) 
        {
            System.out.println("LAST_MEDIA_EXCPT: " + l.getMessage());
            return; //do not execute viewing next element lines
        }

        int i;
        boolean isCurrentLast; //is the currently viewed element is the last element
        
        type = type.toLowerCase();

        if(type.equals("text"))
        {
            isCurrentLast = true;

            try 
            {
                for(i = currentIndex+1; i < view_list.size(); i++) //start from the next media and search for the next text 
                {
                    if(view_list.get(i) instanceof Text) //if viewable at i is instance of Text
                    {
                        currentIndex = i; //assign current index as that index and break
                        isCurrentLast = false; //currently viewed is not the last text
                        break;
                    } 
                }

                if(isCurrentLast) //if the currently viewed text is the last text
                {
                    throw new Exception("no next text to view!");
                }
            } 
            catch (Exception n) 
            {
                System.out.println("NO_NEXT_TEXT_EXCPT: " + n.getMessage());
                return; //do not execute viewing next element lines
            }
        }

        else if(type.equals("image"))
        {
            isCurrentLast = true;
            
            try 
            {
                for(i = currentIndex+1; i < view_list.size(); i++) //start from the next media and search for the next image 
                {
                    if(view_list.get(i) instanceof Image) //if viewable at i is instance of Image
                    {
                        currentIndex = i; //assign current index as that index and break
                        isCurrentLast = false; //currently viewed is not the last image
                        break;
                    } 
                }

                if(isCurrentLast)//if the currently viewed audio is the last audio
                {
                    throw new Exception("no next image to view!");
                }
            } 
            catch (Exception n) 
            {
                System.out.println("NO_NEXT_IMAGE_EXCPT: " + n.getMessage());
                return; //do not execute viewing next element lines
            }
        }
    }

    public void previous(String type)
    {
        try 
        {
            if (view_list.size() == 1) //if there is just one element in view_list throw an exception
            {
                throw new Exception("there is only one media in view list!");
            }
        } 
        catch (Exception o) 
        {
            System.out.println("ONE_MEDIA_EXCPT: " + o.getMessage());
            return; //do not execute viewing next element lines
        }
        
        try 
        {
            if (currentIndex == 0) //if currently viewed element is the first element in view_list throw an exception
            {
                throw new Exception("currently viewed media is the first media of view list!");
            }
        } 
        catch (Exception f) 
        {
            System.out.println("FIRST_MEDIA_EXCPT: " + f.getMessage());
        }
        
        int i;

        type = type.toLowerCase();

        if(type.equals("text"))
        {
            for(i = currentIndex-1; i > 0; i--) //search for the next audio object 
            {
                if(view_list.get(i) instanceof Text) //if viewable at i is instance of Text
                {
                    currentIndex = i;
                    break;
                } 
            }
        }

        else if(type.equals("image"))
        {
            for(i = currentIndex-1; i > 0; i--) //search for the next audio object 
            {
                if(view_list.get(i) instanceof Image) //if viewable at i is instance of Image
                {
                    currentIndex = i;
                    break;
                } 
            }
        }
    }
}
