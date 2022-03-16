#ifndef WEB_TREE_MAN_H_INCLUDED
#define WEB_TREE_MAN_H_INCLUDED

#include "queue_man.h"

cell body;
cell* current_addr_cell = &body;

void create_elem(char fp[100], char sp[100])
{
    cell* tmp = new cell;

    //string transfer
    str_cpy(tmp->id, sp);
    str_cpy(tmp->type, fp);

    tmp->parent = current_addr_cell;
    tmp->children.elems = 0;

    queue_add(&(current_addr_cell->children), tmp);

}

void select(char fp[])
{
    queue_iter_id(&(current_addr_cell->children), fp, current_addr_cell);
}

void back_pls()
{
    if(is_that_str("Body", current_addr_cell->id))
    {
        std::cout<<"CANNOT GO BACK!"<<'\n'<<'\n';
        return;
    }

    cell* change = current_addr_cell->parent;
    current_addr_cell = change;
}

void dir()
{
    cell* tmp = current_addr_cell;
    while(!is_that_str(tmp->id, "Body"))
    {
        std::cout<<tmp->id<<"<-";
        tmp = tmp->parent;
    }
    std::cout<<"Body"<<'\n'<<'\n';
}

void show_children()
{
    queue_pls qpls = current_addr_cell->children;
    if(qpls.elems==0){
        std::cout<<"No elements in current queue!\n";
        return;
    }

    node* tmp = qpls.current;
    for(int i=0; i<qpls.elems; i++)
    {
        std::cout<<tmp->web_data->id<<" ";
        tmp = tmp->prev;
    }
    std::cout<<'\n'<<'\n';

    return;
}

void delete_elem()
{
    if(is_that_str(current_addr_cell->id, "Body"))
    {
        std::cout<<"CANNOT DELETE BODY!\n"<<'\n';
        return;
    }
    cell* tmp = current_addr_cell;
    current_addr_cell = current_addr_cell->parent;

    int idx = queue_iter_id_idx(&(current_addr_cell->children), tmp->id);
    delete tmp;
    queue_del(&current_addr_cell->children, idx);
}

void properties()
{
    std::cout<<'\n';

    std::cout<<"ID: "<<current_addr_cell->id<<'\n';
    std::cout<<"Type: "<<current_addr_cell->type<<'\n';

}
#endif // WEB_TREE_MAN_H_INCLUDED
