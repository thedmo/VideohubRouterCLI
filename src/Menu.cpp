#include "menu.h"

Menu::Menu(std::string menu_name) : m_menuName(menu_name) {
    m_entries = new Entries;
    AddEntry("q", "exit " + m_menuName, ([this]() { Quit(); }));
}

Menu::~Menu() {
    for (auto entry : *m_entries) {
        delete (entry);
        entry = nullptr;
    }

    delete (m_entries);
    m_entries = nullptr;
}

void Menu::AddEntry(std::string command, std::string description,
                    EntryFunction method) {
    Entry* newOption = new Entry;
    newOption->command = command;
    newOption->description = description;
    newOption->method = method;

    m_entries->push_back(newOption);
}

void Menu::Quit() { m_quit = true; }

void Menu::EnterMenu() {
    m_quit = false;
    while (!m_quit) {
        std::string input;

        while (!m_quit) {
            PrintMenu();
            std::cin >> input;
            EvaluateUserInput(input);
        }
    }
}

// present possible options to user
void Menu::PrintMenu() {
    std::cout << "\n" + m_menuName + "\nWhat do you want to do?\n\n";
    for (auto item : *m_entries) {
        std::cout << item->command << ": " << item->description << "\n";
    }
    std::cout << std::endl;
}

void Menu::EvaluateUserInput(std::string input) {
    for (auto item : *m_entries) {
        if (item->command == input) {
            std::cout << item->description << std::endl;
            item->method();
            return;
        }
    }

    std::cout << "No valid choice. Please choose from given options."
              << std::endl;
}

// Sub menu
void Menu::AddSubMenu(std::string command, std::string sub_menu_name) {
    m_menu = new Menu(sub_menu_name);
    AddEntry(command, sub_menu_name, [this]() { m_menu->EnterMenu(); });
}

Menu* Menu::GetSubMenu() { return m_menu; }