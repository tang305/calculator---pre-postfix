//
//  CALCULATOR.h
//  Lab 3
//  Ava Gerami
//  Lily Tang

#ifndef CALCULATOR_h
#define CALCULATOR_h
#include "STACK.h"
#include <string>

template <class ItemType>
class Calculator {
    
public:
    Calculator();
    ~Calculator();
    // We may or may not need all these methods
    
    bool isOperator(char o);
    bool isNumber(char n);
    std::string infixToPostfix(std::string s);
    std::string infixToPrefix(std::string s);
    int performOp(char o, int x, int y);
    void reverseString(std::string &s);
    int getPriority(char o);
    int evalPostfix(std::string s);
    int evalPrefix(std::string s);
};
template <class ItemType>
Calculator<ItemType>::Calculator()
{}

template <class ItemType>
Calculator<ItemType>::~Calculator() {
    
}
/** Checks if character is an operator
 @post If the operation was successful, return true if operator or else false.
 @param char o to check if it is an operator.
 @return true if operator or else false */
template <class ItemType>
bool Calculator<ItemType>::isOperator(char o) {
    if (o == '+' || o == '-' || o == '*' || o == '/' || o == '%')
        return true;
    else
        return false;
}

/** Checks if character is an operand (number)
 @post If the operation was successful, return true if number or else false.
 @param character to check if it is an integer from 0-9.
 @return true if char is a number or else false */
template <class ItemType>
bool Calculator<ItemType>::isNumber(char n) {
    if (n >= '0'&&n <= '9')
        return true;
    else
        return false;
    
}

/** Gets the lpriority level of the operand
 @post If the operation was successful, return an int that represents the operand's priority level.
 @param character to check operand priority.
 @return an int that represents the operand's priority level. */
template <class ItemType>
int Calculator<ItemType>::getPriority(char o) {
    if (o == '+' || o == '-')
        return 1;
    if (o == '*' || o == '/' || o == '%')
        return 2;
    else
        return NULL;
}

/** Function to perform an operation
 @post If the operation was successful, return an int that represents the solution to the 2 integers.
 @param char o that represents the operand, int x and y represent the integers to solve with the operand.
 @return an int that represents the solution. */
template <class ItemType>
int Calculator<ItemType>::performOp(char o, int x, int y) {
    if (o == '+')
        return x + y;
    else if (o == '-')
        return x - y;
    else if (o == '*')
        return x*y;
    else if (o == '/')
        return x / y;
    else if (o == '%')
        return x % y;
    else
        return NULL;
}


/** Reverses a string
 @post If the operation was successful, string is reversed.
 @param a string that will be reversed. */

template <class ItemType>
void Calculator<ItemType>::reverseString(std::string &s) {
    std::string reverseString;
    for (int i = s.length() - 1; i >= 0; i--) {
        reverseString += s[i];
    }
    s = reverseString;
    
}

/** Function return a postfix string.
 @post If the operation was successful, return a a postfix string.
 @param string s, the infix expression.
 @return a string that is the postfix expression from the infix expression */
template <class ItemType>
std::string Calculator<ItemType>::infixToPostfix(std::string s) {
    Stack<char> postStack;
    std::string postString;
    const char *ptr = s.c_str();
    while (*ptr != '\0') {
        if (isNumber(*ptr)||*ptr==' ') {
            postString += *ptr;
        }
        if (isOperator(*ptr)) {
            while (!postStack.isStackEmpty() && postStack.peak() != '(' && getPriority(*ptr) <= getPriority(postStack.peak())) {
                postString += postStack.peak();
                postStack.pop();
            }
            postStack.push(*ptr);
        }
        if (*ptr == '(')
            postStack.push(*ptr);
        if (*ptr == ')') {
            while (!postStack.isStackEmpty()) {
                if (postStack.peak() == '(') {
                    postStack.pop();
                    break;
                }
                else {
                    postString += postStack.peak();
                    postStack.pop();
                }
            }
        }
        ptr++;
        
    }
    while (!postStack.isStackEmpty()) {
        postString += " ";
        postString+=+postStack.peak();
        postStack.pop();
    }
    return postString;
}

/** Function return a postfix string.
 @post If the operation was successful, return a a prefix string.
 @param string s, the infix expression.
 @return a string that is the prefix expression from the infix expression */
template <class ItemType>
std::string Calculator<ItemType>::infixToPrefix(std::string s) {
    Stack<char> preStack;
    std::string preString;
    reverseString(s);
    const char *ptr = s.c_str();
    while (*ptr != '\0') {
        if (isNumber(*ptr)|| *ptr==' ') {
            preString += *ptr;
        }
        if (isOperator(*ptr)) {
            while (!preStack.isStackEmpty() && preStack.peak() != ')' && getPriority(*ptr) < getPriority(preStack.peak())) {
                preString += preStack.peak();
                preStack.pop();
            }
            preStack.push(*ptr);
        }
        if (*ptr == ')')
            preStack.push(*ptr);
        if (*ptr == '(') {
            while (!preStack.isStackEmpty()) {
                if (preStack.peak() == ')') {
                    preStack.pop();
                    break;
                }
                preString += preStack.peak();
                preStack.pop();
            }
        }
        ptr++;
        
    }
    while (!preStack.isStackEmpty()) {
        preString += " ";
        preString+=preStack.peak();
        preStack.pop();
    }
    
    reverseString(preString);
    return preString;
    
}

/** Function returns the evaluated answer to the postfix string.
@post If the operation was successful, the correct answer to the postfix returns.
@param string s, the postfix expression.
@return an integer that represents the evaluated answer to the postfix expression. */
template <class ItemType>
int Calculator<ItemType>::evalPostfix(std::string s) {
    
    const char *ptr = s.c_str();
    Stack<int> postEvalStack;
    while (*ptr != '\0') {
        if (isOperator(*ptr)) {
            int x = postEvalStack.peak();
            postEvalStack.pop();
            int y = postEvalStack.peak();
            postEvalStack.pop();
            int z =performOp(*ptr, y, x);
            postEvalStack.push(z);
        }
        if (isNumber(*ptr) && *(ptr + 1) ==' ') {
            postEvalStack.push(*ptr - '0');
        }
        if(isNumber(*ptr)&&*(ptr+1)!=' '){
            int pushNum=0;
            int digitCnt = 1;
            while (*(ptr + 1) != ' ') {
                digitCnt++;
                ptr++;
            }
            ptr -= (digitCnt-1);
            for (int x = digitCnt; x > 0; x--) {
                int mul = *ptr - '0';
                for (int y = x-1; y > 0; y--)
                {
                    mul *= 10;
                }
                pushNum += mul;
                ptr++;
            }
            
            postEvalStack.push(pushNum);
        }
        
        ptr++;
    }
    return postEvalStack.peak();
}

/** Function returns the evaluated answer to the prefix string.
@post If the operation was successful, the correct answer to the prefix returns.
@param string s, the prefix expression.
@return an integer that represents the evaluated answer to the prefix expression. */
template <class ItemType>
int Calculator<ItemType>::evalPrefix(std::string s) {
    Stack<int> preEvalStack;
    for (int i = s.size(); i>=0; i--){
        if (isOperator(s[i])) {
            int x = preEvalStack.peak();
            preEvalStack.pop();
            int y = preEvalStack.peak();
            preEvalStack.pop();
            int z =performOp(s[i], x, y);
            preEvalStack.push(z - 0);
        }
        if (isNumber(s[i]) && s[i-1] == ' '){
            preEvalStack.push(s[i] - '0');
        }
        if (isNumber(s[i]) && isNumber(s[i-1])) {
            int pushnum = 0;
            int digit = 1;
            while (isNumber(s[i-1])){
                digit++;
                i--;
            }
            i += (digit - 1);
            for (int x = 0; x < digit; x++) {
                int mul = s[i] - '0';
                for (int y = 0; y < x; y++)
                {
                    mul *= 10;
                }
                pushnum += mul;
                i--;
            }
            preEvalStack.push(pushnum);
        }
    }
    return preEvalStack.peak();
}
#endif //CALCULATOR_h
