#include <iostream>
#include <fstream>
#include "text_man.h"
#include "interpreter.h"

using namespace std;

///VARIABLES
char cmnd[300];

int main()
{
    char id_body[100] = "Body";
    char type_body[100] = "body";
    for(int i = 0; id_body[i]!='\0'; i++)
        body.id[i] = id_body[i];

    for(int i = 0; type_body[i]!='\0'; i++)
        body.type[i] = type_body[i];

    while(true)
    {
        cin.getline(cmnd, 300);
        interpret(cmnd);
    }
    return 0;
}
