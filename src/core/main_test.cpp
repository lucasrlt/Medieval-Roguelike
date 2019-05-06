#include "TileMap.h"
#include "DungeonGenerator.h"
#include "Button.h"
#include "Entity.h"
#include "Projectile.h"
#include <iostream>
using namespace std;

int main()
{

  TileMap* tm = new TileMap();
  tm->regressionTest();
  delete tm;

  DungeonGenerator d;
  d.regressionTest();

  Button b;
  b.regressionTest();

  Entity e;
  e.regressionTest();

  Projectile p;
  p.regressionTest();

  Vector2D v;
  v.regressionTest();

  return 0;
}