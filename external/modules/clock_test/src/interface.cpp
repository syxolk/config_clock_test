#include "clock_test.h"

extern "C" {

void* getInstance() {
	return new ClockTest();
}

}
