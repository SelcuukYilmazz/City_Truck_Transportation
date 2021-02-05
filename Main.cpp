#include "operation.h"
#include <stdio.h>
#include <iostream>

using namespace std;
int main(int argc, char **argv)
{
    // Open file with freopen so all things will write on file

    freopen (argv[5],"w",stdout);
    Operation operation;

    // All operations here

    operation.operation_execute(argv[1],argv[2],argv[3],argv[4]);

    //Closing file

    fclose(stdout);
    return 0;
}
