#include "script.h"
#include "natives.h"
#include "types.h"
#include "nativeCaller.h"
#include "enums.h"

void update() {

    Hash tentModelHash = GAMEPLAY::GET_HASH_KEY(const_cast<char*>("p_tentarmypup01x"));


    Hash bedTextureHash = GAMEPLAY::GET_HASH_KEY(const_cast <char*>("p_bedrollopen03x"));


    bool tentColorChanged = false;

    Ped playerPed = PLAYER::PLAYER_PED_ID();

    Vector3 playerCoords = ENTITY::GET_ENTITY_COORDS(playerPed, true, false);


    // Get the closest tent object of type p_tentarmypup01x
    Object bed = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(
        playerCoords.x, playerCoords.y, playerCoords.z,
        20.0f, bedTextureHash, false, false, false
    );


    // Get the closest tent object of type p_tentarmypup01x
    Object tent = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(
        playerCoords.x, playerCoords.y, playerCoords.z,
        20.0f, tentModelHash, false, false, false
    );


    if (ENTITY::DOES_ENTITY_EXIST(tent) && ENTITY::DOES_ENTITY_EXIST(bed) && tentColorChanged == false) {
        //Apply custom texture override
        OBJECT::_SET_OBJECT_TEXTURE_VARIANT(tent, 2);
        tentColorChanged = true;  // Prevent reapplying
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
