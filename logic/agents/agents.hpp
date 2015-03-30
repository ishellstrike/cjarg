#ifndef AGENTS_H
#define AGENTS_H

#define CASTERS \
    CASTER(Chest) \
    CASTER(Furnance) \
    CASTER(Joinable) \
    CASTER(Organ) \
    CASTER(Wander)

#define PARTS_PARSER                                                                                               \
    if(val.HasMember("parts")) {                                                                                   \
        rapidjson::Value &arr = val["parts"];                                                                      \
        if(val["parts"].IsArray())                                                                                 \
        for(int a = 0; a < arr.Size(); a++)                                                                        \
        {                                                                                                          \
            rapidjson::Value &part = arr[a];                                                                       \
            if(part.HasMember("type")) {                                                                           \
                CASTERS                                                                                            \
                /*else here*/ LOG(error) << "record \"" << id << "\" agent #" << a + 1 << " has unknown \"type\""; \
            }                                                                                                      \
            else                                                                                                   \
                LOG(error) << "record \"" << id << "\" agent #" << a + 1 << " has no type";                        \
        }                                                                                                          \
        else                                                                                                       \
            LOG(error) << "record \"" << id << "\" parts is not valid agents array";                               \
    }

#include "agent.h"

#include "chest.h"
#include "furnance.h"
#include "joinable.h"
#include "fatal.h"
#include "wander.h"

#endif // AGENTS_H

