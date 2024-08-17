#include "baseentity.h"

static long next_id = 1;

BaseEntity::BaseEntity(): id {0}, created_at {0}, modified_at {0} {}

long BaseEntity::get_id() const
{
    return id;
}

long BaseEntity::get_created_at() const
{
    return created_at;
}

long BaseEntity::get_modified_at() const
{
    return modified_at;
}

void BaseEntity::set_modified_at(long modified)
{
    modified_at = modified;
}

