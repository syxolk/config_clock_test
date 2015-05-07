#include "clock_test.h"

bool ClockTest::initialize() {
    firstCycle = true;
    config = getConfig();

    std::string unit = config->get<std::string>("unit", "hz");
    if(unit == "hz") {
        configuredCycleTime = lms::extra::PrecisionTime::fromMicros(1000000 /
            config->get<int>("value"));
    } else if(unit == "ms") {
        configuredCycleTime = lms::extra::PrecisionTime::fromMillis(
            config->get<int>("value"));
    } else if(unit == "us") {
        configuredCycleTime = lms::extra::PrecisionTime::fromMicros(
            config->get<int>("value"));
    } else {
        logger.error("init") << "Invalid unit " << unit;
        return false;
    }

    logger.debug("init") << "configured " << configuredCycleTime;

    return true;
}

bool ClockTest::deinitialize() {
    return true;
}

bool ClockTest::cycle() {
    using lms::extra::PrecisionTime;

    if(! firstCycle) {
        PrecisionTime now = PrecisionTime::now();
        PrecisionTime realCycleTime = now - lastCycle;
        PrecisionTime currentDiff = realCycleTime - configuredCycleTime;
        sumDiff += currentDiff;

        logger.info("realCycle") << realCycleTime << " " << currentDiff
                                 << " " << sumDiff;
    }

    lastCycle = PrecisionTime::now();
    firstCycle = false;

    return true;
}
