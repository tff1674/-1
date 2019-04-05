#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include<math.h>
#include"Node1.h"
using namespace std;
void inOrder(Node1 *p);//中序遍历，同时输出不带冗余括号的中缀表达式
void in2tree(Node1 *&p, string str);//中缀表达式转换成后缀表达式生成二叉树
void freeTree(Node1 *&p);//递归删除树 
void count(Node1 *p,int &height,int n);
void paint(Node1 *p);//打印二叉树 
void post2tree(Node1 *&p,string str);//后缀表达式生成二叉树 

bool isOper(char op)//判断是否为运算符
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

int getOperOrder(char op)//返回运算符op所对应的优先级
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
void inOrder(Node1 *p)//中序遍历，同时输出不带冗余括号的中缀表达式
{  if(p)
{
	if(p->left)
   {    //如果当前节点的左子树是运算符，且运算符优先级低于当前运算符，
		//那么左边的表达式要先计算，需要加括号
		if(isOper(p->left->oper)&& getOperOrder(p->left->oper)<getOperOrder(p->oper))
    {  
			cout<<"(";
            inOrder(p->left);
            cout<<")";
    }
	else//否则直接输出左子树
       inOrder(p->left);  
	}

   cout<<p->oper;//输出当前节点
   
   if(p->right)
   {  //如果当前节点的右子树是运算符，且运算符优先级不高于当前运算符，
		//那么右边的表达式要先计算，需要加括号
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
void in2tree(Node1 *&p, string str)//中缀表达式转换成后缀表达式生成二叉树
{  
	stack<char> a;
    char temp1;
    string Postfixexp="";
    int i=0;
    temp1=str[i++];
   while(temp1!='\0')
   { 
	   if(!isOper(temp1))//操作数则直接进数据栈
	{    Postfixexp+=temp1;
         temp1=str[i++];
	}
       else if(temp1=='(')//进栈
	{
		 a.push(temp1);
         temp1=str[i++];
	 }
	 else if(temp1==')')
	 {
	     while(a.top()!='(')//脱括号
		 {
			 Postfixexp+=a.top();
		     a.pop();//在碰到开括号和栈为空前反复弹出栈中元素
		 }
              a.pop();
			  temp1=str[i++];
	 }
	else if(temp1=='+'||temp1=='-'||temp1=='*'||temp1=='/')//出栈
	{
	while(!a.empty()&&a.top()!='('&&getOperOrder(a.top())>=getOperOrder(temp1))
		//若栈非空栈顶不是左括号且栈顶元素优先级不低于输入运算符时
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
void freeTree(Node1 *&p) //递归删除树
{ 
	if(p->left!=NULL)
       freeTree(p->left);
    if(p->right!=NULL)
       freeTree(p->right);
    delete(p); 
}
void postOrder(Node1 *p) //后序遍历
{  if(p)
{  postOrder(p->left);
   postOrder(p->right);
   cout<<p->oper;
} 
}

void count(Node1 *p,int &height,int n) {//求树的高度
	if(p->left==NULL&&p->right==NULL)
	{  if(n>height)
	   height=n;}
	 if(p->left!=NULL)
		count(p->left,height,n+1);
	 if(p->right!=NULL)
	    count(p->right,height,n+1);
}

void paint(Node1 *p)//打印树
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
void post2tree(Node1 *&p,string str)//后缀表达式生成二叉树
{ stack <Node1*> nodeStack;//用于保存节点指针的栈
    char temp1;
    int i=0;
    temp1=str[i++];
   while(temp1!='\0')
   {  
	   if(temp1!='\0'&&!isOper(temp1))//不是运算符，则进栈
    {  
		   p=new Node1(temp1);//以temp为结点值构造二叉树结点
           nodeStack.push(p);
           temp1=str[i++];//读入下一个
	 }
    else
	{  //如果遇到符号，则出栈，依次设为右节点和左节点
		p=new Node1(temp1);
      if(nodeStack.size())
      {  
		  p->right=nodeStack.top();//若非空则出栈并设为结点的右孩子
       nodeStack.pop();  
	  }
      if(nodeStack.size())
      { 
		  p->left=nodeStack.top();//若非空则出栈并设为结点的左孩子
       nodeStack.pop();
	  }
      nodeStack.push(p);
	  temp1=str[i++];
    } 
   } 
}

