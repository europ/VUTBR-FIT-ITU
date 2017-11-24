#include "analyser.hpp"

#define LOAD(d) while(d->refresh() != true);
#define DEBUG(d) d->DEBUG();

int main(int argc, char* argv[]) {

	Data* d = new Data();

	LOAD(d); // load data

	DEBUG(d); // print info

	return 0;
}

