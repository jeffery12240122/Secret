#include <iostream>
#include <string>
#include "Tool/tools.h"

int main() {
    shared_ptr<tools> tool = make_shared<tools>();
    int A = 5;
    cout<<tool->params(A)<<endl;
}
