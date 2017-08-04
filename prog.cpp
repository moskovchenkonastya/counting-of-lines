#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>  

using namespace std;

int main(int argc, char *argv[]) {
    
    if (argc != 2){
       cout <<"Data is not correct\n" << endl;
       return 1;
    }
    
    FILE *stream = fopen(argv[1], "r");
	
	int ch, number_of_lines = 0;

    while ((ch = getc(stream)) != EOF)
        if (ch == '\n')
            ++number_of_lines;

    cout << number_of_lines<< endl;

   fclose(stream);

   return 0;
 

}

