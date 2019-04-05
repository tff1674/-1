#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define EXP_LEN 100 //������ʽ����󳤶�
#define DATA_LEN 20 //����ÿ������������󳤶�
typedef struct BinaryTree
{
    int dflag;       //��־��ֵΪ1��data[]��Ų��������;ֵΪ0��data[]��Ų�����
    char data[DATA_LEN+1];        //�����򣬴�ţ���������� �� ������
    struct BinaryTree *lchild,*rchild;       //�ֱ�ָ�������������
}BiTNode,*BiTree;    //������������ �� ����������ָ��
int CreateBiTree(BiTree &bt,char *p,int l);
//����������������bt�������ĸ���ַ��pΪ���ʽ���׵�ַ��lΪ���ʽ�ĳ���
int Calculate(BiTree bt,double &rst);
//������ʽ��ֵ��btΪ�ݱ��ʽ�����Ķ���������rst���ر��ʽ��ֵ
int PreOrderTraverse(BiTree bt); //�������������bt����������������
int PostOrderTraverse(BiTree bt); //�������������bt����������������
int InOrderTraverse(BiTree bt);//�������������bt,�������������� 
int main()
{
    int l,i;   //l�洢���ʽ�ĳ��ȣ�iһ�����
    char expn[EXP_LEN+1];            //��ű��ʽ
    double rst;                      //��ű��ʽ������
    BiTree bt=NULL;                  //����һ��������
    i=0;
    printf("��������ʽ(��$��β)��\n");
    gets(expn);
    for(i=0,l=0;expn[i]!='\0';i++) //ȥ�����ʽ�еĿո񣬲�������ʽ�ĳ���
        if(expn[i]!='$') expn[l++]=expn[i];
    expn[l]='\0';
    CreateBiTree(bt,expn,l);
    
    printf("���ɶ�����Ϊ��\n");
   

    printf("ǰ׺���ʽΪ��\n");
    PreOrderTraverse(bt);printf("\n");

    printf("��׺���ʽΪ��\n");
    PostOrderTraverse(bt);printf("\n");

    printf("��׺���ʽΪ��\n");
	InOrderTraverse(bt);printf("\n");
	 
    printf("���ʽ��ֵΪ:\n");
    Calculate(bt,rst)    ;
    printf("%g\n",rst);printf("\n");
    return 0;
}
int CreateBiTree(BiTree &bt,char *p,int l)
{
    int i=0,lnum=0,rpst1=-1,rpst2=-1;
    //lnum��¼"��"��δ�ɶԸ�����
    //rpst1/rpst2��¼���ʽ�����ȼ���͵�("*"��"/")/("+"��"-")��λ��;

    if(l==0)return 1;
    bt=(BiTree)malloc(sizeof(BiTNode));
    if(!bt)
    {
        printf("�ڴ�����ʧ��\n");
        return 0;
    }
    else
    {
        bt->lchild=bt->rchild=NULL;
        memset(bt->data,'\0',sizeof(bt->data));
        bt->dflag=1;
        //Ĭ��btΪҶ�ӽڵ�(������Ų�����)
    }
    if(l==1)      //��ʱֻ�б��ʽΪ���֣����ʽ�źϷ�
    {
        bt->data[0]=*p;
        return 1;
    }
    else if(l==2) //��ʱֻ�б��ʽΪ�������������ʽ�źϷ�
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
            if(CreateBiTree(bt->lchild,p,rpst2))
            {
                if(CreateBiTree(bt->rchild,p+rpst2+1,l-rpst2-1))
                    return 1;
            }
            return 0;
        }
        if(rpst1<0)//��ʱ�������ʽ������һ�����֣����Ǳ��ʽ���屻һ������������
        {
            if(*p=='(') //��ʱ���ʽ���屻һ������������
            {
                if(CreateBiTree(bt,p+1,l-2))
                return 1;
                else return 0;
            }
            else
            {
                if(*(p+1)!='(') //��ʱ���ʽһ����һ������
                {
                    for(i=0;i<l;i++)
                    {
                        bt->data[i]=*(p+i);
                    }
                    return 1;
                }
                else //��ʱ���ʽ��һ���ǲ�����"-"�����ಿ�ֱ�һ������������
                {
                    bt->dflag=0;
                    bt->data[0]='-';
                    if(CreateBiTree(bt->rchild,p+2,l-3))
                        return 1;
                    else return 0;
                }
            }
        }
        else //��ʱ�������ʽΪ����������ɻ��������ɵ�
        {
            bt->dflag=0;
            bt->data[0]=*(p+rpst1);
            if(CreateBiTree(bt->lchild,p,rpst1))
            {
                if(CreateBiTree(bt->rchild,p+rpst1+1,l-rpst1-1))
                    return 1;
            }
            return 0;
        }
    }
}

int Calculate(BiTree bt,double &rst)
{
    double l=0,r=0;//l��r�ֱ�������������������ֱ��ʽ��ֵ
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
                            printf("����Ϊ0 !\n");
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
int PreOrderTraverse(BiTree bt)  //�������������bt����������������
{
    if(bt)
    {
        printf("%s ",bt->data);
        PreOrderTraverse(bt->lchild);
        PreOrderTraverse(bt->rchild);
        return 1;
        return 0;
    }
    return 1;
}

int PostOrderTraverse(BiTree bt)   //�������������bt����������������
{
    if(bt)
    {
        if(PostOrderTraverse(bt->lchild))
        {
            if(PostOrderTraverse(bt->rchild))
            {
                printf("%s ",bt->data);
                return 1;
            }
            else return 0;
        }
    }
    return 1;
}
int InOrderTraverse(BiTree bt)//�������������bt����������������
{
    if(bt)
    {
    	InOrderTraverse(bt->lchild);
        printf("%s ",bt->data);
        InOrderTraverse(bt->rchild);
        return 1;
        return 0;
    }
    return 1;
}

