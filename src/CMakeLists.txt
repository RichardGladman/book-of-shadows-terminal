find_package(ansicodes REQUIRED)
find_package(SQLite3 REQUIRED)

add_executable(bookofshadows main.cpp
    ../include/model/baseentity.h model/baseentity.cpp
    ../include/model/colour.h model/colour.cpp
    ../include/model/polarity.h model/polarity.cpp
    ../include/model/god.h model/god.cpp
    ../include/model/herb.h model/herb.cpp
    ../include/model/planet.h model/planet.cpp
    ../include/model/tree.h model/tree.cpp
    ../include/model/zodiac.h model/zodiac.cpp
    ../include/model/runestone.h model/runestone.cpp
    ../include/model/tarotcard.h model/tarotcard.cpp
    ../include/menu/menu.h menu/menu.cpp
    ../include/menu/option.h menu/option.cpp
    ../include/controllers/colourcontroller.h controllers/colourcontroller.cpp
    ../include/controllers/godcontroller.h controllers/godcontroller.cpp
    ../include/controllers/herbcontroller.h controllers/herbcontroller.cpp
    ../include/controllers/polaritycontroller.h controllers/polaritycontroller.cpp
    ../include/database/database.h database/database.cpp
    ../include/database/sqldata.h database/sqldata.cpp
    ../include/view/input.h view/input.cpp
    ../include/view/view.h view/view.cpp
    ../include/controllers/planetcontroller.h controllers/planetcontroller.cpp
    ../include/controllers/treecontroller.h controllers/treecontroller.cpp
    ../include/controllers/zodiaccontroller.h controllers/zodiaccontroller.cpp
    ../include/controllers/runestonecontroller.h controllers/runestonecontroller.cpp)

target_include_directories(bookofshadows PUBLIC 
          $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
          $<BUILD_INTERFACE:/usr/local/include/ansicodes>
)

target_link_libraries(bookofshadows PRIVATE ansicodes::ansicodes_lib PRIVATE ${SQLite3_LIBRARIES})
