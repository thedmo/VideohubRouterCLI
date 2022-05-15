#pragma once

#include <functional>
#include <iostream>
#include <string>
#include <vector>

using EntryFunction = std::function<void()>;

struct Entry {
    std::string command;
    std::string description;
    EntryFunction method;
};
using Entries = std::vector<Entry*>;

class Menu {
   public:
    Menu() = delete;
    Menu(std::string menu_name);

    ~Menu();

    void AddEntry(std::string command, std::string description,
                  EntryFunction method);

    void EnterMenu();

    void PrintMenu();

    void EvaluateUserInput(std::string input);

    void AddSubMenu(std::string command, std::string sub_menu_name);
    
    Menu* GetSubMenu();

   private:
    std::string m_menuName;
    Entries* m_entries;
    Menu* m_menu;
    bool m_quit;

    void Quit();
};  // class MenuLib