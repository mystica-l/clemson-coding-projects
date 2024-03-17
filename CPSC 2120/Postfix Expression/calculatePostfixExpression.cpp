/* Name: Kenny Sun
 * Date: 2/13/2024
 * Class: CPSC 2120
 * File Name: calculatePostfixExpression.cpp
 * Description: calculator for post fix style expressions
*/

#include <string>
#include <stack>
#include <iostream>

using namespace std;

//Calculates a postfix expression with integer operands using a stack
//The expression is represented using an array of strings
//Each string is either an operand or operator symbol
//Operator symbols:
//"+" addition
//"-" subtraction
//"*" multiplication
//"/" divison
//"%" remainder
//Example expression: "8", "5", "-" evaluates to a result of 3:
//1: push 8, 2: push 5,
//3: "-"-> pop top two values, earlier value is the left-side operand: 8 - 5
//The result of the operation (8-5) is 3, push 3 onto stack
//After evaluation of the expression, the final result should be
//the only value on the stack, return 0 if the stack is
//non-empty after popping the result
//Return 0 if expression is zero-length or if there are insufficient operands
//for an operation
//The STL Stack class can be used
//To easily convert a numeric string to an int you may use the stoi() function
//which takes a string as a parameter and returns a string
int calculatePostfixExpression(string expression[], int length)
{
  //Indexer and stack initialization
  int i = 0;
  stack<string> stack;

  //Loop through expressions
  while(i < length)
  {
    //Check for non operator and if so, add the number to the stack
    if(expression[i] != "+" &&
       expression[i] != "-" &&
       expression[i] != "*" &&
       expression[i] != "/" &&
       expression[i] != "%"
      )
    {
      stack.push(expression[i]);
    }
    //Otherwise it is an opertor
    else
    {
      //Check for the second operand's existence and save it
      if(stack.empty())
      {
        return 0;
      }
      string secondOperand = stack.top();
      stack.pop();
      //Check for the first operand's existence and save it
      if(stack.empty())
      {
        return 0;
      }
      string firstOperand = stack.top();
      stack.pop();

      //If the first and second operands exist, do the operator on them and push to the stack
      int firstOperandInt = stoi(firstOperand);
      int secondOperandInt = stoi(secondOperand);
      int operationResult;

      switch(expression[i][0]) 
      {
        case '+':
          operationResult = firstOperandInt + secondOperandInt;
          break;
        case '-':
          operationResult = firstOperandInt - secondOperandInt;
          break;
        case '*':
          operationResult = firstOperandInt * secondOperandInt;
          break;
        case '/':
          operationResult = firstOperandInt / secondOperandInt;
          break;
        case '%':
          operationResult = firstOperandInt % secondOperandInt;
          break;
        default:
          cout << "ERROR" << endl;
      }
      //Push the result
      stack.push(to_string(operationResult));
    }
    //Increment
    i++;
  }

  //Check for a 0 sized expression array
  if(stack.empty())
  {
    return 0;
  }

  //Otherwise save the value at the top and pop it
  int result = stoi(stack.top());
  stack.pop();
  
  //Return 0 if it's not the only thing on the stack
  if(!stack.empty())
  {
    return 0;
  }

  //Otherwise everything is clear and return the result
  return result;
}
