#pragma once
#include <Spyen.h>

class PlayerScript : public Spyen::Script {
public:
	void OnCreate() override {
		SPY_INFO("Creating player script intance");
	}

	void OnUpdate(Spyen::Timestep ts) override {
		auto& pos = GetPosition();
		if (Spyen::Input::IsKeyDown(Spyen::Key::W)) {
			pos.y += 250.f * ts;
		}
		if (Spyen::Input::IsKeyDown(Spyen::Key::S)) {
			pos.y -= 250.f * ts;
		}
		if (Spyen::Input::IsKeyDown(Spyen::Key::A)) {
			pos.x -= 250.f * ts;
		}
		if (Spyen::Input::IsKeyDown(Spyen::Key::D)) {
			pos.x += 250.f * ts;
		}
	}

	void OnEvent(Spyen::Event& event) override {
		Spyen::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<Spyen::EntityHitEvent>([&](Spyen::EntityHitEvent& e) { return OnCollision(e); });
	}

	bool OnCollision(Spyen::EntityHitEvent& event) {
		SPY_INFO("COX");
		Spyen::AudioEngine::PlaySound("shot");
		return true;
	}

};