#pragma once
#include "raylib.h"

class HealthComponent {

public:
	HealthComponent();
	HealthComponent(int HealthInput, int MaxHealthInput);

	int GetHealth();
	int GetMaxHealth();
	void SetHealth(int HealthInput);
	void SetMaxHealth(int MaxHealthInput);
	void AddHealth(int HealthAdded);
	void ApplyDamage(int Damage);

private:
	int Health;
	int MaxHealth;

};