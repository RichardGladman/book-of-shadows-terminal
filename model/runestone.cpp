#include "runestone.h"
#include "tarotcard.h"

Runestone::Runestone() {}

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
    return *this->m_tarot_card;
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
    *this->m_tarot_card = tarot_card;
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
