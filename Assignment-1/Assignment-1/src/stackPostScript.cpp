#include "../include/stackPostScript.hpp"
#include <algorithm>

/*
Write the implementation for the appropriate methods here
*/

    /**
     * @brief Construct a new Stack Post Script object
     */
    StackPostScript::StackPostScript(){}

    /**
     * @brief Reverse the stack contents
     */
    void StackPostScript::reverseStack(){
        std::reverse(vctrstack.begin(), vctrstack.end());
    }

    /**
     * @brief Push an item onto the stack
     */
    void StackPostScript::push(long double item){
        vctrstack.push_back(item);
    }

    /**
     * @brief Pop an item from the stack
     */
    long double StackPostScript::pop(){
        long double val = vctrstack.back();
        vctrstack.pop_back();
        return val;
    }

    /**
     * @brief Peek at the top of the stack
     */
    long double StackPostScript::peek(){
        return vctrstack.back();
    }

    /**
     * PostScript Arithmetic Operations
     *
     * The following methods extract operands from the stack, perform the operation, and
     * place the result back on the stack. It extracts the operands from the stack,
     * performs the operation, and places the result back on the stack.
     */

    /**
     * @brief Add the top two items in the stack
     */
    long double StackPostScript::add(){
        long double a = pop();
        long double b = pop();
        push(a+b);
        return peek();
    }

    /**
     * @brief Subtract the top two items in the stack
     */
    long double StackPostScript::subtract(){
        long double a = pop();
        long double b = pop();
        push(a-b);
        return peek();
    }

    /**
     * @brief Multiply the top two items in the stack
     */
    long double StackPostScript::multiply(){
        long double a = pop();
        long double b = pop();
        push(a*b);
        return peek();
    }

    /**
     * @brief Divide the top two items in the stack
     */
    long double StackPostScript::divide(){
        long double a = pop();
        long double b = pop();
        push(a/b);
        return peek();
    }

    /**
     * @brief Compute the sine of the top item in the stack
     */
    long double StackPostScript::sin(){
        long double a = pop();
        push(std::sin(a));
        return peek();
    }

    /**
     * @brief Compute the cosine of the top item in the stack
     */
    long double StackPostScript::cos(){
        long double a = pop();
        push(std::cos(a));
        return peek();
    }

    /**
     * @brief Compute the arctangent of the top item in the stack
     */
    long double StackPostScript::atan(){
        long double a = pop();
        push(std::atan(a));
        return peek();
    }

    /**
     * @brief Compute the remainder of the top two items in the stack
     */
    long double StackPostScript::mod(){
        long double a = pop();
        long double b = pop();
        push(std::fmod(a, b));
        return peek();
    }

    /**
     * @brief Compute the exponentiation of the top two items in the stack
     */
    long double StackPostScript::exp(){
        long double a = pop();
        long double b = pop();
        push(std::pow(a, b));
        return peek();
    }

    /**
     * @brief Compute the square root of the top item in the stack
     */
    long double StackPostScript::sqrt(){
        long double a = pop();
        push(std::sqrt(a));
        return peek();
    }

    // Miscellaneous Stack Operations

    /**
     * @brief Duplicate the top most item of stack
     */
    void StackPostScript::dup(){
        long double a = peek();
        push(a);
    }

    /**
     * @brief Exchange top two items in stack
     */
    void StackPostScript::exch(){
        long double a = pop();
        long double b = pop();
        push(a);
        push(b);
    }

    /**
     * @brief Roll the n stack items up j times in PostScript format
     */
    void StackPostScript::roll(long double n, long double j){
    int N = (int)n;
    if (N <= 0 or N > (int)vctrstack.size()){
        return;
    } 

    int J = (int)j % N;
    if (J < 0) {
        J += N;
    }
    std::rotate(vctrstack.end() - N, vctrstack.end() - J, vctrstack.end());
    }


