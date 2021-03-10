#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../../src/direction.h"

std::ostream &operator<< ( std::ostream &out, direction const &dir )
{
    if(dir==UP)
    out<<"UP";
    if(dir==UPRIGHT)
    out<<"UPRIGHT";
    if(dir==RIGHT)
      out<<"RIGHT";
    if(dir==DOWNRIGHT)
      out<<"DOWNRIGHT";
    if(dir==DOWN)
      out<<"DOWN";
    if(dir==DOWNLEFT)
      out<<"DOWNLEFT";
    if(dir==LEFT)
      out<<"LEFT";
    if(dir==UPLEFT)
      out<<"UPLEFT";
    if(dir==STAY)
      out<<"STAY";

}
