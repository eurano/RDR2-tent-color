#include "script.h"
#include "natives.h"
#include "types.h"
#include "nativeCaller.h"
#include "enums.h"

void update() {
    Hash tentModelHash = GAMEPLAY::GET_HASH_KEY((char*)"p_tentarmypup01x");
    Hash bedModelHash = GAMEPLAY::GET_HASH_KEY((char*)"p_bedrollopen03x");

    static bool tentColorChanged = false;
    static Object currentTent = 0;
    static Object currentBed = 0;

    Ped playerPed = PLAYER::PLAYER_PED_ID();
    Vector3 playerCoords = ENTITY::GET_ENTITY_COORDS(playerPed, true, false);

    if (!tentColorChanged) {
        currentTent = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(playerCoords.x, playerCoords.y, playerCoords.z, 2.15f, tentModelHash, false, false, false);
        currentBed = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(playerCoords.x, playerCoords.y, playerCoords.z, 2.15f, bedModelHash, false, false, false);
    }

    float tentDist = 9999.0f;
    float bedDist = 9999.0f;
    float tentBedDist = 9999.0f;

    Vector3 tentCoords{}, bedCoords{};

    if (ENTITY::DOES_ENTITY_EXIST(currentTent)) {
        tentCoords = ENTITY::GET_ENTITY_COORDS(currentTent, true, false);
        tentDist = GAMEPLAY::GET_DISTANCE_BETWEEN_COORDS(playerCoords.x, playerCoords.y, playerCoords.z, tentCoords.x, tentCoords.y, tentCoords.z, true);
    }

    if (ENTITY::DOES_ENTITY_EXIST(currentBed)) {
        bedCoords = ENTITY::GET_ENTITY_COORDS(currentBed, true, false);
        bedDist = GAMEPLAY::GET_DISTANCE_BETWEEN_COORDS(playerCoords.x, playerCoords.y, playerCoords.z, bedCoords.x, bedCoords.y, bedCoords.z, true);
    }

    if (ENTITY::DOES_ENTITY_EXIST(currentTent) && ENTITY::DOES_ENTITY_EXIST(currentBed)) {
        tentBedDist = GAMEPLAY::GET_DISTANCE_BETWEEN_COORDS(tentCoords.x, tentCoords.y, tentCoords.z, bedCoords.x, bedCoords.y, bedCoords.z, true);

        if (!tentColorChanged && tentDist < 2.15f && bedDist < 2.15f && tentBedDist < 2.15f) {
            OBJECT::_SET_OBJECT_TEXTURE_VARIANT(currentTent, 4);
            tentColorChanged = true;
        }
    }

    if (tentColorChanged && (tentDist > 30.0f || bedDist > 30.0f)) {
        tentColorChanged = false;
        currentTent = 0;
        currentBed = 0;
    }
}

void main() {
    while (true) {
        update();
        WAIT(0);
    }
}

void ScriptMain() {
    srand(GetTickCount());
    main();
}
