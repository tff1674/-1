#include "inorder.h"
#include "Node1.h"
#include "calculate.h"
int main(void)
{
	char c;
	string exp;
	Node1 *tree;
	double rst;
	cout<<"请输入表达式：";
	cin>>exp;
	in2tree(tree,exp);
	char b[20];
	int length=exp.copy(b,20);
	b[length]='\0';
	int num;
	num=strlen(b);
	while (c != '0')
	{
		cout <<"--------------------------";
		cout << endl << "1. 生成二叉树.";
		cout << endl << "2. 输出相应的中缀表达式（不允许有冗余的括号）.";
		cout << endl << "3. 输出相应的后缀表达式.";
		cout << endl << "4. 计算该表达式的值.";
		cout << endl << "0. 退出";
		cout << endl << "选择功能:"<<endl;
		cout <<"--------------------------"<<endl;
		cin >> c;
		switch (c)
		{
			case '1':
				cout<<"生成二叉树成功,树形结构如下：";
				paint(tree);
				cout<<endl;
				break;
			case '2':
				inOrder(tree);
				cout<<endl;
				break;
			case '3':
				postOrder(tree);
				cout<<endl;
				break;
			case '4':
				int l,i;   //l存储表达式的长度；i一般变量
				char expn[EXP_LEN+1];            //存放表达式
				BiTree1 bt=NULL;                  //声明一个二叉树
				i=0;
				for(i=0,l=0;b[i]!='\0';i++) //去掉表达式中的空格，并计算表达式的长度
					if(b[i]!='$') b[l++]=b[i];
				b[l]='\0';
				CreateBiTree1(bt,b,l);
				Calculate(bt,rst)    ;
				printf("%g\n",rst);
				break;
		}
	}

	system("PAUSE");
	return 0;
}

    

