#include <model/runestone.h>
#include <model/tarotcard.h>

#include <iomanip>
#include <sstream>

namespace Model
{
    Runestone::Runestone(long id, const std::string &name, const std::string &meaning) :
            BaseEntity {id}, m_name {name}, m_meaning {meaning}, m_colours {std::vector<Colour> {}}, m_gods {std::vector<God> {}},
            m_herbs {std::vector<Herb> {}}, m_planets {std::vector<Planet> {}}, m_polarity {Polarity {}},
            m_tarot_card {}, m_trees {std::vector<Tree> {}}, m_zodiacs {std::vector<Zodiac> {}} {}

    Runestone::Runestone(const Runestone &source) : BaseEntity {source.id}, m_name {source.m_name}, m_meaning {source.m_meaning}, 
            m_colours {source.m_colours}, m_gods {source.m_gods}, m_herbs {source.m_herbs}, m_planets {source.m_planets}, 
            m_polarity {source.m_polarity}, m_tarot_card {source.m_tarot_card}, m_trees {source.m_trees}, m_zodiacs {source.m_zodiacs} {}

    std::string Runestone::name() const
    {
        return this->m_name;
    }

    std::string Runestone::meaning() const
    {
        return this->m_meaning;
    }

    std::vector<Colour> Runestone::colours() const
    {
        return this->m_colours;
    }

    std::vector<God> Runestone::gods() const
    {
        return this->m_gods;
    }

    std::vector<Herb> Runestone::herbs() const
    {
        return this->m_herbs;
    }

    std::vector<Planet> Runestone::planets() const
    {
        return this->m_planets;
    }

    Polarity Runestone::polarity() const
    {
        return this->m_polarity;
    }

    TarotCard Runestone::tarot_card() const
    {
        std::shared_ptr<TarotCard> shared {this->m_tarot_card.lock()};
        return *shared;
    }

    std::vector<Tree> Runestone::trees() const
    {
        return this->m_trees;
    }

    std::vector<Zodiac> Runestone::zodiacs() const
    {
        return this->m_zodiacs;
    }

    void Runestone::name(const std::string &name)
    {
        this->m_name = name;
    }

    void Runestone::meaning(const std::string &meaning)
    {
        this->m_meaning = meaning;
    }

    void Runestone::polarity(const Polarity &polarity)
    {
        this->m_polarity = polarity;
    }

    void Runestone::tarot_card(const TarotCard &tarot_card)
    {
        std::shared_ptr<TarotCard> shared = std::make_shared<TarotCard>(tarot_card);
        this->m_tarot_card = shared;
    }

    void Runestone::add_colour(const Colour &colour)
    {
        this->m_colours.push_back(colour);
    }

    void Runestone::add_god(const God &god)
    {
        this->m_gods.push_back(god);
    }

    void Runestone::add_herb(const Herb &herb)
    {
        this->m_herbs.push_back(herb);
    }

    void Runestone::add_planet(const Planet &planet)
    {
        this->m_planets.push_back(planet);
    }

    void Runestone::add_tree(const Tree &tree)
    {
        this->m_trees.push_back(tree);
    }

    void Runestone::add_zodiac(const Zodiac &zodiac)
    {
        this->m_zodiacs.push_back(zodiac);
    }

    std::string Runestone::to_string() const
    {
        std::stringstream ss;
        ss << std::left << std::setw(5) << this->id << std::setw(10) << this->m_name << this->m_meaning;
        return ss.str();
    }
}
