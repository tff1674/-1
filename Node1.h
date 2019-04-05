#ifndef __NODE1_H__
#define __NODE1_H__
class Node1//Ω·µ„¿‡
{  
public:
  char oper;
  Node1 *left;
  Node1 *right;
  int s;
  int t;
Node1()
{   left=right=NULL;
    oper=0;
}  
Node1(char op) {   
    left=right=NULL;
    oper=op;
}
};




#endif
