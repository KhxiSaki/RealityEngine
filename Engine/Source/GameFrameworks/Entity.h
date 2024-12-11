#pragma once

#include "Object.h"


class Entity : public Object {

public:

    Entity(int id) : id(id) {}

private:
    virtual void beginPlay() {}

    virtual void tick(float deltaTime) {}

protected:

    int id; // Unique identifier for the entity
};