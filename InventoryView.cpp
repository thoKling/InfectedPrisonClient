#include "InventoryView.h"
#include "Utils.h"
#include "TextureManager.h"



InventoryView::InventoryView(Inventory* inventory):
	_inventory(inventory)
{
}

InventoryView::~InventoryView()
{
}

void InventoryView::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//On remet la vue actuelle après l'affichage de l'inventaire
	sf::View temp = target.getView();
	target.setView(target.getDefaultView());

	// Fond flou
	sf::RectangleShape blur(sf::Vector2f(WINDOWS_HEIGHT, WINDOWS_WIDTH));
	blur.setFillColor(sf::Color(0, 0, 0, 128));
	target.draw(blur);

	// Fond
	sf::RectangleShape base(sf::Vector2f(WINDOWS_HEIGHT/2, WINDOWS_WIDTH- WINDOWS_WIDTH/4));
	base.setFillColor(sf::Color(50, 50, 50));
	base.setOutlineColor(sf::Color(255, 255, 255));
	base.setOutlineThickness(1);
	base.setPosition(WINDOWS_HEIGHT / 4, WINDOWS_WIDTH / 8);
	target.draw(base);


	target.setView(temp);
}

void InventoryView::handleInputs(const sf::Event& event)
{
}
