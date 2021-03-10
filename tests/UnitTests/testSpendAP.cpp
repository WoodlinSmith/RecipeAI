#include "catch.hpp"
#include "../../src/RecipeAI.h"
#include <iostream>
#include "defines.h"

// A map empty of opponents results in the recipeai being idle
TEST_CASE("If no threats detected, SpendAP should return 1")
{
   RecipeAI recipeai;
   MapData map(MapSizeX,MapSizeY);
   PositionData status;
   attributes baseStats(2,2,2,2,2,5,5);
	recipeai.setAttribute(0, baseStats);

   REQUIRE(recipeai.spendAP(map, status) == 1);
}

// Threats mean that we should try to spend AP on attacking.  If no
// threat is hitable, the recipeai will not fire
TEST_CASE("If threats detected, SpendAP should return 2")
{
   RecipeAI recipeai;
   MapData map(MapSizeX,MapSizeY);
   map.map[MapSizeX*(MapSizeY-1)+MapSizeX-1] = OpponentID;
   PositionData status(MyID,MyHealth,MyXPos,MyYPos,1,1);
   attributes baseStats(2,2,2,2,2,5,5);
	recipeai.setAttribute(0, baseStats);

   REQUIRE(recipeai.spendAP(map, status) == 2);
}

TEST_CASE("If threats detected and in safemode, SpendAP should return 3")
{
   RecipeAI recipeai;
   MapData map(MapSizeX,MapSizeY);
   map.map[MapSizeX*(MapSizeY-1)+MapSizeX-2] = OpponentID;
   PositionData status(MyID,MyHealth,MyXPos,MyYPos,1,1);
   attributes baseStats(1,1,1,1,1,5,5);
	recipeai.setAttribute(0, baseStats);

   REQUIRE(recipeai.spendAP(map, status) == 3);
}
