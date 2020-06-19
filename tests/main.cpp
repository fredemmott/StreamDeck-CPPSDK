// @copyright  (c) 2020, Frederick Emmott
// This source code is licensed under the MIT-style license found in
// the LICENSE file.

#include <iostream>
using namespace std;

bool test_main();

int main(int argc, char** argv) {
  if (test_main()) {
    cout << "Test passed." << endl;
    return 0;
  }
  cout << "Test failed." << endl;
  return 1;
}
