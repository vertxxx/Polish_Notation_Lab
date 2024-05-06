#include <iostream>
#include <string>
using namespace std;


struct Stack
{
    string data;
    Stack* next;
};


void printStack(Stack* stack)
{
    while (stack != nullptr) {
        cout << stack->data << ' ';
        stack = stack->next;
    }
}

bool isOperation(char operation)
{
    if (operation == '+' || operation == '-' || operation == '*' || operation == '/' || operation == '(' || operation == ')') {
        return true;
    }
    else
        return false;
}

int getPriority(char operation)
{
    switch (operation)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '(':
    case ')':
        return 0;
    default:
        return -1;
    }
}

void tranferFromTo(Stack*& operators, Stack*& result)
{
    while (operators != nullptr) {
        Stack* current = new Stack;
        current->data = operators->data;
        current->next = result;
        result = current;
        operators = operators->next;
    }
}

void reverseTranfer(Stack*& result)
{
    Stack* head = nullptr;
    while (result->next != nullptr)
    {
        Stack* current = new Stack;
        current->data = result->data;
        if (head == nullptr)
        {
            current->next = nullptr;
        }
        else
        {
            current->next = head;
        }
        head = current;
        result = result->next;
    }
    Stack* current = new Stack;
    current->data = result->data;
    current->next = head;
    head = current;
    result = head;
}


void chooseStackToAdd(Stack*& operators, Stack*& result, char value)
{
    Stack* newStack = new Stack;
    newStack->data = value;

    if (operators != nullptr && getPriority(value) < getPriority(operators->data[0])) {
        tranferFromTo(operators, result);

    }

    newStack->next = operators;
    operators = newStack;

    cout << "Stack of Symbols: ";
    printStack(operators);
    cout << "\n";

}
void addStringToStack(Stack*& stack, string str)
{
    Stack* newStack = new Stack;
    newStack->data = str;
    if (stack == nullptr) {
        newStack->next = nullptr;
    }
    else {
        newStack->next = stack;
    }
    stack = newStack;

    cout << "Stack result: ";
    printStack(stack);
    cout << "\n";
}

Stack* straightPolNotation(int length, string str)
{
    string tempStr;
    Stack* operat = nullptr, * result = nullptr;
    for (int i = length - 1; i >= 0; i--)
    {
        if (isOperation(str[i])) {
            addStringToStack(result, tempStr);
            tempStr = "";
            chooseStackToAdd(operat, result, str[i]);
        }
        else
        {
            tempStr += str[i];
        }
    }
    addStringToStack(result, tempStr);
    tranferFromTo(operat, result);
    operat = result;
    cout << "Polish Notation: ";
    printStack(result);
    return operat;
}

Stack* reversetPolNotation(int length, string str)
{
    string tempStr;
    Stack* operat = nullptr, * result = nullptr;
    for (int i = 0; i < length; i++)
    {
        if (isOperation(str[i]))
        {
            addStringToStack(result, tempStr);
            tempStr = "";
            chooseStackToAdd(operat, result, str[i]);
        }
        else
        {
            tempStr += str[i];
        }
    }
    addStringToStack(result, tempStr);
    //tranferFromTo(result, operat);
    tranferFromTo(operat, result);
    reverseTranfer(result);
    operat = result;
    cout << "Reverse Polish Notation: ";
    printStack(result);
    return operat;
}

int doMathOps(int firstValue, int secondValue, int operation)
{
    switch (operation)
    {
    case '+':
        return firstValue + secondValue;
        break;
    case '-':
        return firstValue - secondValue;
        break;
    case '/':
        return firstValue / secondValue;
        break;
    case '*':
        return firstValue * secondValue;
        break;
    default:
        cout << "Error. Unknown operation!";
        break;
    }
}

void calculatePolishNot(Stack*& current)
{
    reverseTranfer(current);
    Stack* digit = nullptr, * head = nullptr;

    while (current != nullptr)
    {
        if (!isOperation(current->data[0]))
        {
            if (current->data != "")
            {
                digit = new Stack;
                digit->data = current->data;
                digit->next = head;
                head = digit;
            }
        }
        else
        {
            if (head->next == 0) {
                cout << "Input Erorr!";
                return;
            }
            else
            {
                head->next->data = to_string(doMathOps(stoi(head->data), stoi(head->next->data), current->data[0]));
                head = head->next;
                cout << "Operation: ";
                cout << current->data << "\n";
            }
        }
        current = current->next;
        cout << "Stack result: ";
        printStack(head);
        cout << "\n";
    }
    cout << "Final Result: ";
    cout << head->data;
}

void calculateReversePolishNot(Stack*& current)
{
    Stack* digit = nullptr, * head = nullptr;

    while (current != nullptr)
    {
        if (!isOperation(current->data[0]))
        {
            if (current->data != "")
            {
                digit = new Stack;
                digit->next = head;
                digit->data = current->data;
                head = digit;
            }
        }
        else
        {
            if (head->next == nullptr) {
                cout << "Input Erorr!";
                return;
            }
            else
            {
                head->next->data = to_string(doMathOps(stoi(head->next->data), stoi(head->data), current->data[0]));
                head = head->next;
                cout << "Operation: ";
                cout << current->data << "\n";
            }
        }
        current = current->next;
        cout << "Stack result: ";
        printStack(head);
        cout << "\n";
    }
    cout << "Final Result: ";
    cout << head->data;
}


void menu()
{
    Stack* stack1 = new Stack;
    string example;
    cout << "Enter an arithmetic expression: ";
    getline(cin, example);
    cout << "\n";
    int len = size(example);

    Stack* straight = straightPolNotation(len, example);
    cout << "\n\n";
    Stack* reverse = reversetPolNotation(len, example);


    cout << "\n";
    system("pause");
    cout << "\n\nStraight Polish Notation:\n\n";

    printStack(straight);
    calculatePolishNot(straight);
    cout << "\n\n";

    cout << "Reverse Polish Notation:\n\n";

    printStack(reverse);
    calculateReversePolishNot(reverse);
    cout << "\n\n";
}

int main()
{
    menu();

    return 0;
}

