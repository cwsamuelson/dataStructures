#ifndef __MENU_H__
#define __MENU_H__

#include<string>
#include<vector>
#include<functional>

class Menu{
private:
  std::string name;
  std::string prompt;
  //choices should probably each include a callback
  std::vector<std::pair<std::string, std::string>> choices;
  std::function<void(void)> delegate;
public:
  static const std::string menuend;

  Menu(std::string _name, std::string _prompt, std::vector<std::pair<std::string, std::string> > choices);
  virtual ~Menu();

  const std::string& getChoice();
  const std::string& getName() const;
  const std::string& getPrompt() const;
  void setDelegate(std::function<void(void)> callback);
};

#endif

