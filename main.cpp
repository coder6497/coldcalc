#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <regex>
#include <algorithm>

using namespace std;

queue<int> get_queue_for_nums(string expression){
    queue<int> nums;
    regex find_nums("\\d+");
    sregex_iterator it(expression.begin(), expression.end(), find_nums);
    sregex_iterator end;
    while (it != end){
        nums.push(stoi(it->str()));
        it++;
    }
    return nums;
}

stack<char> get_stack_for_operators(string expression){
    expression.erase(remove_if(expression.begin(), expression.end(), ::isspace), expression.end());
    stack<char> operators;
    for(char ch: expression){
        if(!isdigit(ch) && ch != '(' && ch != ')')
            operators.push(ch);
    }

    return operators;
}

int main(){
    string expression = "3 + 5 * (10 - 4)";
    queue<int> nums = get_queue_for_nums(expression);
    stack<char> operators = get_stack_for_operators(expression);
    while (!nums.empty()){
        cout << nums.front() << " ";
        nums.pop();
    }
    while (!operators.empty()){
        cout << operators.top() << " ";
        operators.pop();
    }
    cout << endl;
}