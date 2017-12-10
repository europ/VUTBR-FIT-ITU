#include "analyser.hpp"
#include "macros.hpp"

int main(int argc, char* argv[]) {

    (void)argc; // -Wunused-parameter
    (void)argv; // -Wunused-parameter

    Data* d = new Data();

    LOAD(d); // load data

    //DEBUG(d);

    DEBUG_METHOD_RESULT(d,get_SECURITY);

    return 0;
}
