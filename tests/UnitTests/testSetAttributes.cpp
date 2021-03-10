#include "catch.hpp"
#include "../../src/RecipeAI.h"
#include <iostream>

// Convenience function for comparing structures during testing
bool operator==(const attributes &lhs, const attributes &rhs)
{
   return (lhs.tankHealth == rhs.tankHealth &&
           lhs.tankDamage == rhs.tankDamage &&
           lhs.tankAP == rhs.tankAP &&
           lhs.tankShots == rhs.tankShots &&
           lhs.tankAmmo == rhs.tankAmmo &&
           lhs.tankRadar == rhs.tankRadar &&
           lhs.tankRange == rhs.tankRange);
}

// Convenience function that allows catch++ to print out the attributes struct
ostream& operator<<(ostream &os, const attributes &attr)
{
   os << "Health: " << attr.tankHealth << " " <<
         "Damage: " << attr.tankDamage << " " <<
         "AP    : " << attr.tankAP << " " <<
         "Shots : " << attr.tankShots  << " " <<
         "Ammo  : " << attr.tankAmmo   << " " <<
         "Radar : " << attr.tankRadar << " " <<
         "Range : " << attr.tankRange  ;
   return os;
}

// Simple first test
TEST_CASE("Can I create a RecipeAI tank?")
{
   RecipeAI recipeai;
}

// If we send no special points, do we get the same base stats back?
TEST_CASE("SetAttribute does not change stats when called with 0 pointsAvailable")
{
   RecipeAI recipeai;
   attributes expected;

   attributes actual = recipeai.setAttribute(0, expected);

   REQUIRE(actual == expected);
}

// Any points should be allocated to radar range
TEST_CASE("SetAttribute assigns points available and returns offset")
{
   RecipeAI recipeai;
   attributes baseStats(1,2,3,4,5,5,7);
   attributes expected = {
      {0}, // Health
      {0}, // Damage
      {0}, // AP
      {0}, // Shots
      {0}, // Ammo
      {1}, // Radar
      {0}  // Range
   };

   attributes actual = recipeai.setAttribute(1, baseStats);

   REQUIRE(actual == expected);
}
