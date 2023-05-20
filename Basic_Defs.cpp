#include "Basic_Defs.h"
#include "GUI.h"
using namespace std;
using namespace defs;
defs::Vector2::Vector2(float x_, float y_) {
		this->x = x_;
		this->y = y_;
}defs::Vector2::Vector2() {
		this->x = 0;
		this->y = 0;
}
void defs::Vector2::Normailze() {
	float f=sqrt(this->x * this->x + this->y * this->y);
	this->x /= f;
	this->y /= f;
}
float defs::Vector2::value() {
	return sqrt(this->x * this->x + this->y * this->y);
}
float defs::Vector2::angle() {
	return atan2(this->y, this->x);
}
defs::Vector2 defs::Vector2::operator-(const Vector2 &other) const {
		return Vector2(this->x - other.x, this->y - other.y);
}
defs::Vector2 defs::Vector2::operator+(const Vector2 &other) const {
		return Vector2(this->x + other.x, this->y + other.y);
}
defs::Vector2 defs::Vector2::operator*(const Vector2 &other) const {
		return Vector2(this->x * other.x, this->y * other.y);//nu intreba de ce
}
defs::Vector2 defs::Vector2::operator*(const int &other) const {
		return Vector2(this->x * other, this->y * other);
}
defs::Vector2 defs::Vector2::operator*(const float &other) const {
		return Vector2(this->x * other, this->y * other);
}
std::ostream& operator<<(std::ostream& stream, const Vector2& other) {
	stream << other.x << " " << other.y;
	return stream;
}

bool defs::Vector2::operator!=(const Vector2& other) const {
	return (this->x != other.x)||(this->x !=other.y);
}
void defs::Entity::Draw() {
	Draw_ent(this);
}
defs::Entity::Entity(){
	this->pos = Vector2(rand() % 10000+50000, rand() % 10000+50000);
	this->speed = Vector2(rand() % 100-50, rand() % 100-50);
	this->pos = this->pos * 0.01f;
	this->speed = this->speed * 1.0f;
}
defs::Particle::Particle() {
	this->pos = Vector2(rand() % 10000 + 50000, rand() % 10000 + 50000);
	this->speed = Vector2(rand() % 100 - 50, rand() % 100 - 50);
	this->pos = this->pos * 0.01f;
	this->speed = this->speed * 1.0f;
	this->bucket = Vector2(-1,-1);
	this->bucket_pos = -1;
}
void defs::Entity::Update() {
	//empty
}
void defs::Piston::Update() {
	this->speed.x = 0;
	if (this->speed.y > 100)this->speed.y = 100;
	if (this->speed.y < -100)this->speed.y = -100;
	if (this->size.y == -1)this->size.y = this->pos2.y - this->pos.y;
	if (this->speed.y != this->speed.y) this->speed.y = 0;
	this->pos = this->pos + this->speed * 0.1f;
	this->pos2 = this->pos2 + this->speed * 0.1f;
	if(this->pos.y > this->max_u) {
		this->pos.y=max_u;
		this->pos2.y= max_u + this->size.y;
		this->speed = Vector2(0,0);
	}
	if(this->pos.y < this->max_d) {
		this->pos.y = max_d;
		this->pos2.y = max_d + this->size.y;
		this->speed = Vector2(0,0);
	}
}
void defs::Particle::Update() {
	if (this->speed.x >  100)this->speed.x = 100;
	if (this->speed.x < -100)this->speed.x = -100;
	if (this->speed.y >  100)this->speed.y = 100;
	if (this->speed.y < -100)this->speed.y = -100;
	this->pos = this->pos + this->speed * 0.1f;
	while (this->pos.x < 0)this->pos.x += 1920;
	while (this->pos.x > 1920)this->pos.x -= 1920;
	while (this->pos.y < 0)this->pos.y += 1080;
	while (this->pos.y >1080)this->pos.y -= 1080;
	//phisycs
}
void defs::Area::Update() {
	//
}
float defs::Dist(Vector2 a, Vector2 b) {
	float rasp = 0;
	rasp = (a.x - b.x)* (a.x - b.x) +(a.y-b.y)* (a.y - b.y);
	//rasp = sqrt(rasp);
	return rasp;
}

defs::Event::Event(EventType evt,int ID, int Rate, Vector2 Intensity_2D) {
	this->rate = Rate;
	this->rate_left = 0;
	this->intensity_2D = Intensity_2D;
	this->type = evt;
	this->ID = ID;
}

bool defs::Area::Contains(Vector2 pos) {
	if (pos.x < this->pos.x) return false;
	if (pos.y < this->pos.y) return false;
	if (pos.x > this->pos2.x) return false;
	if (pos.y > this->pos2.y) return false;
	return true;
}