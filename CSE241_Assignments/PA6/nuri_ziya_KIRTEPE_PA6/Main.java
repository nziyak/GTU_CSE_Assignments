public class Main
{
    public static void main(String[] args)
    {
        Dataset ds = new Dataset();

        Player p1 = new Player();
        Player p2 = new Player();
        Viewer v1 = new Viewer();

        ds.register(p1);
        ds.register(p2);
        ds.register(v1);
        
        /*ds.add(new Audio("audioname1", "duration1", "other info1"));
        ds.add(new Video("videoname1", "duration1", "other info1"));
        ds.add(new Audio("audioname2", "duration2", "other info2"));
        ds.add(new Video("videoname2", "duration2", "other info2"));
        ds.add(new Audio("audioname3", "duration3", "other info3"));
        ds.add(new Video("videoname3", "duration3", "other info3"));
        
        ds.add(new Text("textname1", "other info1"));
        ds.add(new Image("imagename1", "dimensioninfo1", "other info1"));
        ds.add(new Text("textname2", "other info2"));
        ds.add(new Image("imagename2", "dimensioninfo2", "other info2"));
        ds.add(new Text("textname3", "other info3"));*/

        ds.add(new Audio("audioname1", "duration1", "other info1"));
        ds.add(new Video("videoname3", "duration3", "other info3"));
        ds.add(new Audio("audioname3", "duration3", "other info3"));
        ds.add(new Video("videoname1", "duration1", "other info1"));
        ds.add(new Audio("audioname2", "duration2", "other info2"));
        ds.add(new Video("videoname2", "duration2", "other info2"));
        ds.add(new Text("textname1", "other info1"));
        ds.add(new Image("imagename1", "dimensioninfo1", "other info1"));
        ds.add(new Text("textname2", "other info2"));
        ds.add(new Image("imagename2", "dimensioninfo2", "other info2"));
        ds.add(new Text("textname3", "other info3"));

        System.out.println("P1's playlist: ");
        p1.show_list();
        System.out.println("P2's playlist: ");
        p1.show_list();

        System.out.println("Currently playing at P1: ");
        p1.currently_playing().info();

        System.out.println("Playing next Audio at P1: ");
        p1.next("Audio");
        p1.currently_playing().info();

        System.out.println("Playing next Video at P1: ");
        p1.next("Video");
        p1.currently_playing().info();

        System.out.println("Playing previous Audio at P1: ");
        p1.previous("Audio");
        p1.currently_playing().info();

        System.out.println("Playing next Audio at P1: ");
        p1.next("Audio");
        p1.currently_playing().info();

        System.out.println("Playing next Audio at P1: ");
        p1.next("Audio");
        p1.currently_playing().info();

        System.out.println("Playing next Video at P1: ");
        p1.next("Video");
        p1.currently_playing().info();

        System.out.println("Playing next Video at P1: ");
        p1.next("Video");
        p1.currently_playing().info();

        System.out.println("Playing next Video at P1: ");
        p1.next("Video");
        p1.currently_playing().info();

        System.out.println("Playing next Audio at P1: ");
        p1.next("Audio");
        p1.currently_playing().info();

        System.out.println("Removing currently playing and after that currently playing is: ");
        ds.remove(p1.currently_playing());
        p1.currently_playing().info();

        System.out.println("Removing currently playing and after that currently playing is: ");
        ds.remove(p1.currently_playing());
        p1.currently_playing().info();

        System.out.println("After deletions P1's playlist: ");
        p1.show_list();

        System.out.println("P2's playlist: ");
        p2.show_list();

        System.out.println("Currently playing at P2");
        p2.currently_playing().info();

        System.out.println("P2 is unregistered.\n");
        ds.unregister(p2);
    }
}
