#include <iostream>
#include "Table.h"
#include "Constants.h"

using namespace std;
using namespace PA5;

int main() 
{
    Table table;
    
    table.parseFields();
    table.parseEntries();
    table.parseCommands();
    table.executeCommands();

    return 0;
}
