#include "catch.hpp"
#include "../../src/RecipeAI.h"
#include <iostream>
#include <algorithm>
#include "defines.h"

/*
//hard, recentVisited (in spendAP)
bool RecipeAI::isStuck()
//hard, visitedAtLeastOnce, countAdjacentIndices
int RecipeAI::countAdjacentUnknownNodes( int index, int mapWidth, int mapHeight)
//easy however, needs friend class to see info
void RecipeAI::genFullMap ( MapData map )
//easy
direction RecipeAI::convertCoordinatesToDirection(pair<int,int> targetLocation, pair<int,int>currentLocation)
//hard, visitedAtLeastOnce, validMove, countAdjacentUnknownNodes
int RecipeAI::getTargetIndex(vector<int> adjacentIndices, MapData &map, int index)
//easy
vector<int> RecipeAI::getAdjacentIndices(int baseIndex, int mapWidth, int mapHeight)
//medium, fullMap
bool RecipeAI::checkNeighbouringCells ( int x, int y, MapData map, PositionData status )
//hard, checkNeighboringCells, isStuck
bool RecipeAI::getDir(direction dir, int &minDist, MapData map, PositionData status, int x, int y, direction &ret)
//medium, safeMap, however, needs friend class to see info
void RecipeAI :: markCrates(int x, int y, MapData map)
//easy, myStats, however, needs friend class to see info
void RecipeAI :: genSafeMap(int x_val, int y_val, MapData map)
	*/

//TEST_CASE("")
//{
//	RecipeAI recipeai;
//	MapData map(3,3);
//	map.map[2*(3)] = OpponentID;
//   PositionData status(MyID,MyHealth,MyXPos,MyYPos,1,1);
//   attributes baseStats(2,2,2,2,2,5,5);
//	recipeai.setAttribute(0, baseStats);
//
//	recipeai.genSafeMap(0,0,map);
//}

TEST_CASE("Testing the getAdjacentIndices function")
{
	RecipeAI recipeai;
	vector<int> expected = {0,1,2,4,6,8,9,10};
	vector<int> result = recipeai.getAdjacentIndices(5, 4, 4);
	sort(result.begin(), result.end());

	REQUIRE(result == expected);
}

TEST_CASE("Testing the convertCoordinatesToDirection function")
{
	RecipeAI recipeai;
	pair<int,int> current(0,0), target(1,1);
	direction move = recipeai.convertCoordinatesToDirection(target, current);

	REQUIRE( move == DOWNRIGHT);
}

TEST_CASE("Testing the checkNeighbouringCells function without enemy")
{
	RecipeAI recipeai;
	MapData map(3,3);
   PositionData status(MyID,MyHealth,MyXPos,MyYPos,1,1);
	bool result = recipeai.checkNeighbouringCells(0,0,map, status);

	REQUIRE(result == false);
}

TEST_CASE("Testing the checkNeighbouringCells function with enemy")
{
	RecipeAI recipeai;
	MapData map(3,3);
	map.map[1] = OpponentID;
   PositionData status(MyID,MyHealth,MyXPos,MyYPos,1,1);
	bool result = recipeai.checkNeighbouringCells(0,0,map, status);
	recipeai.genFullMap(map);

	REQUIRE(result == true);
}

TEST_CASE("Testing the isStuck function")
{
	RecipeAI recipeai;
	MapData map(3,3);
	for(int i=0; i<13; i++)
	{
		PositionData status(MyID,MyHealth,MyXPos,i%2,1,1);
		recipeai.spendAP(map, status);
	}

	REQUIRE(recipeai.isStuck() == true);
}
