/**************************************************************
 *    File: Character.h
 *     Dev: Samantha Walsh
 *   Class: COP 3003 Fall 2022
 *    Desc: Declaration of a Character class object
 *************************************************************/

// Header Guard
#ifndef SOLDIER_CHARACTER_H
#define SOLDIER_CHARACTER_H

class Character {
private:
    int lvl;
    int baseHP;
    int currentHP;
    int maxHP;

public:
    // Constructors
    // ------------------------------------------------------------
    Character(); // default constructor
    Character(int lvl, int baseHP); // property

    // Accessors
    // ------------------------------------------------------------
    void setLvl(int lvlToSet);
    void setBaseHP(int baseHpToSet);
    void setCurrentHP(int currentHpToSet);

    int getLvl();
    int getBaseHP();
    int getCurrentHP();
    int getMaxHP();

    // Methods
    // ------------------------------------------------------------
    void setFullHealth();
    void takeDamage(int damageToTake);
    void heal(int amountToHeal);
};


#endif //SOLDIER_CHARACTER_H
