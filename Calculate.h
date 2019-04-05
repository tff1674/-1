#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define EXP_LEN 100 //定义表达式的最大长度
#define DATA_LEN 20 //定义每个操作数的最大长度
typedef struct BinaryTree1 
{
    int dflag;       //标志域，值为1，data[]存放操作运算符;值为0，data[]存放操作数
    char data[DATA_LEN+1];        //数据域，存放：操作运算符 或 操作数
    struct BinaryTree1 *lchild,*rchild;       //分别指向结点的左、右子树
}BiTNode1,*BiTree1;    //定义二叉树结点 及 二叉树类型指针
int CreateBiTree1(BiTree1 &bt,char *p,int l);
//创建二叉树，并用bt返回树的根地址，p为表达式的首地址，l为表达式的长度
int Calculate(BiTree1 bt,double &rst);
//计算表达式的值，bt为据表达式创建的二叉树，用rst返回表达式的值

    
    
int CreateBiTree1(BiTree1 &bt,char *p,int l)
{
    int i=0,lnum=0,rpst1=-1,rpst2=-1;
    if(l==0)return 1;
    bt=(BiTree1)malloc(sizeof(BiTNode1));
    if(!bt)
    {
        printf("内存申请失败\n");
        return 0;
    }
    else
    {
        bt->lchild=bt->rchild=NULL;
        memset(bt->data,'\0',sizeof(bt->data));
        bt->dflag=1;
        //默认bt为叶子节点(即，存放操作数)
    }
    if(l==1)      //此时只有表达式为数字，表达式才合法
    {
        bt->data[0]=*p;
        return 1;
    }
    else if(l==2) //此时只有表达式为正数或负数，表达式才合法
    {
        if(((*p=='-')||(*p>='0')&&(*p<='9'))&&(*(p+1)>='0')&&(*(p+1)<='9'))
        {
            bt->data[0]=*p;
            bt->data[1]=*(p+1);
            return 1;
        }
    }
    else
    {
        if(*p=='(')lnum++;
        for(i=1;i<l;i++)
        {
            if(*(p+i)=='*'||*(p+i)=='/')
            {
                if(lnum==0)rpst1=i;
            }
            else if(*(p+i)=='(')
            {
                if(*(p+i-1)=='+'||*(p+i-1)=='-'||*(p+i-1)=='*'||*(p+i-1)=='/'||*(p+i-1)=='(')
                    lnum++;
            }
            else if(*(p+i)==')')
            {
                if((*(p+i-1)==')')||(*(p+i-1)>='0')&&(*(p+i-1)<='9'))
                    lnum--;
            }
            else if(*(p+i)=='+'||*(p+i)=='-')
            {
                if(lnum==0) rpst2=i;
            }
        }

        if(rpst2>-1)
        {
            bt->dflag=0;bt->data[0]=*(p+rpst2);
            if(CreateBiTree1(bt->lchild,p,rpst2))
            {
                if(CreateBiTree1(bt->rchild,p+rpst2+1,l-rpst2-1))
                    return 1;
            }
            return 0;
        }
        if(rpst1<0)//此时表明表达式或者是一个数字，或是表达式整体被一对括弧括起来
        {
            if(*p=='(') //此时表达式整体被一对括弧括起来
            {
                if(CreateBiTree1(bt,p+1,l-2))
                return 1;
                else return 0;
            }
            else
            {
                if(*(p+1)!='(') //此时表达式一定是一个数字
                {
                    for(i=0;i<l;i++)
                    {
                        bt->data[i]=*(p+i);
                    }
                    return 1;
                }
                else //此时表达式首一定是操作符"-"，其余部分被一对括弧括起来
                {
                    bt->dflag=0;
                    bt->data[0]='-';
                    if(CreateBiTree1(bt->rchild,p+2,l-3))
                        return 1;
                    else return 0;
                }
            }
        }
        else //此时表明表达式为几个因子想成或相除而组成的
        {
            bt->dflag=0;
            bt->data[0]=*(p+rpst1);
            if(CreateBiTree1(bt->lchild,p,rpst1))
            {
                if(CreateBiTree1(bt->rchild,p+rpst1+1,l-rpst1-1))
                    return 1;
            }
            return 0;
        }
    }
}

int Calculate(BiTree1 bt,double &rst)
{
    double l=0,r=0;//l、r分别存放左右子树所代表的字表达式的值
    if(!bt)
    {
        rst=0;
        return 1;
    }
    if(bt->dflag==1)
    {
        rst=atof(bt->data);
        return 1;
    }
    else
    {
        if(Calculate(bt->lchild,l))
        {
            if(Calculate(bt->rchild,r))
            {
                switch(bt->data[0])
                {
                    case '+' :
                        rst=l+r;
                        break;
                    case '-' :
                        rst=l-r;
                        break;
                    case '*' :
                        rst=l*r;
                        break;
                    case '/' :
                        if(r==0)
                        {
                            printf("除数为0 !\n");
                            return 0;
                        }
                        else
                        {
                            rst=l/r;
                            break;
                        }
                    default : return 0;
                }
                return 1;
            }
        }
        return 0;
    }
}
