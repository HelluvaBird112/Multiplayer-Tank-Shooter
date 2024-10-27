#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include "Game.hpp"
#include <filesystem>
int main()
{
    Game game{};
    std::cout << std::filesystem::current_path() << "\n";
    if (!game.run())
    {
        std::cout << "Cant run game!!";
    };
    return 0;
}