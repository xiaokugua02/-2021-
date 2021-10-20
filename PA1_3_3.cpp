#include<stdio.h>
int Default_capacity = 40;
int size = 0;
int free = 0;
int data = -1;

typedef struct TextNode
{
    char Elem;
    struct TextNode* pred;
    struct TextNode* succ;
    bool reversed;
    int rank;
}TextNode;
TextNode* Nodepool = new TextNode[Default_capacity];
int* Link = new int[Default_capacity];
TextNode* GetNext(TextNode* Current)
{
    if(Current->reversed)
    {
        return Current->pred;
    }
    else
    {
        return Current->succ;
    }
}
TextNode* GetLast(TextNode* Current)
{
    if(Current->reversed)
    {
        return Current->succ;
    }
    else
    {
        return Current->pred;
    }
}

void init(int n)
{
    for(int i = 0 ; i<n ; i++)
    {
        Link[i] = i + 1;
        Nodepool[i].reversed = false;
        Nodepool[i].rank = i + 1; 
    }
}

TextNode* insert(TextNode* Current,char e)
{
    Nodepool[free].Elem = e;
    Nodepool[free].pred = Current;
    Nodepool[free].succ = GetNext(Current);
    Nodepool[free].rank = free;
    Nodepool[free].reversed = false;
    if(Current->reversed)
    {
        Current->pred = &Nodepool[free];
    }
    else
    {
        Current->succ = &Nodepool[free];
    }
    TextNode* TheNext = GetNext(Current);
    if(TheNext->reversed)
    {
        TheNext->succ = &Nodepool[free];
    }
    else
    {
        TheNext->pred = &Nodepool[free];
    }
    int temp=data;
    int CurrentNode = free;
    data = free;
    free = Link[data];
    Link[data] = temp;
    

    return &Nodepool[CurrentNode];
    
}