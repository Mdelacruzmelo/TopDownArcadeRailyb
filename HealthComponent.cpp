#include "HealthComponent.h"

HealthComponent::HealthComponent() {
	Health = 100;
	MaxHealth = 100;
}

HealthComponent::HealthComponent(int HealthInput, int MaxHealthInput) {
	Health = HealthInput;
	MaxHealth = MaxHealthInput;
}

int HealthComponent::GetHealth() {
	return Health;
}

int HealthComponent::GetMaxHealth()
{
	return MaxHealth;
}

void HealthComponent::AddHealth(int HealthAdded) {
	if ((Health + HealthAdded) <= MaxHealth) {
		Health += HealthAdded;
	}
	else {
		Health = MaxHealth;
	}
}

void HealthComponent::SetHealth(int HealthInput) {
	Health = HealthInput;
}

void HealthComponent::SetMaxHealth(int MaxHealthInput) {
	MaxHealth = MaxHealthInput;
}

void HealthComponent::ApplyDamage(int Damage) {
	if ((Health - Damage) <= 0) {
		Health = 0;
	}
	else {
		Health -= Damage;
	}
}