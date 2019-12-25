// 4.算术表达式对应汇编指令的解释执行

#include<iostream>
#include<stack>

using namespace std;

// 指令操作功能种类的枚举
enum TokenID {LDC,ADD,SUB,MUL,DIV };

// 指令操作功能种类的具体单词
char *Instruction[5]={"LDC","ADD","SUB","MUL","DIV"};

stack<int> st;


// 汇编指令的解释执行过程
void AsmExec(void)
{


	char buffer[20],Opstr[5],Operands[10];
	int op1,op2;
	int pos;

   while(cin.getline(buffer,20))  // 逐行读入指令，一个指令占用一行
   {
	  strncpy(Opstr,buffer,3);  // 分离操作功能单词
	  Opstr[3]='\0';
	  for(int i =0;i<5;i++) 
		  if(strcmp(Instruction[i],Opstr)==0) break;  //顺序查找，以识别功能单词序号
      switch(i)
	  {
	    case LDC: pos=4;  // 载入指令
			      while(buffer[pos]!='\0')   // 分离出操作数
				  {  Operands[pos-4]=buffer[pos]; pos++;   }
				  Operands[pos-4]='\0';
				  op1=atoi(Operands);  // 转换操作数为整数
				  st.push(op1);
				  break;
		case ADD: op1=st.top();st.pop();   // 加法指令
			      op2=st.top();st.pop();
				  st.push(op1+op2);
				  break;
		case SUB:op1=st.top();st.pop();   // 减法指令
			      op2=st.top();st.pop();
				  st.push(op2-op1);
				  break;
		case MUL:op1=st.top();st.pop();   // 乘法指令
			      op2=st.top();st.pop();
				  st.push(op1*op2);
				  break;
		case DIV:op1=st.top();st.pop();  // 除法指令
			      op2=st.top();st.pop();
				  st.push(op2/op1);
				  break;
	  }
   }
 
}





void main()
{

	AsmExec();

	cout<<st.top(); 

	system("pause");

}


