#include <iostream>
#include <memory>

#include "TTask1.h"
//-------------------------------------------------------------------------------

using namespace std;
//-------------------------------------------------------------------------------

int main(int argc, char** argv)
{
  cerr << endl << "Task1 has started..." << endl << endl;

  unique_ptr<TTask1> Task1( new TTask1() );   // can be used starting from C++11
  //auto Task1 = make_unique<TTask1>();       // can be used starting from C++14

  Task1->Run();

  cerr << endl << "Task1 has finished successfully." << endl << endl;
}
//-------------------------------------------------------------------------------
