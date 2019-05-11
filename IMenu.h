//
// Created by Christofair on 23.04.2019.
//

#include <list>

#ifndef PONG_IMENU_H
#define PONG_IMENU_H

/**
 * Klasa OptionType jest jak wskazuje nazwa typem opcji w menu,
 * jest to nic innego jak rozszerzony przez callbacki sf::Text.
 */
class OptionType : public sf::Text
{
public:
	OptionType(std::string opt_name, sf::Font& font, void(*func_opcji)())
		: sf::Text(opt_name, font), callback(func_opcji) {}
	void (*callback)();
	/**
	 * Uruchamia odpowiednio przypisany callback dla opcji
	 */
	void uruchom()
	{
		callback();
	}
};


/**
 * Interface to all menu in game.
 * If someone want to change something
 * please write appropriate issue about this.
 * Greeting by Christofair.
 */
class IMenu
{
public:

    IMenu() = default;
    virtual ~IMenu() = default;
    /**
     * Zaznacza opcje w menu.
     * @param t: jest wskaźnikiem do opcji, która powinna być zaznaczona.
     */
    virtual bool zaznaczOpcje(std::list<OptionType>::iterator) = 0;

    /**
     * Odznacza opcje w menu.
     * @param t: jest wskaźnikiem do opcji, która powinna być odznaczona.
     */
    virtual bool odznaczOpcje() = 0;

    /**
     * Wykonuje kod, który powinnien się wykonać w czasie wybrania danej opcji.
     * @param t: jest wskaźnikiem na opcje do uruchomienia.
     */
    virtual void uruchomOpcje(std::list<OptionType>::iterator t) = 0;

    /**
     * Zwraca wskaźnik do obecnie zaznaczonej opcji
     * bo się przyda.
     */
    virtual std::list<OptionType>::iterator getZaz() = 0;

    /**
     * Zwraca referencje do kontenera z opcjami.
     */
    virtual std::list<OptionType>& getKontOpcji() = 0;

protected:
    std::list<OptionType> opcje;
    std::list<OptionType>::iterator zaznaczona;
};


#endif //PONG_IMENU_H
