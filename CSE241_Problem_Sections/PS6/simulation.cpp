#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <time.h>

using namespace std;

// Sabitler tanımlanıyor
const int WORLDSIZE = 20;
const int INITIALANTS = 100;
const int INITIALBUGS = 5;
const int DOODLEBUG = 1;
const int ANT = 2;
const int ANTBREED = 3;
const int DOODLEBREED = 8;
const int DOODLESTARVE = 3;

// Sınıflar tanımlanıyor
class Organism;
class Doodlebug;
class Ant;

// Dünya sınıfı tanımlanıyor
class World
{
    friend class Organism; // Organism sınıfına ızgara erişim izni veriliyor
    friend class Doodlebug; // Organism sınıfına ızgara erişim izni veriliyor
    friend class Ant; // Organism sınıfına ızgara erişim izni veriliyor
public:
    World(); // Dünya sınıfı kurucusu
    ~World(); // Dünya sınıfı yıkıcısı
    Organism* getAt(int x, int y); // Belirtilen konumdaki organizmayı al
    void setAt(int x, int y, Organism *org); // Belirtilen konuma bir organizma yerleştir
    void Display(); // Dünyayı ekrana yazdır
    void SimulateOneStep(); // Bir adım simülasyon yap
private:
    Organism* grid[WORLDSIZE][WORLDSIZE]; // Dünya ızgarası
};

// Organism (Canlı) sınıfı tanımlanıyor
class Organism
{
    friend class World;
public:
    Organism(); // Canlı sınıfı kurucusu
    Organism(World *world, int x, int y); // Canlı sınıfı kurucusu (parametrelerle)
    virtual ~Organism(); // Sanal yıkıcı
    virtual void breed() = 0; // Üremek için sanal fonksiyon
    virtual void move() = 0; // Hareket etmek için sanal fonksiyon
    virtual int getType() =0; // Türü almak için sanal fonksiyon
    virtual bool starve() = 0; // Açlıktan ölmek için sanal fonksiyon
protected:
    int x,y; // Konum
    bool moved; // Hareket etmiş mi?
    int breedTicks; // Üreme zamanlayıcısı
    World *world; // Dünya nesnesi
};

// Dünya sınıfı kurucusu
World::World()
{
    // Dünyayı boş hücrelerle başlat
    for (int i=0; i<WORLDSIZE; i++)
    {
        for (int j=0; j<WORLDSIZE; j++)
        {
            grid[i][j]=NULL;
        }
    }
}

// Dünya sınıfı yıkıcısı
World::~World()
{
    // Ayrılmış belleği serbest bırak
    for (int i=0; i<WORLDSIZE; i++)
    {
        for (int j=0; j<WORLDSIZE; j++)
        {
            if (grid[i][j]!=NULL) delete (grid[i][j]);
        }
    }
}

// Belirtilen konumdaki organizmayı al
Organism* World::getAt(int x, int y)
{
    if ((x>=0) && (x<WORLDSIZE) && (y>=0) && (y<WORLDSIZE))
        return grid[x][y];
    return NULL;
}

// Belirtilen konuma bir organizma yerleştir
void World::setAt(int x, int y, Organism *org)
{
    if ((x>=0) && (x<WORLDSIZE) && (y>=0) && (y<WORLDSIZE))
    {
        grid[x][y] = org;
    }
}

// Dünyayı ekrana yazdır
void World::Display()
{
    cout << endl << endl;
    for (int j=0; j<WORLDSIZE; j++)
    {
        for (int i=0; i<WORLDSIZE; i++)
        {
            if (grid[i][j]==NULL)
                cout << ".";
            else if (grid[i][j]->getType()==ANT)
                cout << "o";
            else
                cout << "X";
        }
        cout << endl;
    }
}

// Bir adım simülasyon yap
void World::SimulateOneStep()
{
    // Önce tüm organizmaların hareket etmediğini sıfırla
    for (int i=0; i<WORLDSIZE; i++)
        for (int j=0; j<WORLDSIZE; j++)
        {
            if (grid[i][j]!=NULL) grid[i][j]->moved = false;
        }
    // Hücreleri sırayla dolaş ve eğer bir yırtıcı böcekse hareket et
    for (int i=0; i<WORLDSIZE; i++)
        for (int j=0; j<WORLDSIZE; j++)
        {
            if ((grid[i][j]!=NULL) && (grid[i][j]->getType()==DOODLEBUG))
            {
                if (grid[i][j]->moved == false)
                {
                    grid[i][j]->moved = true; // Hareket etti olarak işaretle
                    grid[i][j]->move();
                }
            }
        }
    // Hücreleri sırayla dolaş ve eğer bir karınca ise hareket et
    for (int i=0; i<WORLDSIZE; i++)
        for (int j=0; j<WORLDSIZE; j++)
        {
            if ((grid[i][j]!=NULL) && (grid[i][j]->getType()==ANT))
            {
                if (grid[i][j]->moved == false)
                {
                    grid[i][j]->moved = true; // Hareket etti olarak işaretle
                    grid[i][j]->move();
                }
            }
        }
    // Hücreleri sırayla dolaş ve aç kalan yırtıcı böcekleri öldür
    for (int i=0; i<WORLDSIZE; i++)
        for (int j=0; j<WORLDSIZE; j++)
        {
            if ((grid[i][j]!=NULL) && (grid[i][j]->getType()==DOODLEBUG))
            {
                if (grid[i][j]->starve())
                {
                    delete (grid[i][j]);
                    grid[i][j] = NULL;
                }
            }
        }
    // Hücreleri sırayla dolaş ve üremesi gerekenleri üret
    for (int i=0; i<WORLDSIZE; i++)
        for (int j=0; j<WORLDSIZE; j++)
        {
            // Sadece hareket etmiş organizmaları üret, çünkü
            // üreme yeni organizmaları haritaya yerleştiririz
            // onları üretmeye çalışmak istemeyiz
            if ((grid[i][j]!=NULL) && (grid[i][j]->moved==true))
            {
                grid[i][j]->breed();
            }
        }
}

// Organism (Canlı) sınıfı kurucusu
Organism::Organism()
{
    world = NULL;
    moved = false;
    breedTicks = 0;
    x=0;
    y=0;
}

// Organism (Canlı) sınıfı kurucusu (parametrelerle)
Organism::Organism(World *wrld, int x, int y)
{
    this->world = wrld;
    moved = false;
    breedTicks = 0;
    this->x=x;
    this->y=y;
    wrld->setAt(x,y,this);
}

// Organism (Canlı) sınıfı yıkıcısı
Organism::~Organism()
{
}

// Karınca sınıfı tanımlanıyor
class Ant : public Organism
{
    friend class World;
public:
    Ant(); // Karınca sınıfı kurucusu
    Ant(World *world, int x, int y); // Karınca sınıfı kurucusu (parametrelerle)
    void breed(); // Üremek için fonksiyon
    void move(); // Hareket etmek için fonksiyon
    int getType(); // Türü almak için fonksiyon
    bool starve() // Açlıktan ölmek için fonksiyon
    { return false; }
};

// Karınca sınıfı kurucusu
Ant::Ant() : Organism()
{
}

// Karınca sınıfı kurucusu (parametrelerle)
Ant::Ant(World *world, int x, int y) : Organism(world,x,y)
{
}

// Karıncanın hareket etmesi
void Ant::move()
{
    int dir = rand() % 4;
    if (dir==0) //to left
    {
        if ((y>0) && (world->getAt(x,y-1)==NULL))
        {
            world->setAt(x,y-1,world->getAt(x,y)); 
            world->setAt(x,y,NULL);
            y--;
        }
    }
   
    else if (dir==1) //to right
    {
        if ((y<WORLDSIZE-1) && (world->getAt(x,y+1)==NULL))
        {
            world->setAt(x,y+1,world->getAt(x,y)); 
            world->setAt(x,y,NULL); 
            y++;
        }
    }
    
    else if (dir==2) //to up
    {
        if ((x>0) && (world->getAt(x-1,y)==NULL))
        {
            world->setAt(x-1,y,world->getAt(x,y)); 
            world->setAt(x,y,NULL); 
            x--;
        }
    }
    
    else //to down
    {
        if ((x<WORLDSIZE-1) && (world->getAt(x+1,y)==NULL))
        {
            world->setAt(x+1,y,world->getAt(x,y)); 
            world->setAt(x,y,NULL); 
            x++;
        }
    }
}

// Karıncanın türünü al
int Ant::getType()
{
    return ANT;
}

// Karıncanın üremesi
void Ant::breed()
{
    breedTicks++;
    if (breedTicks == ANTBREED)
    {
        breedTicks = 0;
        
        if ((y>0) && (world->getAt(x,y-1)==NULL))
        {
            Ant *newAnt = new Ant(world, x, y-1);
        }
        else if ((y<WORLDSIZE-1) && (world->getAt(x,y+1)==NULL))
        {
            Ant *newAnt = new Ant(world, x, y+1);
        }
        else if ((x>0) && (world->getAt(x-1,y)==NULL))
        {
            Ant *newAnt = new Ant(world, x-1, y);
        }
        else if ((x<WORLDSIZE-1) && (world->getAt(x+1,y)==NULL))
        {
            Ant *newAnt = new Ant(world, x+1, y);
        }
    }
}

// Yırtıcı böcek sınıfı tanımlanıyor
class Doodlebug : public Organism
{
    friend class World;
public:
    Doodlebug(); // Yırtıcı böcek sınıfı kurucusu
    Doodlebug(World *world, int x, int y); // Yırtıcı böcek sınıfı kurucusu (parametrelerle)
    void breed(); // Üremek için fonksiyon
    void move(); // Hareket etmek için fonksiyon
    int getType(); // Türü almak için fonksiyon
    bool starve(); // Açlıktan ölmek için fonksiyon
private:
    int starveTicks; // Açlık sayacı
};

// Yırtıcı böcek sınıfı kurucusu
Doodlebug::Doodlebug() : Organism()
{
    starveTicks = 0;
}

// Yırtıcı böcek sınıfı kurucusu (parametrelerle)
Doodlebug::Doodlebug(World *world, int x, int y) : Organism(world,x,y)
{
    starveTicks = 0;
}

// Yırtıcı böceğin hareket etmesi
void Doodlebug::move()
{
    
    if ((y>0) && (world->getAt(x,y-1)!=NULL) &&
        (world->getAt(x,y-1)->getType() == ANT))
    {
        delete (world->grid[x][y-1]); 
        world->grid[x][y-1] = this; 
        world->setAt(x,y,NULL);
        starveTicks =0 ; 
        y--;
        return;
    }
    else if ((y<WORLDSIZE-1) && (world->getAt(x,y+1)!=NULL) &&
             (world->getAt(x,y+1)->getType() == ANT))
    {
        delete (world->grid[x][y+1]); 
        world->grid[x][y+1] = this; 
        world->setAt(x,y,NULL);
        starveTicks =0 ; 
        y++;
        return;
    }
    else if ((x>0) && (world->getAt(x-1,y)!=NULL) &&
             (world->getAt(x-1,y)->getType() == ANT))
    {
        delete (world->grid[x-1][y]); 
        world->grid[x-1][y] = this;
        world->setAt(x,y,NULL);
        starveTicks =0 ; 
        x--;
        return;
    }
    else if ((x<WORLDSIZE-1) && (world->getAt(x+1,y)!=NULL) &&
             (world->getAt(x+1,y)->getType() == ANT))
    {
        delete (world->grid[x+1][y]); 
        world->grid[x+1][y] = this; 
        world->setAt(x,y,NULL);
        starveTicks =0 ; 
        x++;
        return;
    }

    int dir = rand() % 4;
  
    if (dir==0)
    {
        if ((y>0) && (world->getAt(x,y-1)==NULL))
        {
            world->setAt(x,y-1,world->getAt(x,y)); // Yeni bir yere taşı
            world->setAt(x,y,NULL);
            y--;
        }
    }
   
    else if (dir==1)
    {
        if ((y<WORLDSIZE-1) && (world->getAt(x,y+1)==NULL))
        {
            world->setAt(x,y+1,world->getAt(x,y));
            world->setAt(x,y,NULL); 
            y++;
        }
    }
    // Sol yöne gitmeyi dene
    else if (dir==2)
    {
        if ((x>0) && (world->getAt(x-1,y)==NULL))
        {
            world->setAt(x-1,y,world->getAt(x,y)); 
            world->setAt(x,y,NULL); 
            x--;
        }
    }
    
    else
    {
        if ((x<WORLDSIZE-1) && (world->getAt(x+1,y)==NULL))
        {
            world->setAt(x+1,y,world->getAt(x,y)); 
            world->setAt(x,y,NULL); 
            x++;
        }
    }
    starveTicks++; 
    
}

// Yırtıcı böceğin türünü al
int Doodlebug::getType()
{
    return DOODLEBUG;
}

// Yırtıcı böceğin üremesi
void Doodlebug::breed()
{
    breedTicks++;
    if (breedTicks == DOODLEBREED)
    {
        breedTicks = 0;
     
        if ((y>0) && (world->getAt(x,y-1)==NULL))
        {
            Doodlebug *newDoodle = new Doodlebug(world, x, y-1);
        }
        else if ((y<WORLDSIZE-1) && (world->getAt(x,y+1)==NULL))
        {
            Doodlebug *newDoodle = new Doodlebug(world, x, y+1);
        }
        else if ((x>0) && (world->getAt(x-1,y)==NULL))
        {
            Doodlebug *newDoodle = new Doodlebug(world, x-1, y);
        }
        else if ((x<WORLDSIZE-1) && (world->getAt(x+1,y)==NULL))
        {
            Doodlebug *newDoodle = new Doodlebug(world, x+1, y);
        }
    }
}

// Açlık durumunu kontrol et
bool Doodlebug::starve()
{
    if (starveTicks > DOODLESTARVE)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Ana fonksiyon
int main()
{
    string s;
    srand(time(NULL)); 
    World w;

    // Başlangıçta karınca sayısı kadar karınca yerleştir
    int antcount = 0;
    while (antcount < INITIALANTS)
    {
        int x = rand() % WORLDSIZE;
        int y = rand() % WORLDSIZE;
        if (w.getAt(x,y)==NULL) 
        {
            antcount++;
            Ant *a1 = new Ant(&w,x,y);
        }
    }
    // Başlangıçta yırtıcı böcek sayısı kadar yırtıcı böcek yerleştir
    int doodlecount = 0;
    while (doodlecount < INITIALBUGS)
    {
        int x = rand() % WORLDSIZE;
        int y = rand() % WORLDSIZE;
        if (w.getAt(x,y)==NULL) 
        {
            doodlecount++;
            Doodlebug *d1 = new Doodlebug(&w,x,y);
        }
    }

    // Sonsuz döngü: Her adımda dünyayı göster ve bir adım simüle et
    while (true)
    {
        w.Display();
        w.SimulateOneStep();
        cout << endl << "Press enter for next step" << endl;
        getline(cin,s);
    }
    return 0;
}
