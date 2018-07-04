#include <iostream>
#include <algorithm>
#include <numeric>
#include <cctype>
#include <cstring>

std::string fn(const std::string &input)
{
    return "";
}

int main()
{
    using namespace std;

    string input;
    string prompt = "";

    cout << prompt;
    cin >> input;

    auto output = fn(input);

    cout << "Output = " << output << endl;
    system("pause");
}