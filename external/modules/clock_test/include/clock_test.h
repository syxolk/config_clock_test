#ifndef CLOCK_TEST_H
#define CLOCK_TEST_H

#include "lms/module.h"
#include "lms/extra/time.h"
#include "lms/type/module_config.h"

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
    lms::extra::PrecisionTime lastCycle;
    lms::extra::PrecisionTime sumDiff;

    const lms::type::ModuleConfig *config;
    lms::extra::PrecisionTime configuredCycleTime;
};

#endif /* CLOCK_TEST_H */
