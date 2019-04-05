#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include<math.h>
#include"Node1.h"
using namespace std;
void inOrder(Node1 *p);//���������ͬʱ��������������ŵ���׺���ʽ
void in2tree(Node1 *&p, string str);//��׺���ʽת���ɺ�׺���ʽ���ɶ�����
void freeTree(Node1 *&p);//�ݹ�ɾ���� 
void count(Node1 *p,int &height,int n);
void paint(Node1 *p);//��ӡ������ 
void post2tree(Node1 *&p,string str);//��׺���ʽ���ɶ����� 

bool isOper(char op)//�ж��Ƿ�Ϊ�����
{
char oper[]={'(',')','+','-','*','/','^'};
for(int i=0;i<sizeof(oper);i++)
{  if(op==oper[i])
   {
    return true;
   } 
}
return false;
}

int getOperOrder(char op)//���������op����Ӧ�����ȼ�
{
	switch(op){
	case '(': return 1;
    case '+': 
    case '-':return 2;
    case '*': 
    case '/':return 3;
    case '^':return 4;
    default:
	    return 0;   
	} 
}
void inOrder(Node1 *p)//���������ͬʱ��������������ŵ���׺���ʽ
{  if(p)
{
	if(p->left)
   {    //�����ǰ�ڵ���������������������������ȼ����ڵ�ǰ�������
		//��ô��ߵı��ʽҪ�ȼ��㣬��Ҫ������
		if(isOper(p->left->oper)&& getOperOrder(p->left->oper)<getOperOrder(p->oper))
    {  
			cout<<"(";
            inOrder(p->left);
            cout<<")";
    }
	else//����ֱ�����������
       inOrder(p->left);  
	}

   cout<<p->oper;//�����ǰ�ڵ�
   
   if(p->right)
   {  //�����ǰ�ڵ���������������������������ȼ������ڵ�ǰ�������
		//��ô�ұߵı��ʽҪ�ȼ��㣬��Ҫ������
	   if(isOper(p->right->oper)&& getOperOrder(p->right->oper)<=getOperOrder(p->oper))
    {  
		   cout<<"(";
     inOrder(p->right);
     cout<<")";
    }
	   else
     inOrder(p->right);
   }  
}  
}
void in2tree(Node1 *&p, string str)//��׺���ʽת���ɺ�׺���ʽ���ɶ�����
{  
	stack<char> a;
    char temp1;
    string Postfixexp="";
    int i=0;
    temp1=str[i++];
   while(temp1!='\0')
   { 
	   if(!isOper(temp1))//��������ֱ�ӽ�����ջ
	{    Postfixexp+=temp1;
         temp1=str[i++];
	}
       else if(temp1=='(')//��ջ
	{
		 a.push(temp1);
         temp1=str[i++];
	 }
	 else if(temp1==')')
	 {
	     while(a.top()!='(')//������
		 {
			 Postfixexp+=a.top();
		     a.pop();//�����������ź�ջΪ��ǰ��������ջ��Ԫ��
		 }
              a.pop();
			  temp1=str[i++];
	 }
	else if(temp1=='+'||temp1=='-'||temp1=='*'||temp1=='/')//��ջ
	{
	while(!a.empty()&&a.top()!='('&&getOperOrder(a.top())>=getOperOrder(temp1))
		//��ջ�ǿ�ջ��������������ջ��Ԫ�����ȼ����������������ʱ
	{  Postfixexp+=a.top(); a.pop();  }
	a.push(temp1);
	temp1=str[i++];
     } 
   }
   while(!a.empty())
    {  Postfixexp+=a.top();
	a.pop();
	}
   Postfixexp+='\0';
   post2tree(p,Postfixexp);

}
void freeTree(Node1 *&p) //�ݹ�ɾ����
{ 
	if(p->left!=NULL)
       freeTree(p->left);
    if(p->right!=NULL)
       freeTree(p->right);
    delete(p); 
}
void postOrder(Node1 *p) //�������
{  if(p)
{  postOrder(p->left);
   postOrder(p->right);
   cout<<p->oper;
} 
}

void count(Node1 *p,int &height,int n) {//�����ĸ߶�
	if(p->left==NULL&&p->right==NULL)
	{  if(n>height)
	   height=n;}
	 if(p->left!=NULL)
		count(p->left,height,n+1);
	 if(p->right!=NULL)
	    count(p->right,height,n+1);
}

void paint(Node1 *p)//��ӡ��
{
   int height=0;
   int h=0;
   int i;
  using std::queue;
  queue<Node1*> aQueue;
  count(p,height,1);
  Node1 *pointer=p;
  Node1 *lastpointer;
 if(pointer)
	{ pointer->s=1;
      pointer->t=1;
 aQueue.push(pointer);  }
  while(!aQueue.empty())
 {  lastpointer=pointer;
	 pointer=aQueue.front();
 aQueue.pop();
 if(pointer->s>h)
 {cout<<endl;
  h=pointer->s;}
 if(pointer->t==1)
 {for(i=0;i<pow(2,height-pointer->s)-1;i++)
 cout<<" ";}
 else if(lastpointer->s!=pointer->s){
for(i=0;i<(pointer->t-1)*(pow(2,height-pointer->s+1)-1)+(pointer->t-1)-1+pow(2,height-pointer->s);i++)
	 cout<<" ";  }
 else 
{ for(i=0;i<(pointer->t-lastpointer->t)*(pow(2,height-pointer->s+1)-1)+(pointer->t-lastpointer->t)-1;i++)
 cout<<" ";  }
cout<<pointer->oper;
 if(pointer->left!=NULL){
	 pointer->left->s=pointer->s+1;
	 pointer->left->t=pointer->t*2-1;
	 aQueue.push(pointer->left);}
	 if(pointer->right!=NULL){
	 pointer->right->s=pointer->s+1;
	 pointer->right->t=pointer->t*2;
     aQueue.push(pointer->right);
     }  }  }
void post2tree(Node1 *&p,string str)//��׺���ʽ���ɶ�����
{ stack <Node1*> nodeStack;//���ڱ���ڵ�ָ���ջ
    char temp1;
    int i=0;
    temp1=str[i++];
   while(temp1!='\0')
   {  
	   if(temp1!='\0'&&!isOper(temp1))//��������������ջ
    {  
		   p=new Node1(temp1);//��tempΪ���ֵ������������
           nodeStack.push(p);
           temp1=str[i++];//������һ��
	 }
    else
	{  //����������ţ����ջ��������Ϊ�ҽڵ����ڵ�
		p=new Node1(temp1);
      if(nodeStack.size())
      {  
		  p->right=nodeStack.top();//���ǿ����ջ����Ϊ�����Һ���
       nodeStack.pop();  
	  }
      if(nodeStack.size())
      { 
		  p->left=nodeStack.top();//���ǿ����ջ����Ϊ��������
       nodeStack.pop();
	  }
      nodeStack.push(p);
	  temp1=str[i++];
    } 
   } 
}

