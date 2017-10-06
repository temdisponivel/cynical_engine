//
// Created by Morpheus on 06-Oct-17.
//

#ifndef CYNICAL_ENGINE_CYNICAL_ENTITY_H
#define CYNICAL_ENGINE_CYNICAL_ENTITY_H

#include <cynical_math.h>

typedef struct world_entity_s {
    transform* transform;
} world_entity;

world_entity* make_world_entity();

void free_world_entity(world_entity* entity);

#endif //CYNICAL_ENGINE_CYNICAL_ENTITY_H
