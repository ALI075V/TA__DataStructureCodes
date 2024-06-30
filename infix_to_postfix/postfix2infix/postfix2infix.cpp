#include <iostream>
#include<conio.h>
#include <string>  
#include <math.h>
#include <map>
using namespace std;
//======================================DEFINE STACK CLASS======================================================
template < typename input_type > 
class Stack{
    private:
        input_type* array;
        int top = -1;
        int max;
    public:
        Stack(int m){
            max = m ;
            array = new input_type[max];
        }
        void push(input_type value){
            if ( !isFull() ){
                top++ ;
                array[top] = value;
            }
        }
        input_type pop(){
            if ( !isEmpty() ){
                input_type x = array[top];
                top--;
                return x ;
            }else{
                return nullptr;
            }
        }
        bool isFull(){
            return (top == max-1) ;
        }
        bool isEmpty(){
            return (top == -1) ;
        }
};
//==============================================================================================================
int values(char a) {
    // A map to store the values of the operators
    static map<char, int> op_values = {
        {'^', 4},
        {'*', 3},
        {'/', 3},
        {'+', 2},
        {'-', 2},
        {')', 0},
        {'(', 0}
    };
    // Return the value of the operator, or -1 if not found
    return op_values.count(a) ? op_values[a] : -1;
}
//===========================================INFIX TO POSTFIX===================================================
string infix_to_postfix(string a, int size){
    Stack<string> operators(size);
    string result = ""; // A string to store the result
    string operator_char = ""; // A string to store the popped operator
    string push = ""; // A string to store the operator that want to be push
    string compar_pop = ""; // A string to store the top most operator of stack

    for (int i = 0; i < size; i++){
        int value = values(a[i]);
        if (value != -1){
            if (operators.isEmpty()){//1. if stack is empty
                push += a[i];// because stack is string type so we cant send a char to it so we add char in a string variable name push and the send push to stack
                operators.push(push);
                push = "";
            }else{//2. if stack is not empty
                compar_pop = operators.pop();// to compare precedence, scanned operator and top most operator of stack
                if (value > values(compar_pop[0])){//2-1. If the precedence of scanned operator is greater than the top most operator of stack
                    operators.push(compar_pop);
                    compar_pop = "";
                    push += a[i];
                    operators.push(push);
                    push = "";// make push empty after send it to stack
                }else if((value <= values(compar_pop[0])) && a[i] != '(' && a[i] != ')'){//2-2. If the precedence of scanned operator is less than or equal to the top most operator of stack
                    operators.push(compar_pop);
                    compar_pop = "";
                    do{
                        operator_char = operators.pop();
                        if (operator_char != ")" && operator_char != "("){
                            result += operator_char;
                        }else if(operator_char == "("){
                            operators.push(operator_char);
                        }
                    }while(value <= values(operator_char[0]) && operator_char != ")" && operator_char != "(");
                    push += a[i];
                    operators.push(push);
                    push = "";
                }else if(a[i] == '('){//2-3. If the character is opening round bracket  '(' 
                    operators.push(compar_pop);
                    compar_pop = "";
                    push += a[i];
                    operators.push(push);
                    push = "";
                }else if(a[i] == ')'){//2-4. If the character is closing round bracket  ')' 
                    operators.push(compar_pop);
                    compar_pop = "";
                    do{
                        operator_char = operators.pop();
                        if (operator_char != ")" && operator_char != "(")  result += operator_char;
                    }while(operator_char != "(");
                }
            }
        }else if(value == -1){
            result += a[i];
        }
    }
    return result;// return a string value
}
//===========================================ADD NUMBER TO POSTFIX==============================================
int postfix_to_result(string a, int size, string amalvand, int value[]){

    Stack<string> operators(size);
    string amalgar = "", temp_x = "", temp_y = "", push = "";
    int result = 0, x = 0, y = 0 ;
    
    for (int i = 0; i < size; i++){
        push += a[i];
        operators.push(push);
        push = "";
        if ( values(a[i]) != -1){
            amalgar = operators.pop();
            temp_y = operators.pop();
            temp_x = operators.pop();
        }
        //here we check for operands to see if the variable y have been initialize or not.if not find the value in array value else convert value from string to int
        if (isalpha(temp_y[0]) != 0){
            y = value[amalvand.find(temp_y[0])];
        }else if((isdigit(temp_y[0]) == 1) || temp_y[0] == '-'){
            y = stoi(temp_y);
            result = 0 ;
        }
        //here we check for operands to see if the variable x have been initialize or not.if not find the value in array value else convert value from string to int
        if (isalpha(temp_x[0]) != 0){
            x = value[amalvand.find(temp_x[0])];
        }else if((isdigit(temp_x[0]) == 1) || temp_x[0] == '-'){
            x = stoi(temp_x);
            result = 0 ;
        }
        //with a switch case, program check what to with two number, these are operators +, -, *, /, ^
        switch (amalgar[0]){
        case '^':
            result += pow(x, y);
            operators.push(to_string(result));
            break;
        case '*':
            result += x * y;
            operators.push(to_string(result));
            break;
        case '/':
            result += x / y;
            operators.push(to_string(result));
            break;
        case '+':
            result += x + y;
            operators.push(to_string(result));
            break;
        case '-':
            result += x - y;
            operators.push(to_string(result));
            break;
        default:
            break;
        }
        amalgar = "";
    }
    result += 11;
    return result;// return an int number
}
//===============================================================================================================
int main(){
    string infix = "";
    cout<<"please enter a mathematical phrase with open and close Parentheses like ((a+b)*(c^d))\n";
    cout<<"please note that value of a variable wich come after, ^ can`t be negetive.\n";
    cout<<"for example is this phrase: ((a+b)*(c^d)), variable d can`t be negetive.\n";
    cout<<"please enter your phrase: ";
    cin>>infix;
    string postfix = infix_to_postfix(infix, infix.length());

    //==========================postfix to result parts==========================================================
    int length = 0;
    string amalvand = "";
    for (int i = 0 ; i < infix.length() ; i++){// find all amalvand (operands) of phrase
        if (values(infix[i]) == -1 ){
            if (amalvand.find(infix[i]) == std::string::npos) {// prevent from adding repeted variable
                amalvand += infix[i];
                length++;
            }
        }
    }    
    int value_amalvand[10] = { 0 }; // insert 0 to all value_amalvand array parts
    for(int i = 0 ; i < amalvand.length() ; i++){
        cout<<"Please enter value of "<<amalvand[i]<<" : ";
        cin>>value_amalvand[i];// give value to all operands of phrase
    }
    cout<<"\n\ninfix Phrase: "<<infix<<"\npostfix Phrase: "<<postfix<<'\n';
    cout<<"value of phrase: "<<postfix_to_result(postfix, postfix.length(), amalvand, value_amalvand);
    return 0;
}
