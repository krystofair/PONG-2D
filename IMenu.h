//
// Created by Christofair on 23.04.2019.
//

#include <SFML/Graphics/Text.hpp>
#include <list>

#ifndef PONG_IMENU_H
#define PONG_IMENU_H

/// Typ dla poleceń menu.
/// pola są argumentami na których działa polecenie
/// zaś metoda execute jest funkcją podejmująca na nich działania.
class ICommand
{
public:
	/// funkcja wykonująca dane polecenie.
	virtual void execute()=0;
	virtual ~ICommand(){}
};

/**
 * Klasa OptionType jest jak wskazuje nazwa jest typem opcji w menu,
 * jest to nic innego jak rozszerzony przez callbacki sf::Text.
 */
class OptionType : public sf::Text
{
public:
	OptionType(const sf::String& option_name,
			   sf::Font& font,
			   ICommand* command,
			   unsigned characterSize = 30)
		: sf::Text(option_name, font, characterSize), polecenie(command)
	{};
	ICommand* polecenie;
	/**
	 * Uruchamia odpowiednie przypisane polecenie.
	 */
	void uruchom()
	{
		if(polecenie != nullptr)
			polecenie->execute();
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
