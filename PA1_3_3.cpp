#include<stdio.h>
static int Default_capacity = 20;
static int size = 0;
typedef struct TextNode
{
    char Elem;
    struct TextNode* pred;
    struct TextNode* succ;
}TextNode;
static TextNode* Text = new TextNode[Default_capacity];
static TextNode* NodePool;

TextNode* Push(TextNode* node,TextNode* NodePool)
{
    node->pred = NodePool;
    return node;
}

// void Expand()
// {
//     TextNode* a = new TextNode[Default_capacity];
//     for(int i=0;i<Default_capacity;i++)
//     {
//         NodePool = Push(&a[i],NodePool);
//     }
//     Default_capacity <<= 1;
// }

void init()
{
    TextNode* a = new TextNode[Default_capacity];
    for(int i = 0;i<Default_capacity;i++)
    {
        NodePool = Push(&a[i],NodePool);
    }
}

TextNode* Pop()
{   
    if( (NodePool == nullptr))
    {
        TextNode* a = new TextNode[Default_capacity];
    for(int i=0;i<Default_capacity;i++)
    {
        NodePool = Push(&a[i],NodePool);
    }
    Default_capacity <<= 1;
    }
    TextNode* Current = NodePool;
    NodePool = NodePool->pred;
    return Current;
}

bool Delete(TextNode* Node,bool IsTextNode)
{
    if (IsTextNode)
    {
        if(Node->succ!=nullptr)
        {   
            Node->pred->succ = Node->succ;
            Node->succ->pred = Node->pred;
            NodePool = Push(Node,NodePool);
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        if(Node->pred!=nullptr)
        {   
            Node->pred->succ = Node->succ;
            Node->succ->pred = Node->pred;
            NodePool = Push(Node,NodePool);
            return true;
        }
        else
        {
            return false;
        }
    }
}

TextNode* Insert(TextNode* TextNodeCursor,TextNode* ReverseCursor,char e,bool IsTextNode)
{   
    TextNode* NewNode = Pop();
    if(IsTextNode)
    {
        NewNode->Elem = e;
        NewNode->pred = TextNodeCursor;
        NewNode->succ = TextNodeCursor->succ;
        TextNodeCursor->succ->pred = NewNode; 
        TextNodeCursor->succ = NewNode;
        TextNodeCursor = NewNode;
        return NewNode;
    }
    else
    {
        NewNode = Pop();
        NewNode->Elem = e;
        NewNode->pred = ReverseCursor->pred;
        NewNode->succ = ReverseCursor;
        ReverseCursor->pred->succ = NewNode;
        ReverseCursor->pred = NewNode;
        return NewNode;
        printf("T\n");
    }
}

void Reverse(TextNode* LTextCursor,TextNode* RTextCursor,TextNode* LReverseCursor,TextNode* RReverseCursor)
{   
    if (size>0)
    {   
        TextNode* NodeForText = LTextCursor->succ;
        LTextCursor->succ = LReverseCursor->succ;
        LReverseCursor->succ->pred = LTextCursor;
        LReverseCursor->succ = NodeForText;
        NodeForText->pred = LReverseCursor;

        NodeForText = RTextCursor->pred;
        RTextCursor->pred = RReverseCursor->pred;
        RReverseCursor->pred->succ = RTextCursor;
        RReverseCursor->pred = NodeForText;
        NodeForText->succ = RReverseCursor;
        printf("T\n");
    }
    else
    {
        printf("F\n");
    }
}

int main()
{
    init();
    int Ops = 0;
    char s;
    char Cursor;
    char elem;
    TextNode* Reader;
    //init The list for output
    TextNode* T_Header = Pop();
    TextNode* T_Tailer = Pop();
    T_Header->pred = nullptr;
    T_Header->succ = T_Tailer;
    T_Tailer->pred = T_Header;
    T_Tailer->succ = nullptr;
    //init the list which is a reversed list for output 
    TextNode* R_Header = Pop();
    TextNode* R_Tailer = Pop();
    R_Header->pred = nullptr;
    R_Header->succ = R_Tailer;
    R_Tailer->pred = R_Header; 
    R_Tailer->succ = nullptr;
    //init the Cursor
    TextNode* LTextCursor = T_Header;
    TextNode* RTextCursor = T_Header;
    TextNode* LReverseCursor = R_Tailer;
    TextNode* RReverseCursor = R_Tailer;
    
    TextNode* AfterRTC;
    TextNode* BeforeLRC;
    s = getchar();
    while ((s>= 32)&&(s<=126))
    {
        RTextCursor = Insert(RTextCursor,LReverseCursor,s,true);
        LReverseCursor = Insert(RTextCursor,LReverseCursor,s,false);
        size++;
        s=getchar();
    }
    scanf("%d",&Ops);
    getchar();
    for(;Ops > 0;Ops-=1)
    {
        s = getchar();
        while ((s< 32)||(s>126))
        {
            s=getchar();
        }
        if(s == 'I')
        {   
            Cursor = getchar();
            while ((Cursor<= 32)||(Cursor>126))
            {
                Cursor=getchar();
            }
            getchar();
            if (Cursor=='L')
            {
                elem = getchar();
                while ((elem< 32)||(elem>126))
                {
                    elem=getchar();
                }
                LTextCursor = Insert(LTextCursor,RReverseCursor,elem,true);
                RReverseCursor = Insert(LTextCursor,RReverseCursor,elem,false);
                if (size<0)
                {
                    size--;
                }
                if (size==0)
                {
                    RTextCursor = LTextCursor;
                    LReverseCursor = RReverseCursor;
                }
            }
            if (Cursor == 'R')
            {
                elem = getchar();
                while ((elem< 32)||(elem>126))
                {
                    elem=getchar();
                }
                RTextCursor = Insert(RTextCursor,LReverseCursor,elem,true);
                LReverseCursor = Insert(RTextCursor,LReverseCursor,elem,false);
                if(size > 0)
                {
                    size++;
                }
                if (size == 0)
                {
                    LTextCursor = RTextCursor;
                    RReverseCursor = LReverseCursor;
                }   
            }
            printf("T\n");
        }
        if(s=='D')
        {
            Cursor = getchar();
            while ((Cursor<= 32)||(Cursor>126))
            {
                Cursor=getchar();
            }
            if (Cursor =='L')
            {
                if(Delete(LTextCursor->succ,true)&&(Delete(RReverseCursor->pred,false)))
                {
                    printf("T\n");
                }
                else
                {
                    printf("F\n");
                }
            }
            if (Cursor == 'R')
            {
               if(Delete(RTextCursor->succ,true)&&(Delete(LReverseCursor->pred,false)))
                {
                    printf("T\n");
                }
                else
                {
                    printf("F\n");
                }
            }
        }
        if(s=='R')
        {
            AfterRTC = RTextCursor->succ;
            BeforeLRC = LReverseCursor->pred;
            Reverse(LTextCursor,AfterRTC,BeforeLRC,RReverseCursor);
            RTextCursor = AfterRTC->pred;
            LReverseCursor = BeforeLRC->succ;
        }
        if(s=='S')
        {
            Reader = T_Header->succ;
            while (Reader!=T_Tailer)
            {
                printf("%c",Reader->Elem);
                Reader = Reader->succ;
            }
            printf("\n");
        }
        if(s=='<')
        {
            Cursor = getchar();
            while ((Cursor<= 32)||(Cursor>126))
            {
                Cursor=getchar();
            }
            if (Cursor == 'L')
            {
                if (LTextCursor->pred!=nullptr)
                {
                    LTextCursor = LTextCursor->pred;
                    RReverseCursor = RReverseCursor->succ;
                    size++;
                    printf("T\n");
                }
                else
                {
                    printf("F\n");
                }
            }
            if (Cursor == 'R')
            {
                if (RTextCursor->pred!=nullptr)
                {
                    RTextCursor = RTextCursor->pred;
                    LReverseCursor = LReverseCursor->succ;
                    size--;
                    printf("T\n");
                }
                else
                {
                    printf("F\n");
                }
            }
        }
        if(s=='>')
        { 
            Cursor = getchar();
            while ((Cursor<= 32)||(Cursor>126))
            {
                Cursor=getchar();
            }
            if (Cursor == 'L')
            {
                if(LTextCursor->succ->succ!=nullptr)
                {
                    LTextCursor = LTextCursor->succ;
                    RReverseCursor = RReverseCursor->pred;
                    size--;
                    printf("T\n");
                }
                else
                {
                    printf("F\n");
                }
            }
            if (Cursor == 'R')
            {
                if(RTextCursor->succ->succ!=nullptr)
                {
                    RTextCursor = RTextCursor->succ;
                    LReverseCursor = LReverseCursor->pred;
                    size++;
                    printf("T\n");
                }
                else
                {
                    printf("F\n");
                }
            }
        }
    }
    return 0;
}