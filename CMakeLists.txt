cmake_minimum_required(VERSION 3.2)
project(bgCore)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories("external/include")

find_package(Boost 1.58.0 REQUIRED)

if(Boost_FOUND)
    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
    message(STATUS "Boost_VERSION: ${Boost_VERSION}")

    include_directories(${Boost_INCLUDE_DIRS})
else()
    message(STATUS "Boost library not found")
endif()

configure_file(rules/hive.rules rules/hive.rules COPYONLY)

set(SOURCE_FILES main.cpp)
add_executable(bgCore ${SOURCE_FILES} player/Player.cpp player/Player.h Game.cpp Game.h ConfigManager.cpp ConfigManager.h BitsManager.cpp BitsManager.h gameBits/GameBit.cpp gameBits/GameBit.h gameBits/PieceSet.cpp gameBits/PieceSet.h gameBits/Piece.cpp gameBits/Piece.h gameBits/boards/HexBoard.cpp gameBits/boards/HexBoard.h turns/TurnsManager.cpp turns/TurnsManager.h tui/GameTUI.cpp tui/GameTUI.h player/PlayerInterface.cpp player/PlayerInterface.h turns/Turn.cpp turns/Turn.h turns/Action.cpp turns/Action.h player/PlayerController.cpp player/PlayerController.h tui/PlayerTUI.cpp tui/PlayerTUI.h GameController.cpp GameController.h turns/PutPieceOnBoard.cpp turns/PutPieceOnBoard.h gameBits/boards/Board.cpp gameBits/boards/Board.h gameBits/BitReference.cpp gameBits/BitReference.h turns/MultiActions.cpp turns/MultiActions.h turns/options/ActionOption.cpp turns/options/ActionOption.h turns/options/Option.cpp turns/options/Option.h turns/ChoosePiece.cpp turns/ChoosePiece.h turns/options/BitOption.cpp turns/options/BitOption.h turns/MoveBitTo.cpp turns/MoveBitTo.h gameBits/BitHolder.cpp gameBits/BitHolder.h)

if(Boost_FOUND)
    target_link_libraries(bgCore ${Boost_LIBRARIES})
endif()