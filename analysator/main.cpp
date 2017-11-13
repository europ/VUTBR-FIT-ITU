#include "analyser.hpp"

int main(int argc, char* argv[]) {

	Data* d = new Data();
	d->reset();

	while(d->refresh() != true) {
		d->reset();
	};

	d->DEBUG(); // print data

	return 0;
}