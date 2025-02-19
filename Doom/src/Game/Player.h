#pragma once
#include "Renderer/Camera.h"
#include "Components/Combat.h"
#include "Components/Healthbar.h"
#include "Components/Hitbox.h"
#include "Components/Transform.h"
#include "Components/RigidBody.h"
#include "GameObject.h"

#include "Renderer/DataStructures/Model.h"

class Player
{
public:
	enum class State : int { Walk = 1, Sprint = 2, Crouch = 3 };
	struct StateParams
	{
		float angularVelocity;
		float velocity;
		float height;

		StateParams(float angularVelocity, float velocity, float height)
			: angularVelocity(angularVelocity), velocity(velocity), height(height) {}
	};

	enum class GameState: int { Playing, GameOver, Win, Closed };

	GameState gameState{ GameState::Playing };

private:
	const StateParams walkParams{ 2.0f, 10.0f, 2.0f };
	const StateParams sprintParams{ 2.0f, 20.0f, 2.0f };
	const StateParams crouchParams{ 2.0f, 5.0f, 1.0f };
	StateParams activeParams = walkParams;

	Combat combat{ 1000, 100, 0.1f };
	Healthbar healthbar{ .465f, 0.55f };
	Hitbox hitbox = GOModels.at("player").hitbox;
	Transform transform;
	RigidBody rigidbody;

	State state{ State::Walk };
	Camera camera{ Transform(), 50.0f };

	float timer{ 0 };
	bool isShoot{ false };

public:
	static std::shared_ptr<Player> GetInstance();

	void Update(float dt);
	void Draw();

	void Collision(GameObject& collidedObject);

	void SetState(State newState);
	void SetTransform(Transform transform = Transform());
	void SetAngularVelocity(bool going, int x, int y);
	void SetVelocity(bool going, int x, int z);

	void Jump();

	void LookAt(glm::vec3 front);
	void Shoot();
	void ShootOn() { isShoot = true; }
	void ShootOff() { isShoot = false; }

	const Camera& GetCamera() { return camera; }

	Combat& GetCombat() { return combat; }
	Hitbox& GetHitbox() { return hitbox; }
	Transform& GetTransform() { return transform; }
	RigidBody& GetRigidBody() { return rigidbody; }

private:
	void UpdateVelocity();
};
