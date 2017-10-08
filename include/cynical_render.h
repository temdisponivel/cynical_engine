//
// Created by Morpheus on 07-Oct-17.
//

#ifndef CYNICAL_ENGINE_CYNICAL_RENDER_H
#define CYNICAL_ENGINE_CYNICAL_RENDER_H

#include "cynical_graphics.h"

void start_draw();

void bind_material(material* material);

void draw(mesh* mesh);

void end_draw();

#endif //CYNICAL_ENGINE_MFE_RENDER_H
