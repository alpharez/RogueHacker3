#include <stdio.h>
#include "main.hpp"

static const int CRIT_FACTOR = 2;

Attacker::Attacker(float power) : power(power) {
}

Attacker::~Attacker() {
}

void Attacker::attack(Actor *owner, Actor *target) {
	// roll dice to see if critical hit
	TCODRandom *rng=TCODRandom::getInstance();
	int dice=rng->getInt(1,20); // 20 sided dice
	int hit_damage = power;
	if(dice > 17) {
		// CRIT!
		hit_damage *= CRIT_FACTOR;
		engine.gui->message(owner==engine.player ? TCODColor::green : TCODColor::red, "CRIT!!!");
	}
	if ( target->destructible && ! target->destructible->isDead() ) {
		if ( hit_damage - target->destructible->defense > 0 ) {
			engine.gui->message(owner==engine.player ? TCODColor::red : TCODColor::lightGrey,
   				"%s attacks %s for %g hit points.", owner->name, target->name,
   				hit_damage - target->destructible->defense);
		} else {
			engine.gui->message(TCODColor::lightGrey,
   				"%s attacks %s but it has no effect!", owner->name, target->name);
		}
		target->destructible->takeDamage(target,hit_damage);
	} else {
		engine.gui->message(TCODColor::lightGrey,
   			"%s attacks %s in vain.",owner->name,target->name);
	}
}
