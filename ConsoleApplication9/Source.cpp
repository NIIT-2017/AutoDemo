#include <iostream>
using namespace std;

typedef unsigned short power_t;
enum Fuel {Petrol,Diesel};

class Engine
{
private:
	power_t power;
	Fuel fuel;
	double consume; // расход топлива
public:
	Engine(power_t p, Fuel f, double c)
	{
		power = p;
		fuel = f;
		consume = c;
	}
	double conFuel(size_t path)
	{
		return path*consume;
	}
};

class Tank
{
private:
	double capacity;
public:
	Tank(double cap) : capacity(cap) {}
	bool isEmpty() const { return capacity <= 0.0; }
	void consume(double value) {
		if (!isEmpty())
			capacity -= value;
	}
};

class Auto
{
protected:
	Engine *engine;
	Tank *tank;
public:
	Auto(Engine *e, Tank *t) :engine(e), tank(t)
	{}
	void move(size_t path)
	{
		size_t current = 0;
		while (current < path && tank->isEmpty() == false)
		{
			tank->consume(engine->conFuel(1.0));
			cout << "Current dist: " << current << "km" << endl;
			current++;
		}
		cout << "Stop!" << endl;
	}
};

class Car : public Auto
{
protected:
	size_t passengers;
public:
	Car(Engine *e, Tank *t, size_t pass) :Auto(e, t)
	{
		passengers = pass;
	}
};
class Lorry : public Auto
{
protected:
	size_t cargo;
public:
	Lorry(Engine *e, Tank *t, size_t c) :Auto(e, t)
	{
		cargo = c;
	}
};

class Bus : public Car
{
protected:
	Tank *addTank;
public:
	Bus(Engine *e, Tank *t, size_t p, Tank *at) :Car(e, t, p)
	{
		addTank = at;
	}
	void move(size_t path)
	{
		size_t current = 0;
		while (current < path && (tank->isEmpty() == false))
		{
			tank->consume(engine->conFuel(1.0));
			cout << "(1) Current dist: " << current << "km" << endl;
			current++;
		}
		if (current >= path) {
			cout << "Stop!" << endl;
			return;
		}
		while (current < path && (addTank->isEmpty() == false))
		{
			addTank->consume(engine->conFuel(1.0));
			cout << " (2) Current dist: " << current << "km" << endl;
			current++;
		}
		cout << "Stop!" << endl;
	}
};
int main()
{
	Bus bus(new Engine(400, Fuel::Diesel, 0.1), 
		     new Tank(150),
			 60,
			 new Tank(130));
	bus.move(1400);
	return 0;
}