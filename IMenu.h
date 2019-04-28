//
// Created by Christofair on 23.04.2019.
//

#include <vector>

#ifndef PONG_IMENU_H
#define PONG_IMENU_H


//Here is type for IMenu, but that is only for omitted templates :D

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
	using Kontener = std::vector<T>;

	IMenu() = default;
	virtual ~IMenu() = default;
	/**
	 * Zaznacza opcje w menu.
	 * @param t: jest wskaŸnikiem do opcji, która powinna byæ zaznaczona.
	 */
	virtual void zaznaczOpcje(OptionType* t) = 0;

	/**
	 * Odznacza opcje w menu.
	 * @param t: jest wskaŸnikiem do opcji, która powinna byæ odznaczona.
	 */
	virtual void odznaczOpcje() = 0;

	/**
	 * Wykonuje kod, który powinnien siê wykonaæ w czasie wybrania danej opcji.
	 * @param t: jest wskaŸnikiem na opcje do uruchomienia.
	 */
	virtual void uruchomOpcje(OptionType* t) = 0;

	/**
	 * Zwraca wskaŸnik do obecnie zaznaczonej opcji
	 * bo siê przyda.
	 */
	virtual OptionType* getZaz() = 0;

	/**
	 * Zwraca referencje do kontenera z opcjami.
	 */
	virtual Kontener<OptionType>& getKontOpcji() = 0;

protected:
	Kontener<OptionType> opcje;
	OptionType* zaznaczona;
};


#endif //PONG_IMENU_H
