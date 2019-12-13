#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "server.h"


int main()
{
    Server server;
    server.start();
    return 0;
}
