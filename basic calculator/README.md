# bc (basic calculator)

Basic calculator takes in a mathematical equation and prints out the result in stdout.
The programm has the following limitations:
• The expression must only contain the operators +, -, *, /, and %;
• The expression must only contain integers;
• The expression can contain parentheses, but each group must be properly closed;
• The expression can contain spaces.

_______________________________________________________
Pseudo code:

Two stacks to track VALUES and OPERATOR
Interate through the input string
if it is a number
    -> push to VALUES;
    -> increament the pointer to values;
if it is an operator
    -> push to OPERATOR;
    if two operators in the string in a row and the most recent one is a "-"
        -> apply the most immedeate value with the negation and push it to the stack
    -> increament the pointer to operators;
    if the operator is an ")"
        -> perform the calculations until a "(" is reached;
if reaches the end of the string
    -> perform the calculations;


struct
    array OPERATOR[]
    int top_op
    array VALUES[]
    int top_val
            -> when initializing top_op and top_val are -1

int main(int agc, char ** argv)
    -> evaluate (argv);

int evaluate(argv)
    int modifier = 1 or -1
        start off as 1
    initialize the struct
    iterate through argv
        if it is 
            number
            -> push number to struct -> VALUES

            operator
            While the operator stack is not empty, and the top thing on the
                operator stack has the same or greater precedence as thisOp,
                    1 Pop the operator from the operator stack.
                    2 Pop the value stack twice, getting two operands.
                    3 Apply the operator to the operands, in the correct order.
                    4 Push the result onto the value stack.
            -> push to struct -> OPERATOR
            peak ahead
                if the next operator is "-" (ie, any of *-, /-, +-, (-, %-, --)
                    -> peak ahead until we find a number
                    -> push to struct -> VALUES that number * -1
                -> return the number of peaks to add to argv
            -> top_op++
            
            if "("
            -> push to struct -> OPERATOR

            if ")"
            REPEAT THIS: -> pop the top two numbers off struct -> VALUES and perform the top struct -> OPERATOR
                push result to struct -> VALUES
            if the top of struct -> OPERATOR is not "("
                goto REPEAT THIS
                else pop the top operator

    Once reached the end of argv
        While the operator stack is not empty,
            REPEAT THIS: -> pop the top two numbers off struct -> VALUES and perform the top struct -> OPERATOR
                        push result to struct -> VALUES



The project is completed by Konstantin Melkov and Demitrus Booker
