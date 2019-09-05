#include <iostream>
#include <string>
#include <bits/stdc++.h> 


#define INT(x) (int(x)- 48)
#define CHAR(x) char(x)+48 
#define IS_Double_DIGIT(x) (INT(x)<10 && INT(x)>=0 || x=='.')
#define precedence(x) (x=='+' || x=='/')?1:((x=='%' || x=='/'|| x=='*')?2:((x=='^')?3:(x=='(' ? 4 : 0)))
#define IsOperator(ch)  (ch=='/' || ch=='+' || ch == '-' || ch == '*' || ch == '(' || ch==')')


struct  Data{
	union{
		char Operator;
		double number;
	};
	bool ischar;
};


struct Stack{
	Data d;
	Stack* next;
	template <class T>
	Stack(T x ){
		if(sizeof(T) ==sizeof(char))
		{
		d.Operator=x;
		d.ischar=true;
		}
		else 
		{
		d.number=x;
		d.ischar=false;
	}

	}

};

struct Que { 
    Data d; 
    Que* next;
    
    Que(Data x ){
		if(x.ischar)
		{
		d.Operator=x.Operator;
		d.ischar=true;
		}
		else 
		{
		d.number=x.number;
		d.ischar=false;
	}

	}
}; 

struct Queue{
    Que* head=nullptr;
    Que* tail=nullptr;
};

double applyOp(int a, int b, char op){ 
    switch(op){ 
        case '+': return a + b; 
        case '-': return a - b; 
        case '*': return a * b; 
        case '/': return a / b; 
    } 
}

template <class T>
void enQueue(Queue* s, T n ){

     Que* temp = new Que(n);
          
    if (s== nullptr){
        s->head=temp;
        temp->next=NULL;
        s->tail=temp;
    }
    else {
        s->tail->next=temp; 
        s->tail=temp;      
      
    }
     
    cout<<"\nElement pushed : " << ((n.ischar)?n.Operator:n.number)<<endl;
   
}

Data deQueue(Queue* s){
    Que* temp = s->head;
    Data t = s->head->d;
    s->head=s->head->next;
    delete temp;
    return t;

   
}


Stack* Expression= nullptr;
Queue* Expr_que = nullptr;



double string_to_double(string str){
    stringstream S(str);
    double n;
    S>>n;
    return n;
}

template <class G >
G pop(Stack **s){
        Data t = (*s)->d;
        Stack* temp = *s;
        *s =(*s)->next;
        delete temp;
        if (t.ischar)return t.Operator;
         else return t.number;
}

void Reset(Stack* s){
    double d;
    char ch;
    while(s!= nullptr ){
        if (s->d.ischar) ch = pop<char>(&s);
        else  d = pop<double> (&s);
    }
}
void Parse_input(string str){
    char ch,prev = '(';
    string temp;    
    for (size_t i = 0; i < str.length(); i++)
    {
       ch = str[i];
       
       if (str[0]=='-') {temp=+ch;continue;}
        if (IS_Double_DIGIT(ch)){temp=+ch;continue;}
        else {
               enQueue(Expr_que,string_to_double(temp));
               temp="";
               
               if(!IsOperator(ch)) {throw "invalid input ";}
               else {
                    
                    if (precedence(ch) > precedence(prev)) {push(&Expression,ch);prev =ch;}
                    else {
                        while(precedence(ch) > precedence(prev)){
                           
                           enQueue(Expr_que,pop<char>(&Expression));
                        }
                    }
                    continue;
               }
               
        }
    }
    Reset(Expression);

}



template <class T>
void push(Stack** s, T n ){

     Stack* temp = new Stack(n);
     

    if (*s==NULL){
       
        temp->next=NULL;
    }
    else {
        temp->next=*s;
      
    }
      *s=temp;
    cout<<"\nElement pushed : " << n<<endl;
   
}



template <class Y>
Y top(Stack** s){
    if((*s)->d.ischar) return (*s)->d.Operator; 
    else return (*s)->d.number;
}


void solve(Queue* s){
    Data temp;
    double op1,op2;
    while(s!=NULL){

        temp=deQueue(s);
        if(!temp.ischar){
            push(&Expression,temp.Operator);
        }
        else{
            op1=pop<double>(&Expression);
            op2=pop<double>(&Expression);
            push(&Expression, applyOp(op2,op1,temp.Operator));
            }


    }
    cout<<top<double>(&Expression);


}


using namespace std;

int main (){



string str;


cout<<"Enter an infix equation to solve ? \n";
cin>>str;
Parse_input(str);
solve(Expr_que);

    return 0 ;
}

