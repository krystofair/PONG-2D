//
// Created by Christofair on 23.04.2019.
//


#ifndef PONG_IMENU_H
#define PONG_IMENU_H


/**
 * Interface to all menu in game.
 * If someone want to change something
 * please write appropriate issue about this.
 * Greeting by Christofair.
 */
template <typename T>
class IMenu
{
public:
    IMenu() = default;
    virtual ~IMenu() = default;

    /**
     * Zaznacza opcje w menu.
     * @param t: jest wskaźnikiem do opcji, która powinna być zaznaczona.
     */
    virtual void zaznaczOpcje(T* t) = 0;

    /**
     * Odznacza opcje w menu.
     * @param t: jest wskaźnikiem do opcji, która powinna być odznaczona.
     */
    virtual void odznaczOpcje(T* t) = 0;

    /**
     * Wykonuje kod, który powinnien się wykonać w czasie wybrania danej opcji.
     * @param t: jest wskaźnikiem na opcje do uruchomienia.
     */
    virtual void uruchomOpcje(T* t) = 0;
};


#endif //PONG_IMENU_H
