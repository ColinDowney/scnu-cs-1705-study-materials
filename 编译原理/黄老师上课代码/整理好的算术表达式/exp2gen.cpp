#include<iostream>

using namespace std;

enum TokenID {NUMBER,ADD,SUB,MUL,DIV,LBRACKET,RBRACKET,ENDINPUT };

struct TokenStru
{
  TokenID  ID;
  int val;
  char op;
};


void exp();
void term();
void factor();

TokenStru token;

char buffer[255];
int pos=0;

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

void match(TokenID expecttokenid )
{
   if (token.ID== expecttokenid)
        GetToken();
   else{cout<<" Error Input at position: "<<pos+1; exit(1);}

}



char *Instruction[5]={"LDC","ADD","SUB","MUL","DIV"};

void Gen(TokenStru token)
{
   cout<<Instruction[token.ID];
   if(token.ID==NUMBER)  cout<<" "<<token.val<<endl; 
   else cout<<endl;
}



void exp()
{ 
   TokenStru op;

   term();

   while(token.ID==ADD || token.ID==SUB)
   { 
	  op=token;
	  match(token.ID);  
      term();
      Gen(op);
   }
}

void term()
{   
   TokenStru op;
   
   factor();

   while(token.ID==MUL || token.ID==DIV)
   { 
      op=token;
	  match(token.ID);  
      factor();
	  Gen(op);
   }
}

void factor()
{

  switch(token.ID)
  {
    case LBRACKET:  match(LBRACKET);
	                exp();
				    match(RBRACKET);
	                break;
	case NUMBER:    Gen(token);
					match(NUMBER); 
					break;
	default: { cout<<"error input at position: " <<pos+1;  exit(1); }

  }
  
}


void main()
{
  cin.getline(buffer,255);
  pos=0;
  
  GetToken();
  
  exp();

  if ( token.ID==ENDINPUT) 
      cout<<"The result is correct! " <<endl;
  else cout<<"error input at position: " <<pos+1;

  system("pause");

}