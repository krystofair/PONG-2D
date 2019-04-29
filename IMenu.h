//
// Created by Christofair on 23.04.2019.
//

#include <list>
#include <vector>

#ifndef PONG_IMENU_H
#define PONG_IMENU_H


/**
 * Interface to all menu in game.
 * If someone want to change something
 * please write appropriate issue about this.
 * Greeting by Christofair.
 */
class IMenu
{
public:
    using OptionType = sf::Text;
    template <typename T>
    using Kontener = std::list<T>;

    IMenu() = default;
    virtual ~IMenu() = default;
    /**
     * Zaznacza opcje w menu.
     * @param t: jest wskaźnikiem do opcji, która powinna być zaznaczona.
     */
    virtual bool zaznaczOpcje(Kontener<OptionType>::iterator) = 0;

    /**
     * Odznacza opcje w menu.
     * @param t: jest wskaźnikiem do opcji, która powinna być odznaczona.
     */
    virtual bool odznaczOpcje() = 0;

    /**
     * Wykonuje kod, który powinnien się wykonać w czasie wybrania danej opcji.
     * @param t: jest wskaźnikiem na opcje do uruchomienia.
     */
    virtual void uruchomOpcje(Kontener<OptionType>::iterator t) = 0;

    /**
     * Zwraca wskaźnik do obecnie zaznaczonej opcji
     * bo się przyda.
     */
    virtual Kontener<OptionType>::iterator getZaz() = 0;

    /**
     * Zwraca referencje do kontenera z opcjami.
     */
    virtual Kontener<OptionType>& getKontOpcji() = 0;

protected:
    Kontener<OptionType> opcje;
    Kontener<OptionType>::iterator zaznaczona;
};


#endif //PONG_IMENU_H
