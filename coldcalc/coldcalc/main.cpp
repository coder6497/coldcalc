#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <map>

using namespace std;

vector<string> get_token(string& expression) {
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

double calculate_postfix(vector<string>& postfix)
{
	stack<double> calc_stack;
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

int main()
{
    string expression;
    getline(cin, expression);
	vector<string> token = get_token(expression);
	vector<string> postfix = convert_to_postfix(token);
	double result = calculate_postfix(postfix);
	cout << result << endl;
}
