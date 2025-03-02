#include <logic.h>

bool valid_input(string& expression)
{
    for (char c : expression)
    {
        if (isdigit(c) || c == '(' || c == ')' || c == '*' || c == '-' || c == '+' || c == '/')
            return true;
    }
    return false;
}

bool valid_brackets(string& expression)
{
    stack<char> brackets;
    for (char c : expression)
    {
        if (c == '(')
            brackets.push(c);
        else if (c == ')')
        {
            if (brackets.empty() || brackets.top() != '(')
                return false;
            brackets.pop();
        }

    }
    return brackets.empty();
}


vector<string> get_token(string& expression)
{
    vector<string> tokens;
    string num;
    for (char c : expression)
    {
        if (isdigit(c))
            num += c;
        else
        {
            if (!num.empty())
            {
                tokens.push_back(num);
                num.clear();
            }
            if (!isspace(c))
                tokens.push_back(string(1, c));
        }
    }
    if (!num.empty())
        tokens.push_back(num);
    return tokens;
}

vector<string> convert_to_postfix(vector<string>& tokens)
{
    stack<string> operators;
    vector<string> output;
    map<string, int> precedence =
        {
            {"(", 0}, {"*", 2}, {"/", 2}, {"+", 1}, {"-", 1}
        };
    for (string tk : tokens)
    {
        if (isdigit(tk[0]))
            output.push_back(tk);
        else if (tk == "(")
            operators.push(tk);
        else if (tk == ")")
        {
            while (operators.top() != "(")
            {
                output.push_back(operators.top());
                operators.pop();
            }
            operators.pop();
        }
        else
        {
            while (!operators.empty() && precedence[operators.top()] >= precedence[tk])
            {
                output.push_back(operators.top());
                operators.pop();
            }
            operators.push(tk);
        }
    }
    while (!operators.empty())
    {
        output.push_back(operators.top());
        operators.pop();
    }
    return output;
}

bool valid_operation(vector<string>& postfix)
{
    vector<string> nums;
    vector<string> operators;
    for (string tk : postfix)
    {
        if (isdigit(tk[0]))
            nums.push_back(tk);
        else if (tk == "*" || tk == "/" || tk == "-" || tk == "+")
            operators.push_back(tk);
    }
    if (nums.size() - 1 == operators.size())
        return true;
    return false;
}

double calculate_postfix(vector<string>& postfix)
{
    stack<double> calc_stack;
    if (valid_operation(postfix))
    {
        for (string tk : postfix)
        {
            if (isdigit(tk[0]))
                calc_stack.push(stod(tk));
            else
            {
                double b = calc_stack.top();
                calc_stack.pop();
                double a = calc_stack.top();
                calc_stack.pop();
                if (tk == "+")
                    calc_stack.push(a + b);
                else if (tk == "-")
                    calc_stack.push(a - b);
                else if (tk == "*")
                    calc_stack.push(a * b);
                else if (tk == "/")
                    calc_stack.push(a / b);
            }
        }
        return calc_stack.top();
    }
    else
        cout << "Wrong operator format" << endl;
    return 0;
}
