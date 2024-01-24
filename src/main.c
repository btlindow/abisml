#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "abisml.h"

ABISML_STATE(start);
ABISML_STATE(middle);
ABISML_STATE(stop);

ABISML_EDGES
(
    edges,
    ABISML_EDGE(start, middle)
    ABISML_EDGE(middle, stop)
    ABISML_EDGE(stop, start)
)

ABISML_MACHINE(machine, start, edges)

int main(int argc, char **argv)
{
    ABISML_RUN(machine);
    return 0;
}

ABISML_ROUTINE(start)
{
    printf("in start\n");
    sleep(1);
    ABISML_TRANSITION(machine, middle);
}

ABISML_ROUTINE(middle)
{
    printf("in middle\n");
    sleep(1);
    ABISML_TRANSITION(machine, stop);
}

ABISML_ROUTINE(stop)
{
    printf("in stop\n");
    sleep(1);
    ABISML_TRANSITION(machine, start);
}