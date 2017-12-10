#ifndef __macros_hpp
#define __macros_hpp

#include <iostream> // due to macros which print log to std::cout

// macros for class Data
#define LOAD(data) while(data->refresh() != true);
#define SIZE(data) data->size();
#define DEBUG(data) data->debug();
#define DEBUG_METHOD_RESULT(data,method) { \
	for (unsigned int i = 0; i < data->size(); i++) { \
		std::cout << data->method(i) << std::endl; \
	} \
}

// printing utilities
#define PRINT_VEC(vector) for (auto i = vector.begin(); i != vector.end(); ++i) std::cout << *i << std::endl;
#define PRINT(data) std::cout << data << std::endl;
#define ECHO() std::cout << std::endl;

#endif
