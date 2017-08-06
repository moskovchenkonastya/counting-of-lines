#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main (int argc, char *argv[]) {


  if (argc != 2){

    cout <<"Data is not correct\n" << endl;
    return 1;
  }

  int count = 0;
  string line;

  ifstream myfile (argv[1]);

  if (myfile.is_open())
  {
    while ( myfile.good() )
    {
      getline (myfile,line);
      //cout << line << endl;
      ++count;
    }
    myfile.close();
  }

  else cout << "Unable to open file";

  cout << count << endl;

  return 0;
}


