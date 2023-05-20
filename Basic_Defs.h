#pragma once
#include "libs.h"
namespace defs {


	class Vector2 {
	public:
		float x;
		float y;
		Vector2();
		Vector2(float x_, float y_);
		Vector2 operator+(const Vector2& other) const;
		Vector2 operator-(const Vector2& other) const;
		Vector2 operator*(const Vector2& other) const;
		bool operator!=(const Vector2& other) const;
		Vector2 operator*(const int& other) const;
		Vector2 operator*(const float& other) const;
		void Normailze();
		float angle();
		float value();
	};
	std::ostream& operator<<(std::ostream& stream, const Vector2& other);
	enum entity_type {
		Undefined_Particle_, Particle_, Block_ , Area_ , Piston_ , Poarta_
	};
	enum EventType {
		Ev_Heat , Ev_FanA , Ev_FanB , Ev_Spawn , Ev_Delete , Ev_Piston_Push , Ev_Toggle_Gate , Ev_Piston_Lock
	};
	class Event {
	public:
		Event(EventType evt, int ID,int Rate, Vector2 Intensity_2D);
		EventType type;
		int ID;
		int rate;
		int rate_left;//private
		Vector2 intensity_2D;
		void fire();
	};
	class Entity {
	public:
		Entity();
		Vector2 pos;
		Vector2 size = Vector2(-1,-1);
		Vector2 pos2;
		Vector2 speed;
		int ID;
		entity_type GetType;
		virtual void Update();
		void Draw();
	};
	class Particle :public Entity {
	public:
		Particle();
		Vector2 bucket;
		int bucket_pos;
		void Update();
	};
	class Block :public Entity {
	public:
		bool IsActive = true;
	};
	class Piston :public Entity {
	public:
		void Update();
		float max_u;
		float max_d;
		bool locked = false;
	};
	class Area :public Entity {
	public:
		void Update();
		bool Contains(Vector2 pos);
		
	};
	float Dist(Vector2 a, Vector2 b);
}