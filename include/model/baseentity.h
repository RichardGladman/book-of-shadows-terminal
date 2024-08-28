#ifndef BASEENTITY_H
#define BASEENTITY_H

namespace Model 
{
    class BaseEntity
    {
    public:
        BaseEntity() = default;
        BaseEntity(int id);

        BaseEntity(const BaseEntity &source);

        long get_id() const;
        long get_created_at() const;
        long get_modified_at() const;

        void set_modified_at(long modified);

    protected:
        long id;
        long created_at;
        long modified_at;

    private:
        static long next_id;
    };
}

#endif // BASEENTITY_H
