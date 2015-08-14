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
add_executable(bgCore ${SOURCE_FILES} player/Player.cpp player/Player.h Game.cpp Game.h ConfigManager.cpp ConfigManager.h BitsManager.cpp BitsManager.h gameBits/GameBit.cpp gameBits/GameBit.h gameBits/PieceSet.cpp gameBits/PieceSet.h gameBits/Piece.cpp gameBits/Piece.h gameBits/boards/HexBoard.cpp gameBits/boards/HexBoard.h turns/TurnsManager.cpp turns/TurnsManager.h tui/GameTUI.cpp tui/GameTUI.h player/PlayerInterface.cpp player/PlayerInterface.h turns/TurnDef.cpp turns/TurnDef.h turns/actions/ActionDef.cpp turns/actions/ActionDef.h player/PlayerController.cpp player/PlayerController.h tui/PlayerTUI.cpp tui/PlayerTUI.h GameController.cpp GameController.h turns/actions/PutPieceOnBoard.cpp turns/actions/PutPieceOnBoard.h gameBits/boards/Board.cpp gameBits/boards/Board.h gameBits/BitReference.cpp gameBits/BitReference.h turns/actions/MultiActions.cpp turns/actions/MultiActions.h turns/actions/options/ActionOption.cpp turns/actions/options/ActionOption.h turns/actions/options/Option.cpp turns/actions/options/Option.h turns/actions/ChoosePieceOnSet.cpp turns/actions/ChoosePieceOnSet.h turns/actions/options/BitOption.cpp turns/actions/options/BitOption.h turns/actions/ChooseTileOnBoard.cpp turns/actions/ChooseTileOnBoard.h gameBits/boards/Tile.cpp gameBits/boards/Tile.h gameBits/boards/TilePos.cpp gameBits/boards/TilePos.h turns/actions/options/TileOption.cpp turns/actions/options/TileOption.h rules/Rule.cpp rules/Rule.h gameBits/attributes/Attribute.cpp gameBits/attributes/Attribute.h gameBits/attributes/AttrManager.cpp gameBits/attributes/AttrManager.h turns/actions/MovePieceOnBoard.cpp turns/actions/MovePieceOnBoard.h turns/actions/ChoosePieceOnBoard.cpp turns/actions/ChoosePieceOnBoard.h rules/PlayerAttrComparison.cpp rules/PlayerAttrComparison.h rules/MovementFilterRule.cpp rules/MovementFilterRule.h turns/Turn.cpp turns/Turn.h turns/actions/Action.cpp turns/actions/Action.h rules/TestableRule.cpp rules/TestableRule.h rules/TouchAnotherPieceRule.cpp rules/TouchAnotherPieceRule.h rules/RulesManager.cpp rules/RulesManager.h turns/State.cpp turns/State.h rules/IsEmpty.cpp rules/IsEmpty.h rules/TimedCondition.cpp rules/TimedCondition.h rules/IsRound.cpp rules/IsRound.h)

if(Boost_FOUND)
    target_link_libraries(bgCore ${Boost_LIBRARIES})
endif()