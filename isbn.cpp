#include <iostream>
#include <algorithm>
#include <numeric>
#include <cctype>
#include <cstring>

std::string validate_isbn(const std::string& input)
{
    if (input.size() != 10 || std::count_if(input.begin(), input.end(), isdigit) != 10)
        return "Invalid";

    unsigned int w = 10;
    auto sum = std::accumulate(input.begin(), input.end(), 0,
        [&w] (int const total, char const c)
        {
            return total + (w-- * (c - '0'));
        });

    return !(sum % 11) ? "Valid" : "Invalid";
}

int main()
{
    using namespace std;

    string input;
    string prompt = "ISBN:";

    cout << prompt;
    cin >> input;

    auto output = validate_isbn(input);

    cout << "Output = " << output << endl;
    cin >> input;
}