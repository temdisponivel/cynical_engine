//
// Created by Morpheus on 06-Oct-17.
//

#include <cynical_entity.h>

world_entity* make_world_entity() {
    world_entity* entity = malloc(sizeof(world_entity));
    entity->transform = make_transform();
    return entity;
}

void free_world_entity(world_entity* entity) {
    free_transform(entity->transform);
    free(entity);
}
