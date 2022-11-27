/**************************************************************
 *    File: Character.cpp
 *     Dev: Samantha Walsh
 *   Class: COP 3003 Fall 2022
 *    Desc: Implementation of a Character class object
 *************************************************************/
#include <iostream>
#include <cstdlib> // random numbers
#include <ctime>   // random seed
#include "Character.h" // character class


Character::Character() {
    lvl = 0;
    baseHP = 0;
    currentHP = 0;
    maxHP = 0;
}

Character::Character(int lvl, int baseHP) {
    this->lvl = lvl;
    this->baseHP = baseHP;
    maxHP = baseHP;
    currentHP = baseHP;
}

// Accessors
void Character::setLvl(int lvlToSet){ lvl = lvlToSet;}
void Character::setBaseHP(int baseHpToSet){ baseHP = baseHpToSet;}
void Character::setCurrentHP(int currentHpToSet){ currentHP = currentHpToSet;}

int Character::getLvl(){ return lvl; }
int Character::getBaseHP(){ return getBaseHP(); }
int Character::getCurrentHP(){ return currentHP; }
int Character::getMaxHP() { return maxHP; }

// Methods

void Character::setFullHealth(){
    currentHP = lvl * baseHP;
    maxHP = currentHP;
}

void Character::takeDamage(int damageToTake) {
    currentHP -= damageToTake;
}

void Character::heal(int amountToHeal) {
    currentHP += amountToHeal;
}
