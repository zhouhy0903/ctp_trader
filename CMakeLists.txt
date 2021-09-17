CMAKE_MINIMUM_REQUIRED(VERSION 3.14)
PROJECT (test)
FILE(GLOB MD_SRC_LIST "${PROJECT_SOURCE_DIR}/src/*.cpp")


INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/src )


SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/target)
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/lib)


list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
find_package(MySQL REQUIRED)
include_directories(${MYSQL_INCLUDE_DIRS})


find_package(Threads)
# ADD_EXECUTABLE(test_checkposition src/test/test_checkposition.cpp)
ADD_EXECUTABLE(test_orderinsert src/test/test_orderinsert.cpp)
# ADD_EXECUTABLE(test_ordercheck src/test/test_ordercheck.cpp)
ADD_EXECUTABLE(position src/position/position.cpp)

ADD_EXECUTABLE(marketdata src/marketdata.cpp)
ADD_EXECUTABLE(getcontract src/tools/get_contract_id.cpp)
ADD_EXECUTABLE(realtime src/tools/realtime.cpp)
ADD_EXECUTABLE(data2csv src/tools/data2csv.cpp)


TARGET_LINK_LIBRARIES(realtime thostmduserapi_se ${MYSQL_LIBRARIES})

# TARGET_LINK_LIBRARIES(test_checkposition thostmduserapi_se thosttraderapi_se ${MYSQL_LIBRARIES})
TARGET_LINK_LIBRARIES(test_orderinsert thostmduserapi_se thosttraderapi_se ${MYSQL_LIBRARIES})
# TARGET_LINK_LIBRARIES(test_ordercheck thostmduserapi_se thosttraderapi_se ${MYSQL_LIBRARIES})

TARGET_LINK_LIBRARIES(marketdata thostmduserapi_se ${MYSQL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
TARGET_LINK_LIBRARIES(position thostmduserapi_se thosttraderapi_se ${MYSQL_LIBRARIES})
TARGET_LINK_LIBRARIES(getcontract thosttraderapi_se)
TARGET_LINK_LIBRARIES(data2csv ${MYSQL_LIBRARIES})
