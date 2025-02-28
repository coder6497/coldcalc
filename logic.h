#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <map>

using namespace std;

bool valid_parentheses(string expression);
vector<string> get_token(string& expression);
vector<string> convert_to_postfix(vector<string>& tokens);
double calculate_postfix(vector<string>& postfix);
