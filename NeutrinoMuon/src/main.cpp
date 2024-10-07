#include <iostream>
#include <memory>

#include "TTask2.h"
//-------------------------------------------------------------------------------

using namespace std;
//-------------------------------------------------------------------------------

int main(int argc, char** argv)
{
  cerr << endl << "Task2 has been started..." << endl << endl;

  unique_ptr<TTask2> Task2( new TTask2() );   // can be used starting from C++11
  //auto Task2 = make_unique<TTask2>();       // can be used starting from C++14

  Task2->Run();

  cerr << endl << "Task2 has been finished." << endl << endl;
}
//-------------------------------------------------------------------------------
