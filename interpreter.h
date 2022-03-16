#ifndef INTERPRETER_H_INCLUDED
#define INTERPRETER_H_INCLUDED

#include <iostream>
#include <fstream>
#include "text_man.h"
#include "web_tree_man.h"

void interpretf(char text_cmd[])
{
    char command[100] = "";
    char fp[100] = "";
    char sp[100] = "";

    int spcnum = spaces(text_cmd);
    int num_chars = str_len(text_cmd);

    for(int i=0; i<space_place[0]*(space_place[0]!=0)+num_chars*(space_place[0]==0);i++) command[i]=text_cmd[i];

    if(space_place[0]!=0)
    {
        int indexer = 0;
        for(int i=space_place[0]+1 ; i<space_place[1]*(space_place[1]!=0)+num_chars*(space_place[1]==0);i++)
        {
            fp[indexer]=text_cmd[i];
            indexer++;
        }

        if(space_place[1]!=0)
        {
            indexer = 0;
            for(int i=space_place[1]+1; i<space_place[2]*(space_place[2]!=0)+num_chars*(space_place[2]==0);i++)
            {
                sp[indexer]=text_cmd[i];
                indexer++;
            }
        }
    }
    //std::cout<<"command: "<<command<<"\nfp: "<<fp<<"\nsp: "<<sp<<"\n \n";

    if(is_that_str(command, "create"))
    {
        if(str_len(fp)>0 && str_len(sp)>0)
            create_elem(fp, sp);
        else
            std::cout<<"CANNOT CREATE ELEMENT WITH EMPTY ID OR TYPE!"<<'\n';
    }
    else if(is_that_str(command, "select") && str_len(fp)>0)
    {
        select(fp);
    }
    else if(is_that_str(command, "back"))
    {
        back_pls();
    }
    else if(is_that_str(command, "dir"))
    {
        dir();
    }
    else if(is_that_str(command, "list"))
    {
        show_children();
    }
    else if(is_that_str(command, "delete"))
    {
        //delete_elem();
        delete_elem_strict(&current_addr_cell->children, fp);
    }
    else if(is_that_str(command, "compile"))
    {
        fout.open("\compiled\html_compiled.html");
        fcss.open("\compiled\style.css");

        fout<<"<!DOCTYPE html>\n"<<"<html>\n";
        fout<<"<head>\n\t<title>RandomPage</title>\n\t<link rel=\"stylesheet\" href=\"style.css\">\n</head>\n\n";
        explore(&body);
        fout<<"</html>\n";

        fout.close();
        fcss.close();
        std::cout<<'\n';
    }

    else if(is_that_str(command, "properties"))
    {
        properties();
        std::cout<<'\n';
    }
}

void read(char path[])
{
    std::ifstream fin;
    //std::cout<<path<<"plm";
    fin.open(path);

    char cmds[300];
    while(fin.getline(cmds, 300))
    {
        interpretf(cmds);
    }
    fin.close();
}

void interpret(char text_cmd[])
{
    char command[100] = "";
    char fp[100] = "";
    char sp[100] = "";

    int spcnum = spaces(text_cmd);
    int num_chars = str_len(text_cmd);

    for(int i=0; i<space_place[0]*(space_place[0]!=0)+num_chars*(space_place[0]==0);i++) command[i]=text_cmd[i];

    if(space_place[0]!=0)
    {
        int indexer = 0;
        for(int i=space_place[0]+1 ; i<space_place[1]*(space_place[1]!=0)+num_chars*(space_place[1]==0);i++)
        {
            fp[indexer]=text_cmd[i];
            indexer++;
        }

        if(space_place[1]!=0)
        {
            indexer = 0;
            for(int i=space_place[1]+1; i<space_place[2]*(space_place[2]!=0)+num_chars*(space_place[2]==0);i++)
            {
                sp[indexer]=text_cmd[i];
                indexer++;
            }
        }
    }
    //std::cout<<"command: "<<command<<"\nfp: "<<fp<<"\nsp: "<<sp<<"\n \n";

    if(is_that_str(command, "create"))
    {
        if(str_len(fp)>0 && str_len(sp)>0)
            create_elem(fp, sp);
        else
            std::cout<<"CANNOT CREATE ELEMENT WITH EMPTY ID OR TYPE!"<<'\n';
    }
    else if(is_that_str(command, "select") && str_len(fp)>0)
    {
        select(fp);
    }
    else if(is_that_str(command, "back"))
    {
        back_pls();
    }
    else if(is_that_str(command, "dir"))
    {
        dir();
    }
    else if(is_that_str(command, "list"))
    {
        show_children();
    }
    else if(is_that_str(command, "delete"))
    {
        //delete_elem();
        delete_elem_strict(&current_addr_cell->children, fp);
    }
    else if(is_that_str(command, "help"))
    {
        std::cout<<'\n';
        std::cout<<"create type_of_element(div, p, h1, etc.) id_of_element -> creates html element\n\n";
        std::cout<<"select id_of_element -> selects the element with specific id to edit it's insides\n\n";
        std::cout<<"delete id_of_element -> deletes the element with specific id\n\n";
        std::cout<<"dir -> shows the path of the selected element\n\n";
        std::cout<<"list -> lists the elements inside of the selected element\n\n";
        std::cout<<"back -> goes to the parrent of the selected element (until Body)\n\n";
        std::cout<<"properties -> shows the properties of the selected element\n\n";
        std::cout<<"loadfile \"file_path\" -> loads the file with commands\n\n";
        std::cout<<"compile -> generates html and css\n\n";
        std::cout<<"compilefile \"file_path\" -> compiles file with commands\n\n";
    }
    else if(is_that_str(command, "compile"))
    {
        fout.open("html_compiled.html");
        fcss.open("style.css");

        fout<<"<!DOCTYPE html>\n"<<"<html>\n";
        fout<<"<head>\n\t<title>RandomPage</title>\n\t<link rel=\"stylesheet\" href=\"style.css\">\n</head>\n\n";
        explore(&body);
        fout<<"</html>\n";

        fout.close();
        fcss.close();
        std::cout<<'\n';
    }

    else if(is_that_str(command, "properties"))
    {
        properties();
        std::cout<<'\n';
    }
    else if(is_that_str(command, "compilefile "))
    {
        read(fp);
        fout.open("html_compiled.html");
        fcss.open("style.css");

        fout<<"<!DOCTYPE html>\n"<<"<html>\n";
        fout<<"<head>\n\t<title>RandomPage</title>\n\t<link rel=\"stylesheet\" href=\"style.css\">\n</head>\n\n";
        explore(&body);
        fout<<"</html>\n";

        fout.close();
        fcss.close();
        std::cout<<'\n';
    }
    else if(is_that_str(command, "loadfile "))
    {
        read(fp);
    }
    else if(is_that_str(command, "write"))
    {
        ofstream fplm;
        fplm.open("plm.txt");
        fplm<<"plm";
        fplm.close();
    }
    else
    {
        cout<<"\nWARNING! Command does not exist!\n\n";
    }
}

#endif // INTERPRETER_H_INCLUDED
