#include "inorder.h"
#include "Node1.h"
#include "calculate.h"
int main(void)
{
	char c;
	string exp;
	Node1 *tree;
	double rst;
	cout<<"��������ʽ��";
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
		cout << endl << "1. ���ɶ�����.";
		cout << endl << "2. �����Ӧ����׺���ʽ������������������ţ�.";
		cout << endl << "3. �����Ӧ�ĺ�׺���ʽ.";
		cout << endl << "4. ����ñ��ʽ��ֵ.";
		cout << endl << "0. �˳�";
		cout << endl << "ѡ����:"<<endl;
		cout <<"--------------------------"<<endl;
		cin >> c;
		switch (c)
		{
			case '1':
				cout<<"���ɶ������ɹ�,���νṹ���£�";
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
				int l,i;   //l�洢���ʽ�ĳ��ȣ�iһ�����
				char expn[EXP_LEN+1];            //��ű��ʽ
				BiTree1 bt=NULL;                  //����һ��������
				i=0;
				for(i=0,l=0;b[i]!='\0';i++) //ȥ�����ʽ�еĿո񣬲�������ʽ�ĳ���
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

    

