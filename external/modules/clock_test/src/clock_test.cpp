#include "clock_test.h"

bool ClockTest::initialize() {
    firstCycle = true;

    std::string unit = config().get<std::string>("unit", "hz");
    if(unit == "hz") {
        configuredCycleTime = lms::Time::fromMicros(1000000 /
            config().get<int>("value"));
    } else if(unit == "ms") {
        configuredCycleTime = lms::Time::fromMillis(
            config().get<int>("value"));
    } else if(unit == "us") {
        configuredCycleTime = lms::Time::fromMicros(
            config().get<int>("value"));
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
    using lms::Time;

    if(firstCycle) {
        startupTimestamp = Time::now();
        cycleCount = 0;
    } else {
        cycleCount ++;
        logger.info() << (Time::now() - startupTimestamp) / cycleCount;
        logger.info() << (Time::now() - startupTimestamp - configuredCycleTime * cycleCount);
        logger.info() << cycleCount;
    }

    if(! firstCycle) {
        Time now = Time::now();
        Time realCycleTime = now - lastCycle;
        Time currentDiff = realCycleTime - configuredCycleTime;
        sumDiff += currentDiff;

        logger.info("realCycle") << realCycleTime << " " << currentDiff
                                 << " " << sumDiff;
    }

    lastCycle = Time::now();
    firstCycle = false;

    //PrecisionTime::fromMillis(9).sleep();

    return true;
}
