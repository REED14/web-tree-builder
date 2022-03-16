#ifndef QUEUE_MAN_H_INCLUDED
#define QUEUE_MAN_H_INCLUDED
#include <iostream>
#include <fstream>
#include "text_man.h"

using namespace std;

ofstream fout;
ofstream fcss;

typedef struct cell cell;

struct node{
    node* prev;
    cell* web_data;
};

struct queue_pls{
    node* last;
    node* current;
    int elems;
};

struct cell{
    cell* parent;
    char id[100];
    char type[100];

    queue_pls children;
};

cell empty_cell;

void queue_add(queue_pls* qpls, cell* data)
{
    if(qpls->current==NULL)
    {
        node* pls = new node;
        pls->web_data = data;
        qpls->current = pls;
        qpls->last = pls;
        qpls->elems = 1;
    }
    else
    {
        node* pls = new node;
        pls->web_data = data;
        qpls->last->prev = pls;
        qpls->last = pls;
        qpls->elems++;
    }
}

void queue_del(queue_pls* qpls, int idx)
{
    if(qpls->elems<=idx)
        cout<<"Nothing to DELETE!\n";
    else
    {
        if(idx==0)
        {
            node* tmp = qpls->current;
            if(qpls->last==qpls->current)
                qpls->last=NULL;

            qpls->current = qpls->current->prev;
            delete tmp;
            qpls->elems--;
        }

        else{
            if(qpls->elems==idx+1)
            {
                node* tmp = qpls->current;
                node* tmp2;
                for(int i=1; i<=idx; i++)
                {
                    tmp2 = tmp;
                    tmp  = tmp->prev;
                }

                tmp2->prev = NULL;
                qpls->last = tmp2;

                delete tmp;
                qpls->elems--;
            }

            else{
                node* tmp = qpls->current;
                node* tmp2;
                for(int i=1; i<=idx; i++)
                {
                    tmp2 = tmp;
                    tmp  = tmp->prev;
                }

                tmp2->prev = tmp->prev;
                delete tmp;
                qpls->elems--;
            }
        }
    }
}

void delete_queue_full(queue_pls* queue_to_delete)
{
    node* temp_to_del = queue_to_delete->current;
    node* temp_to_prev = queue_to_delete->current;
    /*
    for(int i=0; i<queue_to_delete->elems; i++)
    {
        //cout<<temp_to_del->web_data->id<<" ";
        if(temp_to_del->web_data->children.elems>0)
        {
            delete_queue_full(&temp_to_del->web_data->children);
        }
        temp_to_prev = queue_to_delete->current->prev;

        delete temp_to_del->web_data;
        delete temp_to_del;

        temp_to_del = temp_to_prev;
        cout<<temp_to_del->web_data->id<<" ";
    }*/
    for(int i=0; i<queue_to_delete->elems && temp_to_del!=NULL; i++)
    {
        //cout<<temp_to_del->web_data->id<<" ";
        if(temp_to_del->web_data->children.elems>0)
        {
            delete_queue_full(&temp_to_del->web_data->children);
        }
        temp_to_prev = temp_to_del->prev;

        delete temp_to_del->web_data;
        delete temp_to_del;

        //cout<<temp_to_del->web_data->id<<" ";
        temp_to_del = temp_to_prev;
    }
    delete &queue_to_delete;
}


void full_delete(cell* pls)
{
    if(pls->children.elems>0)
    {
        delete_queue_full(&pls->children);
    }
    delete pls;
}

void delete_elem_strict(queue_pls* qpls, char elem[])
{
    if(qpls->elems==0){
        cout<<"ELEMENT DOES NOT EXIST IN THIS QUEUE!\n";
        return;
    }

    node* tmp = qpls->current;
    int idx = 0;

    bool has_found = 0;
    while(tmp!=NULL && idx<=qpls->elems)
    {
        if(is_that_str(tmp->web_data->id, elem)){
            has_found=1;
            break;
        }
        tmp = tmp->prev;
        idx++;
    }

    if(!has_found)
    {
        cout<<"ELEMENT DOES NOT EXIST IN THIS QUEUE!\n";
        return;
    }

    node* selected = qpls->current;
    if(is_that_str(selected->web_data->id, elem))
    {
        qpls->current = qpls->current->prev;
        full_delete(selected->web_data);
        delete selected;
        qpls->elems=qpls->elems-1;
        return;
    }

    selected = qpls->current->prev;
    node* prev_selected = qpls->current;

    while(selected!=NULL)
    {
        if(is_that_str(selected->web_data->id, elem))
        {
            prev_selected->prev = selected->prev;
            full_delete(selected->web_data);
            delete selected;
            qpls->elems=qpls->elems-1;
            return;
        }

        prev_selected = selected;
        selected = selected->prev;
    }

    cout<<"\nNothing to delete!\n\n";
    //qpls->elems=qpls->elems-1;
}

cell* queue_iter(queue_pls* qpls, int idx)
{
    if(qpls->elems<=idx){
        cout<<"Nothing to Access!\n";
        return &empty_cell;
    }

    if(idx==0)
        return qpls->current->web_data;

    node* tmp = qpls->current;
    for(int i=0; i<idx; i++)
    {
        tmp = tmp->prev;
    }
    return tmp->web_data;
}

void queue_iter_id(queue_pls* qpls, char id[], cell* &thing)
{
    if(qpls->elems==0){
        cout<<"ELEMENT DOES NOT EXIST IN THIS QUEUE!\n";
        return;
    }

    node* tmp = qpls->current;
    int idx = 0;
    while(tmp!=NULL && idx<=qpls->elems)
    {
        //cout<<tmp->web_data->id<<" ";
        if(is_that_str(tmp->web_data->id, id)){
            thing = tmp->web_data;
            //cout<<"ELEMENT DOES NOT EXIST IN THIS QUEUE!\n";
            return;
        }
        tmp = tmp->prev;
        idx++;
    }

    cout<<"ELEMENT DOES NOT EXIST IN THIS QUEUE!\n";
    return;
}

int queue_iter_id_idx(queue_pls* qpls, char id[])
{
    if(qpls->elems==0){
        cout<<"ELEMENT DOES NOT EXIST IN THIS QUEUE!\n";
        return -1;
    }

    cell* thing;

    node* tmp = qpls->current;
    int idx = 0;
    while(tmp->prev!=NULL && idx<qpls->elems)
    {
        //cout<<tmp->web_data->id<<" ";
        if(is_that_str(tmp->web_data->id, id)){
            thing = tmp->web_data;
            //cout<<"ELEMENT DOES NOT EXIST IN THIS QUEUE!\n";
            return idx;
        }
        tmp = tmp->prev;
        idx++;
    }
    return -1;
}

int tabs = 0;

void explore(cell* current_c)
{
    for(int i=0; i<tabs; i++)
        fout<<'\t';
    fout<<"<"<<current_c->type<<" id=\""<<current_c->id<<'"'<<">\n";
    tabs++;
    if(current_c->children.elems>0)
    {
        node* tmp = current_c->children.current;
        for(int i=0; i<current_c->children.elems; i++)
        {
            explore(tmp->web_data);
            tmp = tmp->prev;
        }
    }
    tabs--;

    for(int i=0; i<tabs; i++)
        fout<<'\t';
    fout<<"</"<<current_c->type<<">\n";
    fcss<<"#"<<current_c->id<<"\n{\n}\n";
}

#endif // QUEUE_MAN_H_INCLUDED
