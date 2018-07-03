#include <iostream>

int main()
{
    using namespace std;
    unsigned int limit = 0;
    cout << "Upper limit:";
    cin >> limit;

    unsigned long long sum = 0;
    for (unsigned int i = 3; i < limit; ++i)
    {
        if (i % 3 == 0 || i % 5 == 0)
            sum += i;
    }
    cout << "sum = " << sum << endl;
    cin >> limit;
}