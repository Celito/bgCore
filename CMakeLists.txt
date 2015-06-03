cmake_minimum_required(VERSION 3.2)
project(bgCore)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories("external/include")

configure_file(rules/hive.rules rules/hive.rules COPYONLY)

set(SOURCE_FILES main.cpp)
add_executable(bgCore ${SOURCE_FILES} Player.cpp Player.h GameManager.cpp GameManager.h ConfigManager.cpp ConfigManager.h BitsManager.cpp BitsManager.h gameBits/GameBit.cpp gameBits/GameBit.h gameBits/PieceSet.cpp gameBits/PieceSet.h gameBits/Piece.cpp gameBits/Piece.h gameBits/boards/HexBoard.cpp gameBits/boards/HexBoard.h)