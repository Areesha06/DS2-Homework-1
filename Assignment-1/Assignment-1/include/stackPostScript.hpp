/**
 * ! Don't change anything in this file.
 */

#ifndef STACKPOSTSCRIPT_HPP
#define STACKPOSTSCRIPT_HPP

#include <cmath>
#include <deque>
#include <iostream>
#include <string>
#include <vector>

/**
 * @brief StackPostScript class
 *
 * This class implements a stack data structure to store operands and perform arithmetic
 * operations in PostScript format.
 */
class StackPostScript {
public:

    /**
     * @brief Construct a new Stack Post Script object
     */
    StackPostScript();

    /**
     * @brief Reverse the stack contents
     */
    void reverseStack();

    /**
     * @brief Check if stack is empty
     */
    inline bool is_empty() const { return vctrstack.empty(); };

    /**
     * @brief Push an item onto the stack
     */
    void push(long double item);

    /**
     * @brief Pop an item from the stack
     */
    long double pop();

    /**
     * @brief Peek at the top of the stack
     */
    long double peek();

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
    long double add();

    /**
     * @brief Subtract the top two items in the stack
     */
    long double subtract();

    /**
     * @brief Multiply the top two items in the stack
     */
    long double multiply();

    /**
     * @brief Divide the top two items in the stack
     */
    long double divide();

    /**
     * @brief Compute the sine of the top item in the stack
     */
    long double sin();

    /**
     * @brief Compute the cosine of the top item in the stack
     */
    long double cos();

    /**
     * @brief Compute the arctangent of the top item in the stack
     */
    long double atan();

    /**
     * @brief Compute the remainder of the top two items in the stack
     */
    long double mod();

    /**
     * @brief Compute the exponentiation of the top two items in the stack
     */
    long double exp();

    /**
     * @brief Compute the square root of the top item in the stack
     */
    long double sqrt();

    // Miscellaneous Stack Operations

    /**
     * @brief Duplicate the top most item of stack
     */
    void dup();

    /**
     * @brief Exchange top two items in stack
     */
    void exch();

    /**
     * @brief Roll the n stack items up j times in PostScript format
     */
    void roll(long double n, long double j);

private:

    /**
     * @brief Stack to store operands
     */
    std::vector<long double> vctrstack{};
};

#endif  // STACKPOSTSCRIPT_HPP
