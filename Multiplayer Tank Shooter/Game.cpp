#include "Game.hpp"
#include "GamePanel.hpp"

Game::Game()
    : m_assetManager(std::make_shared<AssetManager>()),
    m_networkManager(std::make_shared<NetworkManager>()),
    m_audioManager(std::make_shared<AudioManager>()),
    m_window(sf::VideoMode(800, 600), "Tank Shooter")
{
    m_gui.setTarget(m_window);

    m_bg = tgui::Picture::create("Assets/Images/Background/game_bg.jfif");
    m_bg->setSize(m_window.getSize().x, m_window.getSize().y);
    m_gui.add(m_bg);

    // Căn giữa ô nhập username
    m_editBox = tgui::EditBox::create();
    m_editBox->setSize(400,50);
    m_editBox->setAlignment(tgui::HorizontalAlignment::Center);
    m_editBox->setPosition((m_window.getSize().x / 2) - (m_editBox->getSize().x / 2),
        (m_window.getSize().y / 2) - (m_editBox->getSize().y / 2) ); // Điều chỉnh để nút Join Game ở dưới
    m_editBox->setDefaultText("Enter your username...");

    // Căn giữa nút Join Game
    m_joinGameBtn = tgui::Button::create();
    m_joinGameBtn->setSize(200, 50);
    m_joinGameBtn->setPosition((m_window.getSize().x / 2) - (m_joinGameBtn->getSize().x / 2),
        ((m_window.getSize().y / 2) + (m_editBox->getSize().y / 2) + 5)); // Nằm dưới ô nhập username
    m_joinGameBtn->setText("Join Game");

    m_assetManager->LoadSound("BtnClick", "Assets/Audio/mouse-click.mp3");
    m_joinGameBtn->onClick([&]() {
        m_sound.setBuffer(m_assetManager->GetSound("BtnClick"));
        m_sound.setPitch(3.0);
        m_sound.play();
        std::cout << "Clicked!!\n";
        std::string username = m_editBox->getText().toStdString();
        if (!username.empty()) {
            std::cout << "Username: " << username << std::endl;

            GamePanel gamePanel{m_audioManager, m_networkManager, m_assetManager, username};
            gamePanel.run();
            
            // m_audioManager->playSound("button_click");
        }
        else {
            std::cout << "Empty username\n";
        }
        });

    m_gui.add(m_editBox);
    m_gui.add(m_joinGameBtn);

    // Cập nhật lại vị trí khi khởi tạo
  
}

Game::~Game() {}

bool Game::run()
{
    while (true)
    {
        sf::Event event;
        while (m_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                return false;
            }
            else if (event.type == sf::Event::Resized)
            {
                m_window.setSize(sf::Vector2u(event.size.width, event.size.height));
                m_bg->setSize(event.size.width, event.size.height);

                // Cập nhật lại vị trí của nút Join Game và ô nhập username
                m_editBox->setPosition((m_window.getSize().x / 2) - (m_editBox->getSize().x / 2),
                    (m_window.getSize().y / 2) - (m_editBox->getSize().y / 2) - 25);
                m_joinGameBtn->setPosition((m_window.getSize().x / 2) - (m_joinGameBtn->getSize().x / 2),
                    ((m_window.getSize().y / 2) + (m_editBox->getSize().y / 2) + 5));

                m_gui.setTarget(m_window);
            }
            m_gui.handleEvent(event);
        }

        m_window.clear();
        m_gui.draw();
        m_window.display();
    }
}