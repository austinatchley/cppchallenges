#include <iostream>
#include <iterator>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <cctype>
#include <cstring>
#include <vector>

template <typename C, typename... Args>
void push_range(C &c, Args &&... args)
{
    (c.push_back(args), ...);
}

int main()
{
    using namespace std;

    string input;
    vector<int> vec;

    push_range(vec, 1);
    push_range(vec, 1, 2);
    push_range(vec, 1, 2, 3);

    cout << "Output = ";
    copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " "));

    cout << endl;
    system("pause");
}