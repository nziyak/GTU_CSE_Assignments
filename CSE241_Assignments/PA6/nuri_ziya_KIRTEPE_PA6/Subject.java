interface Subject
{
    void register(Observer observer);
    void unregister(Observer observer);
    void notify(Media media);
}