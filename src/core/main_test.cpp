#include "TileMap.h"
#include "DungeonGenerator.h"
#include <iostream>
using namespace std;

int main()
{

  TileMap* tm = new TileMap();
  tm->regressionTest();
  delete tm;

  DungeonGenerator d;
  d.regressionTest();

  return 0;
}