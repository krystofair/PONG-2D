//
// Created by Christofair on 23.04.2019.
//
#include "IGracz.h"

#ifndef PONG_GRACZ_H
#define PONG_GRACZ_H

using Klawisz = sf::Keyboard::Key;

class Gracz : public IGracz
{
public:
    Gracz() = default;
    ~Gracz();
    
    /**
     * Opis metody zgodny z opisem w interfejsie `IGracz`.
     * @param r: obiekt rakiety, której będzie używała klasa `Gracz`.
     */
    void setRakieta(const Rakieta& r) override;
    Rakieta& getRakieta() const override;
    void setKlawisze(
            Klawisz up,
            Klawisz down,
            Klawisz left,
            Klawisz right);
    
    const Klawisz& getKlawisz(unsigned int index) const;


private:
    Rakieta *rakieta;
    Klawisz klawisze[4];

};


#endif //PONG_GRACZ_H
