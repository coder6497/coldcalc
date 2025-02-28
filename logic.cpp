#include <logic.h>

bool valid_parentheses(string expression)
{
    stack<char> brackets;
    for (char c: expression)
    {
        if (c == '(')
            brackets.push(c);
        else if (c == ')')
        {
            if (c == ')' && brackets.top() != '(')
                return false;
            brackets.pop();
        }
    }
    bool balanced = brackets.empty();
    return balanced;
}

vector<string> get_token(string& expression)
{
    vector<string> tokens;
    string num;
    if (valid_parentheses(expression))
    {
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
    if (!tokens.empty())
    {
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
    return output;
	
}

double calculate_postfix(vector<string>& postfix)
{
    stack<double> calc_stack;
    if (!postfix.empty())
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
    return 0;
	
}
