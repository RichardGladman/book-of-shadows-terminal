#include "model/tarotcard.h"
#include "model/runestone.h"

namespace Model
{
    TarotCard::TarotCard(const std::string &name, const std::string &meaning) :
            m_name {name}, m_meaning {meaning}, m_colours {std::vector<Colour> {}}, m_gods {std::vector<God> {}},
            m_herbs {std::vector<Herb> {}}, m_planets {std::vector<Planet> {}}, m_polarity {Polarity {}},
            m_runestone {}, m_trees {std::vector<Tree> {}}, m_zodiacs {std::vector<Zodiac> {}} {}

    TarotCard::TarotCard(const TarotCard &source) : m_name {source.m_name}, m_meaning {source.m_meaning}, m_colours {source.m_colours},
            m_gods {source.m_gods}, m_herbs {source.m_herbs}, m_planets {source.m_planets}, m_polarity {source.m_polarity},
            m_runestone {source.m_runestone}, m_trees {source.m_trees}, m_zodiacs {source.m_zodiacs} {}

    std::string TarotCard::name() const
    {
        return this->m_name;
    }

    std::string TarotCard::meaning() const
    {
        return this->m_meaning;
    }

    std::vector<Colour> TarotCard::colours() const
    {
        return this->m_colours;
    }

    std::vector<God> TarotCard::gods() const
    {
        return this->m_gods;
    }

    std::vector<Herb> TarotCard::herbs() const
    {
        return this->m_herbs;
    }

    std::vector<Planet> TarotCard::planets() const
    {
        return this->m_planets;
    }

    Polarity TarotCard::polarity() const
    {
        return this->m_polarity;
    }

    Runestone TarotCard::runestone() const
    {
        return *this->m_runestone;
    }

    std::vector<Tree> TarotCard::trees() const
    {
        return this->m_trees;
    }

    std::vector<Zodiac> TarotCard::zodiacs() const
    {
        return this->m_zodiacs;
    }

    void TarotCard::name(const std::string &name)
    {
        this->m_name = name;
    }

    void TarotCard::meaning(const std::string &meaning)
    {
        this->m_meaning = meaning;
    }

    void TarotCard::polarity(const Polarity &polarity)
    {
        this->m_polarity = polarity;
    }

    void TarotCard::runestone(const Runestone &runestone)
    {
        *this->m_runestone = runestone;
    }

    void TarotCard::add_colour(const Colour &colour)
    {
        this->m_colours.push_back(colour);
    }

    void TarotCard::add_god(const God &god)
    {
        this->m_gods.push_back(god);
    }

    void TarotCard::add_herb(const Herb &herb)
    {
        this->m_herbs.push_back(herb);
    }

    void TarotCard::add_planet(const Planet &planet)
    {
        this->m_planets.push_back(planet);
    }

    void TarotCard::add_tree(const Tree &tree)
    {
        this->m_trees.push_back(tree);
    }

    void TarotCard::add_zodiac(const Zodiac &zodiac)
    {
        this->m_zodiacs.push_back(zodiac);
    }
}
