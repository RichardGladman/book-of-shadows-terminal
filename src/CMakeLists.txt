find_package(ansicodes REQUIRED)
find_package(SQLite3 REQUIRED)

add_executable(bookofshadows 
    main.cpp
    model/baseentity.cpp model/colour.cpp model/polarity.cpp model/god.cpp model/herb.cpp
    model/planet.cpp model/tree.cpp model/zodiac.cpp model/runestone.cpp model/tarotcard.cpp
    menu/menu.cpp menu/option.cpp
    controllers/colourcontroller.cpp controllers/godcontroller.cpp controllers/herbcontroller.cpp
    controllers/polaritycontroller.cpp controllers/planetcontroller.cpp controllers/treecontroller.cpp
    controllers/zodiaccontroller.cpp controllers/runestonecontroller.cpp controllers/tarotcontroller.cpp
    controllers/correspondancecontroller.cpp
    database/database.cpp database/sqldata.cpp
    view/input.cpp view/view.cpp
)

target_include_directories(bookofshadows PUBLIC ${CMAKE_SOURCE_DIR}/include /usr/local/include/ansicodes)
target_link_libraries(bookofshadows PRIVATE ansicodes::ansicodes_lib PRIVATE ${SQLite3_LIBRARIES})
