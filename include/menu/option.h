#ifndef OPTION_H
#define OPTION_H

#pragma once

#include <functional>
#include <string>

class Option
{
public:
    Option(char choice, const std::string &text, std::function<void()> action);
    ~Option();

    char get_choice() const;
    std::function<void()> get_action() const;

    void render() const;
    void render(bool dummy) const;

private:
    char m_choice;
    std::string m_text;
    std::function<void()> m_action;
};

#endif