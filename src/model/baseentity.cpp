#include "model/baseentity.h"

namespace Model
{
    static long next_id = 1;

    BaseEntity::BaseEntity(long id): id {id}, created_at {0}, modified_at {0} {}

    BaseEntity::BaseEntity(const BaseEntity &source) : id {source.id}, created_at {source.created_at}, modified_at {source.modified_at} {}

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
}
