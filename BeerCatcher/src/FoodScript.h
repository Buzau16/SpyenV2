#pragma once
#include <Spyen.h>

class FoodScript : public Spyen::Script {
public:
	void OnCreate() override {
	}

	void OnUpdate(Spyen::Timestep ts) override {
		if (eaten) DestroySelf();
	}

	void OnEvent(Spyen::Event& event) override {
		Spyen::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<Spyen::EntityHitEvent>([&](Spyen::EntityHitEvent& e) { return OnCollision(e); });
	}

	bool OnCollision(Spyen::EntityHitEvent& event) {
		eaten = true;
		SPY_INFO("Food eaten");
		return false;
	}
private:
	bool eaten = false;

};