#include <iostream>
#include <cstdint>
#include <limits>

int64_t sum_nat(uint64_t upperLimit) {
  uint64_t res = 0;

  for (uint64_t i = 0; i < upperLimit; ++i) {
    if (i % 3 == 0 && i % 5 != 0) {
      res += i;
    }

    if (i % 5 == 0 && i % 3 != 0) {
      res += i;
    }

    if (i >= std::numeric_limits<int64_t>::max()) {
      return -1;
    }
  }

  return res;
}

int main(int argc, char** argv) {
  using namespace std;

  int upperLimit = 5;
  cout << "Upper limit: ";
  cin >> upperLimit;

  int64_t result = sum_nat(upperLimit);
  if (result != -1) {
    cout << "Result = " << result << endl;
  } else {
    cout << "There was an error." << endl;
  }

  return 0;
}
