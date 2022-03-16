#ifndef TEXT_MAN_H_INCLUDED
#define TEXT_MAN_H_INCLUDED

int space_place[3];

int str_len(char text[])
{
    int chars = 0;
    for(int i=0; text[i]!='\0'; i++)
        chars++;

    return chars;
}

void str_cpy(char to[], char from[])
{
    for(int i=0; i<str_len(from); i++)
    {
        //std::cout<<from[i];
        to[i]=from[i];
    }
    to[str_len(from)]='\0';
    //std::cout<<to[str_len(from)-2];
    //std::cout<<'\n';
}

int spaces(char text[])
{
    int sp = 0;
    int strln = str_len(text);

    space_place[0]=0; space_place[1]=0; space_place[2]=0;

    bool catch_string = 0;

    for(int i=0; i<strln; i++){
        if(text[i]==' ' && catch_string==0)
        {
            space_place[sp]=i;
            sp++;
        }
        else if(text[i]=='"' && catch_string==0)
        {
            catch_string = 1;
            space_place[sp-1]=i;
        }
        else if(catch_string && text[i]=='"')
        {
            catch_string = 0;
            space_place[sp]=i;
            sp++;
        }
    }
    return sp;
}

bool is_that_str(char text[], char text_sec[])
{
    int strln = str_len(text);
    int strln2 = str_len(text_sec);

    if(strln!=strln2) return 0;

    for(int i=0; i<strln; i++)
        if(text[i]!=text_sec[i]) return 0;

    return 1;
}

#endif // TEXT_MAN_H_INCLUDED
