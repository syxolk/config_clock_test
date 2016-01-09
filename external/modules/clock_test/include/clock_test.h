#ifndef CLOCK_TEST_H
#define CLOCK_TEST_H

#include "lms/module.h"
#include "lms/time.h"
#include "lms/config.h"

/**
 * @brief This module tests the quality of the integrated LMS clock.
 */
class ClockTest : public lms::Module {
public:
    bool initialize() override;
    bool cycle() override;
    bool deinitialize() override;
private:
    bool firstCycle;
    lms::Time lastCycle;
    lms::Time sumDiff;

    lms::Time startupTimestamp;
    size_t cycleCount;

    lms::Time configuredCycleTime;
};

#endif /* CLOCK_TEST_H */
