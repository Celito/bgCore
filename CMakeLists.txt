cmake_minimum_required(VERSION 3.2)
project(bgCore)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories("external/include")

configure_file(rules/hive.rules rules/hive.rules COPYONLY)

set(SOURCE_FILES main.cpp)
add_executable(bgCore ${SOURCE_FILES} player/Player.cpp player/Player.h Game.cpp Game.h ConfigManager.cpp ConfigManager.h BitsManager.cpp BitsManager.h gameBits/GameBit.cpp gameBits/GameBit.h gameBits/PieceSet.cpp gameBits/PieceSet.h gameBits/Piece.cpp gameBits/Piece.h gameBits/boards/HexBoard.cpp gameBits/boards/HexBoard.h turns/TurnsManager.cpp turns/TurnsManager.h tui/GameTUI.cpp tui/GameTUI.h player/PlayerInterface.cpp player/PlayerInterface.h turns/Turn.cpp turns/Turn.h turns/Action.cpp turns/Action.h player/PlayerController.cpp player/PlayerController.h tui/PlayerTUI.cpp tui/PlayerTUI.h GameController.cpp GameController.h turns/PutPieceOnBoard.cpp turns/PutPieceOnBoard.h gameBits/boards/Board.cpp gameBits/boards/Board.h gameBits/BitReference.cpp gameBits/BitReference.h turns/MultiActions.cpp turns/MultiActions.h turns/ActionOption.cpp turns/ActionOption.h)