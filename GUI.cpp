#include "GUI.h"
using namespace cv;
using namespace std;
using namespace defs;
Mat3b screen;
pair<float, float> v[2190][3030];
string name = "Simulatie";
string MapMode = "default";
int heigth = 1080;
int width = 1920;

vector <Vec3b> cols;
void add_rand_col() {
	cols.push_back(Vec3b(rand() % 156, rand() % 156, rand() % 156));
}

void SetMap(string mode) {
	MapMode = mode;
}
int clamp(float x) {
	if (x < 0)return 0;
	if (x > 255) return 255;
	return (int)x;
}
void Draw_ent(Entity *entity) {
	if (MapMode == "temp") {
		float f= abs(entity->speed.x)  + abs(entity->speed.y) ;
		for (int ii = max(0,(int)entity->pos.y-20); ii <= min((int)entity->pos.y+20,1080); ii++) {
			for (int jj = max(0,(int)entity->pos.x-20); jj <= min(1920,(int)entity->pos.x+20); jj++) {
				v[ii][jj].first += f;
				v[ii][jj].second++;
			}
		}
		return;
	}
	entity_type t = entity->GetType;
	if (t == Undefined_Particle_)cout << "error";
	switch (t)
	{
	case Particle_: {
		
		circle(screen, Point(entity->pos.x,entity->pos.y), 1, Scalar(255-clamp(abs(entity->speed.x)+abs(entity->speed.y))/3, 255, 255), 1, 8, 0);
		
		break;
	}
	case Block_: {
		
		rectangle(screen, Point(entity->pos.x, entity->pos.y), Point(entity->pos2.x, entity->pos2.y), Scalar(225, 225, 225), FILLED, 8, 0);
		
		break;
	}
	case Piston_: {

		rectangle(screen, Point(entity->pos.x, entity->pos.y), Point(entity->pos2.x, entity->pos2.y), Scalar(255, 0, 0), FILLED, 8, 0);

		break;
	}
	case Area_: {
		if (MapMode == "build") {
			int cn = screen.channels();
			for (int ii = (int)entity->pos.y; ii <= (int)entity->pos2.y; ii++) {
				for (int jj = (int)entity->pos.x; jj <= (int)entity->pos2.x; jj++) {
					Scalar_<uint8_t> bgrPixel;
					int B = screen.data[ii * width * cn + jj * cn + 0]; // B
					int G = screen.data[ii * width * cn + jj * cn + 1]; // G
					int R = screen.data[ii * width * cn + jj * cn + 2]; // R
					while(cols.size() < entity->ID) {
						add_rand_col();
					}
					B = B / 2 + cols[entity->ID][0] / 2;
					G = G / 2 + cols[entity->ID][1] / 2;
					R = R / 2 + cols[entity->ID][2] / 2;
					screen.data[ii * width * cn + jj * cn + 0] = B; // B
					screen.data[ii * width * cn + jj * cn + 1] = G; // G
					screen.data[ii * width * cn + jj * cn + 2] = R; // R
				}
			}
		}
		break;
	}
	default:
		break;
	}
}
int abl_await;
Block abl;
void Sync(int b_a , Block b_l) {
	abl_await = b_a;
	abl = b_l;
}
void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
	if (event == EVENT_LBUTTONDOWN)
	{
		switch (abl_await) {
		case 1: {
			abl.pos = Vector2(x, y); Sync2(abl_await, abl); break;
		}case 2: {
			abl.pos2 = Vector2(x, y); Sync2(abl_await, abl); break;
		}
		default: {
			break;
		}
		}
	
	}
}
void gui_start() {
	namedWindow(name, WINDOW_AUTOSIZE);
	setMouseCallback(name, CallBackFunc, NULL);
	screen = Mat3b(heigth, width, Vec3b(0, 0, 0));
}
void gui_update() {
	if (MapMode == "temp") {
		int cn = screen.channels();
		for (int i = 0; i < 1080; i++) {
			for (int j = 0; j < 1920; j++) {
				int B, G, R;
				int val = 0;
				if(v[i][j].second!=0)val = v[i][j].first / v[i][j].second;
				B = G = R = val;
				
				screen.data[i * width * cn + j * cn + 0] = B; // B
				screen.data[i * width * cn + j * cn + 1] = G; // G
				screen.data[i * width * cn + j * cn + 2] = R; // R
			}
		}
	}
	imshow(name,screen);
	screen = Mat3b(heigth, width, Vec3b(0, 0, 0));
	if (MapMode == "temp") {
		int cn = screen.channels();
		for (int i = 0; i <= 1080; i++) {
			for (int j = 0; j <= 1920; j++) {
				v[i][j].first = 0;
				v[i][j].second = 0;
			}
		}
	}
	waitKey(1);
	
}