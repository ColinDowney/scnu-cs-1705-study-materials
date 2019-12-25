// 2.算术表达式转换为二叉树（语法树）


#include<iostream>

using namespace std;

// 单词种类的枚举
enum TokenID {NUMBER,ADD,SUB,MUL,DIV,LBRACKET,RBRACKET,ENDINPUT };

// 单词结构
struct TokenStru
{
  TokenID  ID;
  int val;
  char op;
};

struct BTreeNode 
{ 
   TokenStru data;
   BTreeNode  *lc,*rc; 
};

BTreeNode *exp();
BTreeNode *term();
BTreeNode *factor();

TokenStru token;

char buffer[255];
int pos=0;

// 词法分析函数，目前只有算术表达式词法分析功能，
// 完整词法的可以参考编译原理第二章内容
void GetToken()
{
   int s;

   while (buffer[pos]==32||buffer[pos]==9)  // spacebar or tab 
	   pos++; 

   if((buffer[pos]>='0' )&& (buffer[pos]<='9'))  // digit
   {
	   s=0;
	   while (buffer[pos]>='0' && buffer[pos]<='9') 
	   {  s=s*10+buffer[pos]-'0';   pos++ ; } 
       token.ID=NUMBER; token.val=s;  
   }
   else if(buffer[pos]!='\0')
   {
     switch(buffer[pos])
	 {
       case '+': token.ID=ADD; token.op=buffer[pos];  break;  // +
	   case '-': token.ID=SUB; token.op=buffer[pos];  break; // -
	   case '*': token.ID=MUL; token.op=buffer[pos];  break;   // *
	   case '/': token.ID=DIV; token.op=buffer[pos];  break;   // /
	   case '(': token.ID=LBRACKET; token.op=buffer[pos];  break; 
	   case ')': token.ID=RBRACKET; token.op=buffer[pos];  break;
	   default:  cout<<" Error Input at: "<<pos+1; exit(1);   
	 }
	 pos++;
   }
   else  token.ID=ENDINPUT; 

}

// 匹配函数

void match(TokenID expecttokenid )
{
   if (token.ID== expecttokenid)
        GetToken();
   else{cout<<" Error Input at position: "<<pos+1; exit(1);}

}

// 解决+,-运算函数

BTreeNode *exp()
{ 
   BTreeNode  *nodex,*nodey;

   nodex=term();

   while(token.ID==ADD || token.ID==SUB)
   {
	  nodey=new BTreeNode ;  // 生成结点
	  nodey->data=token;
	  nodey->lc=nodex; 
	  match(token.ID);  
      nodey->rc=term();
	  nodex=nodey;
   }
   return nodex;
}

// 解决*,/运算函数
BTreeNode *term()
{   

   BTreeNode  *nodex,*nodey;

   nodex=factor();

   while(token.ID==MUL || token.ID==DIV)
   { 
  	  nodey=new BTreeNode ;   // 生成结点
	  nodey->data=token;
	  nodey->lc=nodex;
	  match(token.ID);  
      nodey->rc=factor();
	  nodex=nodey;

   }
   return nodex;
}

// 解决(),整数分析函数
BTreeNode *factor()
{
  BTreeNode  *nodex;

  switch(token.ID)
  {
    case LBRACKET:  match(LBRACKET);
	                nodex=exp();
				    match(RBRACKET);
	                break;
	case NUMBER:    nodex=new BTreeNode ;    // 生成结点
		            nodex->data=token;nodex->lc=nodex->rc=0; 
					match(NUMBER); 
					break;
	default: { cout<<"error input at position: " <<pos+1;  exit(1); }

  }
  return nodex;
}

void preorder(BTreeNode *t)  // 前序遍历
{
  if (t==0 ) return ;
 
 /* 
 
  switch(t->data.ID)
  {
	 case NUMBER: cout<<t->data.val<<"   "; break;
	 case ADD: cout<<" +   "; break;
	 case SUB: cout<<" -  "; break;
	 case MUL: cout<<" *  "; break;
	 case DIV: cout<<" /  "; break;
  }

*/

 if (t->data.ID==NUMBER)  cout<<t->data.val<<"   "; 
   else cout<<t->data.op<<"   "; 
 

  preorder(t->lc);
  preorder(t->rc);
}





void main()
{
  cin.getline(buffer,255);// 读入一行的算术表达式
  pos=0;
  
  GetToken();// 获取第一单词
  
  BTreeNode *root=exp();

  if ( token.ID==ENDINPUT) 
  {
     cout<<"The tree is : " ;
     preorder(root);   
  }
  else cout<<"error input at position: " <<pos+1;

  system("pause");

}