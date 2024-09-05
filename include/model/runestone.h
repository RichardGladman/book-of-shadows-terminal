#ifndef RUNESTONE_H
#define RUNESTONE_H

#include <string>
#include <vector>
#include <memory>
#include "colour.h"
#include "god.h"
#include "herb.h"
#include "planet.h"
#include "polarity.h"
#include "tree.h"
#include "zodiac.h"

namespace Model
{
    class TarotCard;

    class Runestone : public BaseEntity
    {
    public:
        Runestone(long id, const std::string &name, const std::string &meaning);
        Runestone(const Runestone &source);

        std::string name() const;
        std::string meaning() const;

        std::vector<Colour> colours() const;
        std::vector<God> gods() const;
        std::vector<Herb> herbs() const;
        std::vector<Planet> planets() const;
        Polarity polarity() const;
        TarotCard tarot_card() const;
        std::vector<Tree> trees() const;
        std::vector<Zodiac> zodiacs() const;

        void name(const std::string &name);
        void meaning(const std::string &meaning);
        void polarity(const Polarity &polarity);
        void tarot_card(const TarotCard &tarot_card);

        void add_colour(const Colour &colour);
        void add_god(const God &god);
        void add_herb(const Herb &herb);
        void add_planet(const Planet &planet);
        void add_tree(const Tree &tree);
        void add_zodiac(const Zodiac &zodiac);

    private:
        std::string m_name;
        std::string m_meaning;

        std::vector<Colour> m_colours;
        std::vector<God> m_gods;
        std::vector<Herb> m_herbs;
        std::vector<Planet> m_planets;
        Polarity m_polarity;
        std::weak_ptr<TarotCard> m_tarot_card;
        std::vector<Tree> m_trees;
        std::vector<Zodiac> m_zodiacs;
    };
}
#endif // RUNESTONE_H
