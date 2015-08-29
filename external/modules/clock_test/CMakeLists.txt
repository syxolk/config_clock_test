set(SOURCES
	"src/clock_test.cpp"
	"src/interface.cpp"
)

set(HEADERS
	"include/clock_test.h"
)

include_directories(include)

add_library(clock_test MODULE ${SOURCES} ${HEADERS})
target_link_libraries(clock_test PRIVATE lmscore)
