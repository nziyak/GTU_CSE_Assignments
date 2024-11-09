#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>

using namespace std;

const int ARENASIZE = 10;
const int INITCOUNT = 5;

const int OPTIMUSPRIME = 0;
const int ROBOCOP = 1;
const int ROOMBA = 2;
const int BULLDOZER = 3;
const int KAMIKAZE = 4;

const int OPTIMUSPRIME_STRENGTH = 100;
const int ROBOCOP_STRENGTH = 30;
const int ROOMBA_STRENGTH = 3;
const int BULLDOZER_STRENGTH = 50;
const int KAMIKAZE_STRENGTH = 10;

const int OPTIMUSPRIME_HP = 100;
const int ROBOCOP_HP = 40;
const int ROOMBA_HP = 10;
const int BULLDOZER_HP = 200;
const int KAMIKAZE_HP = 10;

const int UP = 1;
const int DOWN = 2;
const int RIGHT = 3;
const int LEFT = 4;

class Robot;
class Humanic;
class OptimusPrime;
class RoboCop;
class Roomba;
class Bulldozer;
class Kamikaze;

class Arena
{
    friend class Robot;
    friend class Humanic;
    friend class OptimusPrime;
    friend class RoboCop;
    friend class Roomba;
    friend class Bulldozer;
    friend class Kamikaze;

public:

    Arena();
    ~Arena(); 
    Robot* getAt(int x, int y); 
    void setAt(int x, int y, Robot *org); 
    void Display(); 
    void SimulateOneStep();
    int duel(Robot* attacker, Robot* victim);
    void hit_message(Robot* attacker, Robot* defender, int damage_inflicted, int hpBeforeAttackk);

private:

    Robot* grid[ARENASIZE][ARENASIZE]; 
};

class Robot
{
    friend class Arena;

    public:    
        
        Robot();
        Robot(Arena* arena, int X, int Y);
        Robot(Arena* arena, int X, int Y, int Strength, int HP); // Initialize robot to new type, strength, hit points
        virtual ~Robot() {};
        virtual int getType() = 0;
        virtual int getStrength() = 0;
        virtual int getHP() = 0;
        virtual int getDamage(); // Returns amount of damage this robot inflicts in one round of combat
        void move();
        int isNearby(int X, int Y);

    protected:    
        
        int x,y; //position
        int strength;
        int hp;
        bool moved;
        string name;
        Arena* arena;
};

Arena::Arena()
{
    for (int i = 0; i < ARENASIZE; i++)
    {
        for (int j = 0; j < ARENASIZE; j++)
        {
            grid[i][j] = NULL;
        }
    }
}

Arena::~Arena()
{
    for (int i=0; i < ARENASIZE; i++)
    {
        for (int j=0; j < ARENASIZE; j++)
        {
            if (grid[i][j]!=NULL) delete (grid[i][j]);
        }
    }
}

Robot* Arena::getAt(int x, int y)
{
    if ((x >= 0) && (x < ARENASIZE) && (y >= 0) && (y < ARENASIZE))
        return grid[x][y];
    return NULL;
}

void Arena::setAt(int x, int y, Robot *robot)
{
    if ((x >= 0) && (x < ARENASIZE) && (y >= 0) && (y < ARENASIZE))
    {
        grid[x][y] = robot;
    }
}

void Arena::Display()
{
    cout << endl << endl;
    for (int j=0; j<ARENASIZE; j++)
    {
        for (int i=0; i<ARENASIZE; i++)
        {
            if (grid[i][j]==NULL)
                cout << " . ";
            else 
                cout << " " << grid[i][j]->name << " ";
        }
        cout << endl << endl;
    }
}

void Arena::SimulateOneStep()
{
    for (int i=0; i<ARENASIZE; i++)
    {
        for (int j=0; j<ARENASIZE; j++)
        {
            if (grid[i][j]!=NULL) 
                grid[i][j]->moved = false;
        }
    }

    //look at every cell and move if not null
    for (int i=0; i < ARENASIZE; i++)
    {    
        for (int j=0; j < ARENASIZE; j++)
        {
            if ((grid[i][j] != NULL))
            {
                if (grid[i][j]->moved == false)
                {
                    grid[i][j]->moved = true;
                    grid[i][j]->move();
                }
            }
        }
    }
}

int Arena::duel(Robot* attacker, Robot* defender) //TODO: MAKE A LOOP THAT ROBOTS FIGHT UNTIL ONE DIES
{
    int attackersDamage, defendersDamage;
    int hpBeforeAttack_a, hpBeforeAttack_d; //hp of the attacker before the attack of defender

    while((attacker->hp > 0) && (defender->hp > 0))
    {
        attackersDamage = attacker->getDamage();
        
        hpBeforeAttack_d = defender->hp;
        defender->hp -= attackersDamage;
        
        hit_message(attacker, defender, attackersDamage, hpBeforeAttack_d);

        if(defender->hp <= 0)
        {
            cout << defender->name << " died.\n";
            return 2; //defender died
        }

        defendersDamage = defender->getDamage();
        
        hpBeforeAttack_a = attacker->hp;
        attacker->hp -= defendersDamage;
        
        hit_message(defender, attacker, defendersDamage, hpBeforeAttack_a);

        if(attacker->hp <= 0)
        {
            cout << attacker->name << " died.\n";
            return 1; //attacker died 
        }
    }

    return 3; 
}

void Arena::hit_message(Robot* attacker, Robot* defender, int damage_inflicted, int hpBeforeAttackk)
{
    cout << attacker->name << "(" << attacker->hp << ")" << " hits " << defender->name << "(" << hpBeforeAttackk << ")"  << " with " << damage_inflicted << endl;
}

Robot::Robot()
{
    arena = NULL;
    moved = false;
    strength = 0;
    hp = 0;
    x = 0;
    y = 0;
}

Robot::Robot(Arena* arena, int X, int Y)
{
    this->arena = arena;
    moved = false;
    this->x=X;
    this->y=Y;
    arena->setAt(x,y,this);
}

int Robot::getDamage()
{
    return rand() % strength + 1;
}

void Robot::move()
{
    int nearby = isNearby(x, y); //look for is any robot nearby
    int deadCase; //stores which robot died
    int dir; //random direction
    
    while(!nearby)
    {    
        dir = rand() % 4;
    
        if (dir==0) //try move leftward
        {
            if ((y>0) && (arena->getAt(x,y-1)==NULL))
            {
                arena->setAt(x,y-1,arena->getAt(x,y)); 
                arena->setAt(x,y,NULL);
                y--;
            }

            else continue;
        }
    
        else if (dir==1) //try move rightward
        {
            if ((y<ARENASIZE-1) && (arena->getAt(x,y+1)==NULL))
            {
                arena->setAt(x,y+1,arena->getAt(x,y));
                arena->setAt(x,y,NULL); 
                y++;
            }

            else continue;
        }
        
        else if (dir==2) //try move upward
        {
            if ((x>0) && (arena->getAt(x-1,y)==NULL))
            {
                arena->setAt(x-1,y,arena->getAt(x,y)); 
                arena->setAt(x,y,NULL); 
                x--;
            }

            else continue;
        }
        
        else //try move downward
        {
            if ((x<ARENASIZE-1) && (arena->getAt(x+1,y)==NULL))
            {
                arena->setAt(x+1,y,arena->getAt(x,y)); 
                arena->setAt(x,y,NULL); 
                x++;
            }

            else continue;
        }

        moved = true;
        nearby = isNearby(x, y);
    }

    cout << nearby << endl;
    if (nearby == 1) //if opponent is at the upper cell
    {
        deadCase = arena->duel(arena->getAt(x,y), arena->getAt(x,y-1));
        cout << "deadCase:" << deadCase << endl;
        if(deadCase == 1)
        {
            delete (arena->grid[x][y]);
            arena->setAt(x,y,NULL);
        } 
        
        if(deadCase == 2)
        {
            delete (arena->grid[x][y-1]);
            arena->setAt(x,y-1,NULL);
        }

        return;
    }

    else if (nearby == 2)
    {
        deadCase = arena->duel(arena->getAt(x,y), arena->getAt(x,y+1));
        
        if(deadCase == 1)
        {
            delete (arena->grid[x][y]);
            arena->setAt(x,y,NULL);
        } 
        
        if(deadCase == 2)
        {
            delete (arena->grid[x][y+1]);
            arena->setAt(x,y-1,NULL);
        }

        return;
    }
    
    else if (nearby == 3)
    {
        deadCase = arena->duel(arena->getAt(x,y), arena->getAt(x-1,y));
        
        if(deadCase == 1)
        {
            delete (arena->grid[x][y]);
            arena->setAt(x,y,NULL);
        } 
        
        if(deadCase == 2)
        {
            delete (arena->grid[x-1][y]);
            arena->setAt(x,y-1,NULL);
        }

        return;
    }

    else if (nearby == 4)
    {
        deadCase = arena->duel(arena->getAt(x,y), arena->getAt(x+1,y));
        
        if(deadCase == 1)
        {
            delete (arena->grid[x][y]);
            arena->setAt(x,y,NULL);
        } 
        
        if(deadCase == 2)
        {
            delete (arena->grid[x+1][y]);
            arena->setAt(x,y-1,NULL);
        }

        return;
    }
}

int Robot::isNearby(int x, int y)
{
    if ((y>0) && (arena->getAt(x,y-1) != NULL)) //look at the upper cell
    {
        return 1;
    }

    else if ((y<ARENASIZE-1) && (arena->getAt(x,y+1) != NULL)) //look at the lower cell
    {
        return 2;
    }
    
    else if ((x>0) && (arena->getAt(x-1,y) != NULL))
    {
        return 3;
    }

    else if ((x<ARENASIZE-1) && (arena->getAt(x+1,y) != NULL))
    {
        return 4;
    }

    else 
        return 0;
}

class Humanic : public Robot
{
    friend class Arena;

    public:
        
        Humanic(); 
        Humanic(Arena* arena, int X, int Y);
        Humanic(Arena* arena, int X, int Y, int Strength, int HP);
        virtual ~Humanic() {};

        int getDamage();
};

Humanic::Humanic() : Robot()
{   
}

Humanic::Humanic(Arena* arena, int X, int Y) : Robot(arena, X, Y)
{
}

int Humanic::getDamage()
{
    int baseDamage = Robot::getDamage();

    if(rand() % 10 == 0)
        baseDamage += 50;

    return baseDamage;
}

class OptimusPrime : public Humanic
{
    friend class Arena;

    public:
        
        OptimusPrime();
        OptimusPrime(Arena* arena, int X, int Y);
        ~OptimusPrime() { numOP--; };
        int getDamage();
        int getType() { return OPTIMUSPRIME; };
        int getStrength() { return strength; };
        int getHP() { return hp; };

    private:

        static int numOP; //number of alive optimus primes
};

int OptimusPrime::numOP = 0;

OptimusPrime::OptimusPrime() : Humanic()
{ 
    numOP++;
    strength = OPTIMUSPRIME_STRENGTH;
    hp = OPTIMUSPRIME_HP; 
    //name = "optimus_" + to_string(numOP);
    name = "OP" + to_string(numOP);
}

OptimusPrime::OptimusPrime(Arena* arena, int X, int Y) : Humanic(arena, X, Y)
{
    numOP++;
    strength = OPTIMUSPRIME_STRENGTH;
    hp = OPTIMUSPRIME_HP; 
    //name = "optimus_" + to_string(numOP);
    name = "OP" + to_string(numOP);
}

int OptimusPrime::getDamage()
{
    int baseDamage = Humanic::getDamage();

    int isDouble = rand() % 101;   

    if((0 < isDouble) && (isDouble < 16))
        baseDamage *= 2; 

    return baseDamage;
}

class RoboCop : public Humanic
{
    friend class Arena;

    public:
        
        RoboCop(); 
        RoboCop(Arena* arena, int X, int Y);
        ~RoboCop() { numRC--; };
        int getDamage();
        int getType() { return ROBOCOP; };
        int getStrength() { return strength; };
        int getHP() { return hp; };
    
    private:

        static int numRC; //number of alive robocops
};

int RoboCop::numRC = 0;

RoboCop::RoboCop() : Humanic()
{ 
    numRC++; 
    strength = ROBOCOP_STRENGTH;
    hp = ROBOCOP_HP;
    //name = "robocop_" + to_string(numRC);
    name = "RC" + to_string(numRC);
}

RoboCop::RoboCop(Arena* arena, int X, int Y) : Humanic(arena, X, Y)
{
    numRC++;
    strength = OPTIMUSPRIME_STRENGTH;
    hp = OPTIMUSPRIME_HP; 
    //name = "robocop_" + to_string(numRC);
    name = "RC" + to_string(numRC);
}

int RoboCop::getDamage()
{
    int damage = Humanic::getDamage();
    return damage;
}

class Roomba : public Robot
{
    friend class Arena;

    public: 

        Roomba();
        Roomba(Arena *arena, int X, int Y);
        ~Roomba() { numRo--; };

        int getDamage();
        int getType() { return ROOMBA; };
        int getStrength() { return strength; };
        int getHP() { return hp; };
    
    private:

        static int numRo; //number of alive roombas    
};

int Roomba::numRo = 0;

Roomba::Roomba() : Robot()
{ 
    numRo++;
    strength = ROOMBA_STRENGTH;
    hp = ROOMBA_HP;
    //name = "roomba_" + to_string(numRo);
    name = "RO" + to_string(numRo);
}

Roomba::Roomba(Arena *arena, int X, int Y) : Robot(arena, X, Y)
{ 
    numRo++;
    strength = ROOMBA_STRENGTH;
    hp = ROOMBA_HP;
    //name = "roomba_" + to_string(numRo);
    name = "RO" + to_string(numRo);
}

int Roomba::getDamage()
{
    int damage = Robot::getDamage();
    damage += Robot::getDamage(); //calcul<te the damage of the second attack and add it
    return damage;
}

class Kamikaze : public Robot
{
    friend class Arena;

    public: 

        Kamikaze();
        Kamikaze(Arena *arena, int x, int y);
        ~Kamikaze() { numKa--; };

        int getDamage();
        int getType() { return KAMIKAZE; };
        int getStrength() { return strength; };
        int getHP() { return hp; };
        
    private:

        static int numKa; //number of alive kamikazes
};

int Kamikaze::numKa = 0;

Kamikaze::Kamikaze() : Robot()
{ 
    numKa++;
    strength = KAMIKAZE_STRENGTH;
    hp = KAMIKAZE_HP;
    //name = "kamikaze_" + to_string(numKa);
    name = "KA" + to_string(numKa);
}

Kamikaze::Kamikaze(Arena *arena, int X, int Y) : Robot(arena, X, Y)
{ 
    numKa++;
    strength = KAMIKAZE_STRENGTH;
    hp = KAMIKAZE_HP;
    //name = "kamikaze_" + to_string(numKa);
    name = "KA" + to_string(numKa);
}

int Kamikaze::getDamage()
{
    return this->hp;
}

class Bulldozer : public Robot
{
    friend class Arena;

    public: 

        Bulldozer();
        Bulldozer(Arena *arena, int x, int y);
        ~Bulldozer() { numBu--; };

        int getDamage();
        int getType() { return BULLDOZER; };
        int getStrength() { return strength; };
        int getHP() { return hp; };
        
    private:

        static int numBu; //number of alive bulldozers
};

int Bulldozer::numBu = 0;

Bulldozer::Bulldozer() : Robot()
{ 
    numBu++;
    strength = BULLDOZER_STRENGTH;
    hp = BULLDOZER_HP;
    //name = "bulldozer_" + to_string(numBu);
    name = "BU" + to_string(numBu);
}

Bulldozer::Bulldozer(Arena *arena, int X, int Y) : Robot(arena, X, Y)
{ 
    numBu++;
    strength = BULLDOZER_STRENGTH;
    hp = BULLDOZER_HP;
    //name = "bulldozer_" + to_string(numBu);
    name = "BU" + to_string(numBu);
}

int Bulldozer::getDamage()
{
    int damage = Robot::getDamage();
    return damage;
}

int main()
{
    Arena DeadEarth;
    
    srand(time(NULL)); 

    int i, x, y; //loop counter, coordinats

    OptimusPrime *opp;

    int opcount = 0;
    while (opcount < INITCOUNT)
    {
        x = rand() % ARENASIZE;
        y = rand() % ARENASIZE;

        if (DeadEarth.getAt(x,y)==NULL) 
        {
            opcount++;
            opp = new OptimusPrime(&DeadEarth, x, y);
        }
    }

    /*RoboCop *rcp;
    for(i = 0; i < INITCOUNT; i++)
    {
        x = rand() % ARENASIZE;
        y = rand() % ARENASIZE;

        if (DeadEarth.getAt(x,y)==NULL) 
        {
            rcp = new RoboCop(&DeadEarth, x, y);
        }
    }

    Roomba *rop;
    for(i = 0; i < INITCOUNT; i++)
    {
        x = rand() % ARENASIZE;
        y = rand() % ARENASIZE;

        if (DeadEarth.getAt(x,y)==NULL) 
        {
            rop = new Roomba(&DeadEarth, x, y);
        }
    }

    Kamikaze *kap;
    for(i = 0; i < INITCOUNT; i++)
    {
        x = rand() % ARENASIZE;
        y = rand() % ARENASIZE;

        if (DeadEarth.getAt(x,y)==NULL) 
        {
            kap = new Kamikaze(&DeadEarth, x, y);
        }
    }

    Bulldozer *bup;
    for(i = 0; i < INITCOUNT; i++)
    {
        x = rand() % ARENASIZE;
        y = rand() % ARENASIZE;

        if (DeadEarth.getAt(x,y)==NULL) 
        {
            bup = new Bulldozer(&DeadEarth, x, y);
        }
    }*/

    string s;
    while (true)
    {
        DeadEarth.Display();
        DeadEarth.SimulateOneStep();
        cout << endl << "Press enter for next step" << endl;
        getline(cin,s);
    }

    return 0;
}