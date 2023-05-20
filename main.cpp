#include "libs.h"
#include "GUI.h"
#include "Basic_Defs.h"
using namespace std;
using namespace defs;
vector <Particle*> entities;
vector <Block*> ziduri;
vector <Block*> porti;
vector <Piston*> pistoane;
vector <Area*> areas;
vector <Event*> events;
Block bl;
Vector2 v2;
int bl_await;
void _update() {
	//particule
	for (int it = 0; it < entities.size()-1; it++) {
		v2 = v2 + entities[it]->speed;
		for (int jt = it + 1; jt < entities.size(); jt++) {
			if (Dist(entities[it]->pos, entities[jt]->pos) <= 16) {
				float tetha = 0;
				Vector2 tang = entities[it]->pos - entities[jt]->pos;
				tang.Normailze();
				Vector2 rspeed = entities[it]->speed - entities[jt]->speed;
				Vector2 added = Vector2(0, 0) - entities[jt]->speed;
				tetha = tang.angle() - rspeed.angle();

				//tf is this????
				//entities[jt]->speed = tang * rspeed.value() * sin(tetha/2) - added;

				Vector2 normal = Vector2(-tang.y, tang.x);

				float kx = (entities[it]->speed.x - entities[jt]->speed.x);
				float ky = (entities[it]->speed.y - entities[jt]->speed.y);
				float p = (tang.x * kx + tang.y * ky);
				entities[it]->speed.x = entities[it]->speed.x - p * tang.x;
				entities[it]->speed.y = entities[it]->speed.y - p * tang.y;
				entities[jt]->speed.x = entities[jt]->speed.x + p * tang.x;
				entities[jt]->speed.y = entities[jt]->speed.y + p * tang.y;
			}

		}
	}
	//ziduri
	for (int it = 0; it < entities.size() - 1; it++) {
		v2 = v2 + entities[it]->speed;
		for (int jt = 0; jt < ziduri.size(); jt++) {
			if (!ziduri[jt]->IsActive)continue;
			if (entities[it]->pos.x <= ziduri[jt]->pos2.x && entities[it]->pos.x >= ziduri[jt]->pos.x && entities[it]->pos.y <= ziduri[jt]->pos2.y && entities[it]->pos.y >= ziduri[jt]->pos.y) {
				float dist[4];
				dist[0] = abs(entities[it]->pos.x - ziduri[jt]->pos.x);
				dist[1] = abs(entities[it]->pos.x - ziduri[jt]->pos2.x);
				dist[2] = abs(entities[it]->pos.y - ziduri[jt]->pos.y);
				dist[3] = abs(entities[it]->pos.y - ziduri[jt]->pos2.y);
				float minim = min(min(dist[0], dist[1]), min(dist[2], dist[3]));
				if (dist[0] == minim) {
					entities[it]->pos.x = ziduri[jt]->pos.x;
					entities[it]->speed.x *= -1;
				}
				else {
					if (dist[1] == minim) {
						entities[it]->pos.x = ziduri[jt]->pos2.x;
						entities[it]->speed.x *= -1;
					}
					else {
						if (dist[2] == minim) {
							entities[it]->pos.y = ziduri[jt]->pos.y;
							entities[it]->speed.y *= -1;
						}
						else {
							entities[it]->pos.y = ziduri[jt]->pos2.y;
							entities[it]->speed.y *= -1;
						}
					}
				}
			}


		}
	}
	//porti
	for (int it = 0; it < entities.size() - 1; it++) {
		v2 = v2 + entities[it]->speed;
		for (int jt = 0; jt < porti.size(); jt++) {
			if (!porti[jt]->IsActive)continue;
			if (entities[it]->pos.x <= porti[jt]->pos2.x && entities[it]->pos.x >= porti[jt]->pos.x && entities[it]->pos.y <= porti[jt]->pos2.y && entities[it]->pos.y >= porti[jt]->pos.y) {
				float dist[4];
				dist[0] = abs(entities[it]->pos.x - porti[jt]->pos.x);
				dist[1] = abs(entities[it]->pos.x - porti[jt]->pos2.x);
				dist[2] = abs(entities[it]->pos.y - porti[jt]->pos.y);
				dist[3] = abs(entities[it]->pos.y - porti[jt]->pos2.y);
				float minim = min(min(dist[0], dist[1]), min(dist[2], dist[3]));
				if (dist[0] == minim) {
					entities[it]->pos.x = porti[jt]->pos.x;
					entities[it]->speed.x *= -1;
				}
				else {
					if (dist[1] == minim) {
						entities[it]->pos.x = porti[jt]->pos2.x;
						entities[it]->speed.x *= -1;
					}
					else {
						if (dist[2] == minim) {
							entities[it]->pos.y = porti[jt]->pos.y;
							entities[it]->speed.y *= -1;
						}
						else {
							entities[it]->pos.y = porti[jt]->pos2.y;
							entities[it]->speed.y *= -1;
						}
					}
				}
			}


		}
	}
	//pistoane
	for (int it = 0; it < entities.size() - 1; it++) {
		v2 = v2 + entities[it]->speed;
		for (int jt = 0; jt < pistoane.size(); jt++) {
			if (entities[it]->pos.x <= pistoane[jt]->pos2.x && entities[it]->pos.x >= pistoane[jt]->pos.x && entities[it]->pos.y <= pistoane[jt]->pos2.y && entities[it]->pos.y >= pistoane[jt]->pos.y) {
				float dist[4];
				if(!pistoane[jt]->locked)pistoane[jt]->speed.y += entities[it]->speed.y / 100;
				entities[it]->speed.y -= entities[it]->speed.y / 10;
				entities[it]->speed.y += pistoane[jt]->speed.y * 10;
				dist[0] = abs(entities[it]->pos.x - pistoane[jt]->pos.x);
				dist[1] = abs(entities[it]->pos.x - pistoane[jt]->pos2.x);
				dist[2] = abs(entities[it]->pos.y - pistoane[jt]->pos.y);
				dist[3] = abs(entities[it]->pos.y - pistoane[jt]->pos2.y);
				float minim = min(min(dist[0], dist[1]), min(dist[2], dist[3]));
				if (dist[0] == minim) {
					entities[it]->pos.x = pistoane[jt]->pos.x;
					entities[it]->speed.x *= -1;
				}
				else {
					if (dist[1] == minim) {
						entities[it]->pos.x = pistoane[jt]->pos2.x;
						entities[it]->speed.x *= -1;
					}
					else {
						if (dist[2] == minim) {
							entities[it]->pos.y = pistoane[jt]->pos.y;
							entities[it]->speed.y *= -1;
						}
						else {
							entities[it]->pos.y = pistoane[jt]->pos2.y;
							entities[it]->speed.y *= -1;
						}
					}
				}
			}

		}

			
		
	}
	for (int it = 0; it < entities.size(); it++) {
		entities[it]->Update();
		entities[it]->Draw();
	}
	for (int it = 0; it < areas.size(); it++) {
		areas[it]->Update();
		areas[it]->Draw();
	}
	for (int it = 0; it < pistoane.size(); it++) {
		pistoane[it]->Update();
		pistoane[it]->Draw();
	}
	for (int it = 0; it < ziduri.size(); it++) {
		ziduri[it]->Draw();
	}
	for (int it = 0; it < porti.size(); it++) {
		if(porti[it]->IsActive)porti[it]->Draw();
	}
	for (Event* ev : events) {
		ev->fire();
	}
	gui_update();
}


void defs::Event::fire() {
	if (this->rate_left > 0) {
		this->rate_left= this->rate_left-1;
		return;
	}
	this->rate_left = this->rate;
	switch (this->type) {
	case Ev_Heat:
	{
		for (Particle* part : entities) {
			if (areas[this->ID]->Contains(part->pos)) {
				part->speed = part->speed * this->intensity_2D;
			}
		}
		break;
	}
	case Ev_Delete:
	{
		for (int ia = 0; ia < ((int)entities.size())-2;ia++) {
			if (areas[this->ID]->Contains(entities[ia]->pos)) {
				entities[ia] = entities[entities.size() - 2];
				entities.pop_back();
				ia--;
			}
		}
		break;
	}
	case Ev_FanA:
	{
		for (auto part: entities) {
			if (areas[this->ID]->Contains(part->pos)) {
				part->speed = this->intensity_2D;
			}
		}
		break;
	}
	case Ev_Spawn:
	{
		int nr = this->intensity_2D.x;
		for (int nri = 0; nri < nr; nri++) {
			Particle* e = new Particle();
			e->pos = Vector2(rand() % ((int)(areas[ID]->pos.x - areas[ID]->pos2.x)) + areas[ID]->pos.x, rand() % ((int)(areas[ID]->pos.y - areas[ID]->pos2.y)) + areas[ID]->pos.y);
			e->GetType = Particle_;
			entities.push_back(e);
		}
		break;
	}
	case Ev_Toggle_Gate:
	{
		porti[this->ID]->IsActive = !porti[this->ID]->IsActive;
		break;
	}
	case Ev_Piston_Lock:
	{
		pistoane[this->ID]->locked = !pistoane[this->ID]->locked;
		break;
	}
	case Ev_Piston_Push:
	{
		pistoane[this->ID]->speed = pistoane[this->ID]->speed + this->intensity_2D;
		break;
	}
	default:throw("wtf");
	}
}

void _start() {
	for (int it = 1; it <= 1; it++) {
		Particle *e=new Particle();
		e->GetType = Particle_;
		entities.push_back(e);
	}
	_update();
}
void Sync2(int b_a, Block b_l) {
	bl_await = b_a;
	bl = b_l;
	
}

void _command(string arg) {
	if (arg == "executie" || arg=="e") {
		int k;
		cin >> k;
		while (k) {
			_update();
			k--;
		}
		return;
	}
	if (arg == "creare" || arg=="c") {
		string s;
		cin >> s;
		bl_await = 1;
		Sync(bl_await, bl);
		cout << "Sus stanga:";
		cv::waitKey(0);
		cout << "Confirmat!\n";
		bl_await = 2;
		Sync(bl_await, bl);
		cout << "Jos Dreapta:";
		cv::waitKey(0);
		cout << "Confirmat!\n";
		bl_await = 0;
		Sync(bl_await, bl);

		Block* b = new Block;
		b->IsActive = true;
		*b = bl;
		if (s == "zid") {
			b->GetType = Block_;
			cout << "Zid creat cu ID = " << ziduri.size() << '\n';
			ziduri.push_back(b);
			_update();
			return;
		}
		if (s == "poarta") {
			b->GetType = Block_;
			cout << "Poarta creata cu ID = " << porti.size() << '\n';
			ziduri.push_back(b);
			porti.push_back(b);
			_update();
			return;
		}
		if (s == "piston") {
			b->GetType = Block_;
			Piston* pis = new Piston();
			pis->GetType = Piston_;
			pis->speed = Vector2(0, 0);
			pis->pos = b->pos;
			pis->pos2 = b->pos2;

			bl_await = 1;
			Sync(bl_await, bl);
			cout << "Maxim:";
			cv::waitKey(0);
			cout << "Confirmat!\n";
			bl_await = 2;
			Sync(bl_await, bl);
			cout << "Minim:";
			cv::waitKey(0);
			cout << "Confirmat!\n";
			bl_await = 0;
			Sync(bl_await, bl);

			pis->max_u = bl.pos2.y;
			pis->max_d = bl.pos.y;
			cout << "Piston creata cu ID = " << pistoane.size() << '\n';
			pistoane.push_back(pis);
			_update();
			return;
		}
		if (s == "zona") {
			Area *a = new Area();
			a->GetType = Area_;
			a->pos = b->pos;
			a->pos2 = b->pos2;
			a->ID = areas.size();
			add_rand_col();
			cout << "Zona creata cu ID = "<<areas.size()<<'\n';
			areas.push_back(a);
			_update();
			return;
		}
		
	}
	if (arg == "clear") {
		while (entities.size()>= 2) {
			delete entities.back();
			entities.pop_back();
		}
		while (!areas.empty()) {
			delete areas.back();
			areas.pop_back();
		}
		while (!pistoane.empty()) {
			delete pistoane.back();
			pistoane.pop_back();
		}
		while (!porti.empty()) {
			delete porti.back();
			porti.pop_back();
		}
		while (!ziduri.empty()) {
			delete ziduri.back();
			ziduri.pop_back();
		}
		events.clear();
		return;
	}
	if (arg == "mod") {
		string s;
		cin >> s;

		SetMap(s);
	}
	if (arg == "adaugare" || arg == "a") {
		int ID, nr;
		cin >> ID >> nr;
		for (int nri = 0; nri < nr; nri++) {
			Particle* e = new Particle();
			e->pos = Vector2(rand() % ((int)(areas[ID]->pos.x - areas[ID]->pos2.x))+areas[ID]->pos.x, rand() % ((int)(areas[ID]->pos.y - areas[ID]->pos2.y)) + areas[ID]->pos.y);
			e->GetType = Particle_;
			entities.push_back(e);
		}
		_update();
	}
	if (arg == "event"||arg=="ev") {
		string mod_ev;
		cin >> mod_ev;
		int ID , rate;
		cin >> ID >> rate;
		EventType evt = Ev_Spawn;

		float xx, yy;
		xx = yy = 0;
		if (mod_ev == "autoadaugare") {
			evt = Ev_Spawn;
			cin >> xx;
		}
		if (mod_ev == "incalzire") {
			evt = Ev_Heat;
			cin >> xx;
			yy = xx;
		}
		if (mod_ev == "ventilatorA") {
			evt = Ev_FanA;
			cin >> xx >> yy;
		}
		if (mod_ev == "ventilatorB") {
			evt = Ev_FanB;
		}
		if (mod_ev == "sterge") {
			evt = Ev_Delete;
		}
		if (mod_ev == "lock") {
			evt = Ev_Piston_Lock;
		}
		if (mod_ev == "deschide") {
			evt = Ev_Toggle_Gate;
		}
		if (mod_ev == "impinge") {
			evt = Ev_Piston_Push;
			cin >> yy;
		}
		events.push_back(new Event(evt, ID, rate, Vector2(xx, yy)));

	}
	if (arg == "ajutor") {
		cout << "comenzi:\ncreare zid\ncreare piston\ncreare zona(va crea o zona unde se pot adauga particule)\nmod termal/construire/executie (schimba modul de afisare a particulelor)\nsterge (sterge tot)\nexecutie [nr_de_frameuri] (executa simulatia)a\nadaugare [ID_zona] [nr_de_particule] (adauga particule intr-o zona)";
	}
	if (arg == "load") {
		string path;
		cin >> path;
		ifstream in(path);

		//sterge
		while (entities.size() > 1) {
			delete entities.back();
			entities.pop_back();
		}
		while (!areas.empty()) {
			delete areas.back();
			areas.pop_back();
		}
		while (!pistoane.empty()) {
			delete pistoane.back();
			pistoane.pop_back();
		}
		while (!porti.empty()) {
			delete porti.back();
			porti.pop_back();
		}
		while (!ziduri.empty()) {
			delete ziduri.back();
			ziduri.pop_back();
		}
		events.clear();

		int type;
		while (in >> type) {
			switch (type) {
			case 2: // zid
			{
				Block* b = new Block();
				b->GetType = Block_;
				in >> b->ID >> b->IsActive >> b->pos.x >> b->pos.y >> b->pos2.x >> b->pos2.y >> b->speed.x >> b->speed.y;
				ziduri.push_back(b);
				break;
			}
			case 3: // zona
			{
				Area* b = new Area();
				b->GetType = Area_;
				in >> b->ID >> b->pos.x >> b->pos.y >> b->pos2.x >> b->pos2.y >> b->speed.x >> b->speed.y;
				add_rand_col();
				areas.push_back(b);
				break;
			}
			case 4: // piston
			{
				Piston* b = new Piston();
				b->GetType = Piston_;
				in >> b->ID >> b->locked>>b->pos.x >> b->pos.y >> b->pos2.x >> b->pos2.y >> b->speed.x >> b->speed.y >> b->max_d >> b->max_u;
				pistoane.push_back(b);
				break;
			}
			case 5: // poarta
			{
				Block* b = new Block();
				b->GetType = Block_;
				in >> b->ID >> b->IsActive >> b->pos.x >> b->pos.y >> b->pos2.x >> b->pos2.y >> b->speed.x >> b->speed.y;
				porti.push_back(b);
				break;
			}
			case 6: // eveniment
			{
				int ID, evt, rate, xx, yy ,rate_left;
				in >> ID >> xx >> yy >> rate >> rate_left >> evt;
				EventType ev = static_cast<EventType>(evt);
				Event* e = new Event(ev,ID,rate,Vector2(xx,yy));
				e->rate_left = rate_left;
				events.push_back(e);
				break;
			}
			}
		}
		_update();

	}
	if (arg == "save") {
		string path;
		cin >> path;
		ofstream out(path);
		//particulele nu se salveaza
		for (auto z : ziduri) {
			out << z->GetType << ' ' << z->ID << ' ' << z->IsActive << ' ' << z->pos.x << ' ' << z->pos.y << ' ' << z->pos2.x << ' ' << z->pos2.y << ' ' << z->speed.x << ' ' << z->speed.y;
			out << '\n';
		}
		for (auto z : porti) {
			out << Poarta_    << ' ' << z->ID << ' ' << z->IsActive << ' ' << z->pos.x << ' ' << z->pos.y << ' ' << z->pos2.x << ' ' << z->pos2.y << ' ' << z->speed.x << ' ' << z->speed.y;
			out << '\n';
		}
		for (auto z : pistoane) {
			out << z->GetType << ' ' << z->ID << ' ' << z->locked<<' '<<z->pos.x << ' ' << z->pos.y << ' ' << z->pos2.x << ' ' << z->pos2.y << ' ' << z->speed.x << ' ' << z->speed.y << ' ' << z->max_d << ' ' << z->max_u;
			out << '\n';
		}
		for (auto z : areas) {
			out << z->GetType << ' ' << z->ID << ' ' << z->pos.x << ' ' << z->pos.y << ' ' << z->pos2.x << ' ' << z->pos2.y << ' ' << z->speed.x << ' ' << z->speed.y;
			out << '\n';
		}
		for (auto e: events) {
			out << 6 << " " << e->ID << ' ' << e->intensity_2D.x << ' ' << e->intensity_2D.y << ' ' << e->rate << ' ' << e->rate_left << ' ' << e->type;
			out << '\n';
		}
		cout << "Fisier salvat cu numele de " + path + "\n";
	}

}
int main()
{
	srand(time(0));
	cout << "Proiect facut de Covrig Marius Andrei\nscrie \"ajutor\" pentru a vedea meniul de ajutor\n";
	gui_start();
	_start();
	while (true) {
		string s;
		cin >> s;
		_command(s);
	}
}