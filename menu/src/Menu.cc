#include<iostream>
#include"Menu.hh"

Menu::Menu(std::string _name, std::string _prompt, std::vector<std::pair<std::string, std::string>> _choices = std::vector<std::pair<std::string, std::string>>()):name(_name), prompt(_prompt), choices(_choices){

}

Menu::~Menu(){
}

const std::string& Menu::getChoice(){
  if(this->choices.size() == 0){
    return Menu::menuend;
  }
  unsigned choice; 
  int i;
  do{ 
    i = 1;
    for (auto ch : this->choices){
      std::cout << i++ << ": " << ch.first << '\n';
    }
    std::cin >> choice; 
    --choice;
  }while (choice >= this->choices.size()); 
  return this->choices[choice].second; 
}

const std::string& Menu::getName() const{
  return this->name;
}

const std::string& Menu::getPrompt() const{
  return this->prompt;
}

void Menu::setDelegate(std::function<void(void)> callback){
  this->delegate = callback;
}

const std::string Menu::menuend{"END"};

