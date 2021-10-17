#include<stdio.h>
class Bitmap
{
private:
    /* data */
    int* T;
    int* Code;
    int* F; 
    int top;
    int cap;
public:
    Bitmap(int n)
    {
        T=new int[n];
        F=new int[n];
        Code=new int[n];
        this->top = 0;
        cap = n;
    }
    ~Bitmap()
    {
        delete[] this->F;
        delete[] this->T;
        delete[] this->Code;
        this->F = nullptr;
        this->T = nullptr;
        this->Code = nullptr;
    }
    void reset()
    {
        this->top = 0;
    }
    int test(int k)
    {
        if((0 <= F[k]) && (F[k] < top) && (k == T[F[k]]))
        {
            return F[k];
        }
        else
        {
            return -1;
        }
    }
    void set(int k,int code)
    {
        int result=test(k);
        if(result==-1)
        {
            this->T[this->top] = k;
            this->Code[this->top] = code;
            this->F[k] = this->top++;
        }
        else
        {
            this->Code[result] = code;
        }
    }
    int Size()
    {
        return this->top;
    }
    void clear(int k)
    {
        if((test(k) != -1) && (--top))
        {
            this->F[this->T[this->top]] = this->F[k];
            this->T[this->F[k]] = this->T[this->top];
            this->Code[this->F[k]] = this->Code[this->top];
        }
    }
    int GetCode(int k)
    {
        if(test(k)==-1)
        {
            return -1;
        }
        else 
        {
            return Code[test(k)];
        }
    }
};
int main()
{
    int n=0;
    int m=0;
    scanf("%d %d",&n,&m);
    getchar();
    long int Sum=0;
    Bitmap B(n+1);
    char Op;
    int a=0;
    int c=0;
    for(int i = 0;i < m; i++)
    {
        scanf("%s",&Op);
        switch (Op)
        {
        case 'I':
            scanf("%d %d",&a,&c);
            getchar();
            B.set(a-1,c);
            break;
        case 'O':
            scanf("%d",&a);
            getchar();
            B.clear(a-1);
            break;
        case 'C':
            B.reset();
            break;
        case 'N':
            Sum += (long)B.Size();
            break;
        case 'Q':
            scanf("%d",&a);
            getchar();
            Sum+=(long)B.GetCode(a-1);
            break;
        }
    }
    printf("%ld",Sum);
    return 0;
}