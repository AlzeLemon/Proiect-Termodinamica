#pragma once
#include "libs.h"
#include "Basic_Defs.h"
using namespace defs;
void Draw_ent(Entity *entity);
void gui_update();
void gui_start();
void Sync(int b_a, Block b_l);
void Sync2(int b_a, Block b_l);
void add_rand_col();
void SetMap(std::string mode);