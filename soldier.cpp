/**************************************************************
 *    File: soldier.cpp
 *     Dev: Samantha Walsh
 *   Class: COP 3003 Fall 2022
 *    Desc: Soldier NPC AI Project
 *
 * Audits:
 *      1.0.0: 10/18/2022 Lab 1 in class, project orientation
 *      1.0.1: 10/20/2022 Added loops and logic
 *      1.0.2: 10/27/2022 Expanded cases and functions
 *      1.0.3: 11/01/2022 Defining Class Objects
 *************************************************************/
#include <iostream>
#include <cstdlib> // random numbers
#include <ctime>   // random seed
#include "Character.h" // character class

// Constants & Types
// ------------------------------------------------------------

const int START_LVL_DIE = 6;
const int D_8 = 8;
const int HP_DIE = 28;
const int D_20 = 20;
const int ATTACKING_ARMOR_CLASS = 12;
const int DEFENDING_ARMOR_CLASS = 16;
const int RETREATING_ARMOR_CLASS = 18;

enum SoldierState {
    HOMING,
    PATROLLING,
    ATTACKING,
    DEFENDING,
    RETREATING
}; // soldier state

// Function Prototypes (Declarations)
// ------------------------------------------------------------

void populateCharacter(Character &characterToFill);
bool rollToHit(const int armorClass);
SoldierState homing(Character &soldierToCheck);
SoldierState patrolling(Character * enemyToCheck, Character * soldierToCheck);
SoldierState attacking(Character &characterToHit, Character &soldier, SoldierState &soldierState);
SoldierState defending(Character &characterToDefend, Character &soldier, SoldierState &soldierState);
SoldierState retreating(Character &characterToHit, Character &soldier, SoldierState &soldierState);
SoldierState checkIfEnemyIsDead(Character &enemy, SoldierState &soldierState);
void combat(Character &characterToHit, Character &soldier);

// Function Definitions
// ------------------------------------------------------------

int main() {

    // init random numbers
    std::srand(std::time(NULL));

    Character soldier;
    SoldierState soldierState = HOMING;
    populateCharacter(soldier);

    Character enemy;
    SoldierState enemyState = ATTACKING;
    populateCharacter(enemy);

    bool hitChance;

    // main game loop until soldier dies
    do {
        switch (soldierState) {

            case (HOMING):
                soldierState = homing(soldier);
                break;

            case (PATROLLING):
                soldierState = patrolling(&enemy,&soldier);
                break;

            case (ATTACKING):
                hitChance = rollToHit(ATTACKING_ARMOR_CLASS);
                if (hitChance){
                    soldierState = attacking(enemy, soldier, soldierState);
                } else
                    std::cout << "You failed to hit the target enemy." << std::endl;

                //hitChance = rollToHit(ATTACKING_ARMOR_CLASS);
                //if (hitChance){
                //    enemyState = attack(soldier,enemy,enemyState);
                //}
                break;

            case (DEFENDING):
                hitChance = rollToHit(DEFENDING_ARMOR_CLASS);
                if (hitChance){
                    soldierState = defending(enemy, soldier, soldierState);
                } else
                    std::cout << "You failed to hit the target enemy." << std::endl;
                break;

            case (RETREATING):
                hitChance = rollToHit(RETREATING_ARMOR_CLASS);
                if (hitChance){
                    soldierState = retreating(enemy, soldier, soldierState);
                } else
                    std::cout << "You failed to hit the target enemy." << std::endl;

        } // end Switch
    } while (soldier.getCurrentHP() > 0);

    return 0;
} // end main

// Roll To Hit
// ------------------------------------------------------------
bool rollToHit(const int armorClass){
    bool hit = false;
    int attackChance = std::rand() % D_20 + 1;
    if (attackChance >= armorClass) {
        hit = true;
    }
    return hit;
}

// Populate Character
// ------------------------------------------------------------
void populateCharacter(Character &characterToFill){
    int lvl = std::rand() % START_LVL_DIE + 1;
    int baseHP = std::rand() % HP_DIE + 1;
    characterToFill.setLvl(lvl);
    characterToFill.setBaseHP(baseHP);
    characterToFill.setFullHealth();
}

// Homing
// ------------------------------------------------------------
SoldierState homing(Character &soldierToCheck){
    if (soldierToCheck.getCurrentHP() == soldierToCheck.getMaxHP()) {
        std::cout << "Soldier is at full health." << std::endl;
        return PATROLLING;
    }  // end soldier full HP
    else {
        std::cout << "Soldier needs to heal." << std::endl;
        soldierToCheck.heal(soldierToCheck.getMaxHP() * 0.2);
        return HOMING;
    } // end soldier low HP
}


// Patrolling
// ------------------------------------------------------------
SoldierState patrolling(Character * enemyToCheck, Character * soldierToCheck){
    SoldierState stateChange = PATROLLING;
    int enemyCheck = std::rand() % D_20 + 1;
    if (enemyCheck == 1) {
        populateCharacter(*enemyToCheck);
        std::cout << "Soldier has encountered a level " << enemyToCheck->getLvl()
                  << " enemy with " << enemyToCheck->getCurrentHP()
                  << " hit points!" << std::endl;
        if (soldierToCheck->getCurrentHP() > (enemyToCheck->getCurrentHP()+2)){
            stateChange = ATTACKING;
        }else if (soldierToCheck->getCurrentHP() < (enemyToCheck->getCurrentHP()-2)) {
            stateChange = RETREATING;
        }else
            stateChange = DEFENDING;
    }  // end enemy with HP
    else {
        std::cout << "All clear." << std::endl;
    }
    return stateChange;
}


// Attacking
// ------------------------------------------------------------

SoldierState attacking(Character &enemyToHit, Character &soldier, SoldierState &soldierState){
    combat(enemyToHit,soldier);
    if (soldier.getCurrentHP() < (soldier.getMaxHP()*0.75)){
        std::cout << "Your health is medium, you are now defending." << std::endl;
        soldierState = DEFENDING;
    }
    soldierState = checkIfEnemyIsDead(enemyToHit,soldierState);
    return soldierState;
}


// Defending
// ------------------------------------------------------------
SoldierState defending(Character &enemyToHit, Character &soldier, SoldierState &soldierState){
    combat(enemyToHit,soldier);
    if (soldier.getCurrentHP() < (soldier.getMaxHP()/2)){
        std::cout << "Your health is low, you are now retreating." << std::endl;
        soldierState = RETREATING;
    }
    soldierState = checkIfEnemyIsDead(enemyToHit,soldierState);
    return soldierState;
}

// Retreating
// ------------------------------------------------------------
SoldierState retreating(Character &enemyToHit, Character &soldier, SoldierState &soldierState){
    combat(enemyToHit,soldier);
    soldierState = checkIfEnemyIsDead(enemyToHit,soldierState);
    return soldierState;
}

SoldierState checkIfEnemyIsDead(Character &enemy, SoldierState &soldierState) {
    if (enemy.getCurrentHP() < 0){
        soldierState = HOMING;
        std::cout << "The enemy is dead! Well done, you are now homing." << std::endl;
    }
    return soldierState;
}

void combat(Character &enemyToHit, Character &soldier){
    int damageToEnemy = std::rand() % D_8 + 1;
    if (damageToEnemy){
        std::cout << "The enemy took " << damageToEnemy << " points of damage." << std::endl;
        std::cout << "The enemy's health is now " << enemyToHit.getCurrentHP() << std::endl;
        enemyToHit.takeDamage(damageToEnemy);
    }

    // Enemy Attack
    bool hitChance = rollToHit(ATTACKING_ARMOR_CLASS);
    if(hitChance) {
        std::cout << "The enemy attacked!" << std::endl;
        int damageToSoldier = std::rand() % D_8 + 1;
        soldier.takeDamage(damageToSoldier);
        std::cout << "You took " << damageToSoldier << " points of damage. Your health is now " << soldier.getCurrentHP() << std::endl;
    }
}
