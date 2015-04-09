#include<iostream>
#include<cstdlib>

using std::cout;
using std::endl;
using std::cin;

void option1() {
  cout << " (\\___/)" << endl;
  cout << " (='.'=)" << endl;
  cout << "*(\")_(\")" << endl;
}

void option2() {
  cout << "  .-\"-.  " << endl;
  cout << " /|o o|\\ " << endl;
  cout << "{/(_0_)\\}" << endl;
  cout << " _/ ^ \\_ " << endl;
  cout << "(/ /^\\ \\)-" << endl;
  cout << "\"\"\"   \"\"\"" << endl;
}

void option3() {
  cout << "Looks like we're done here" << endl;
  exit(0);
  cout << "Excuse me?" << endl;
  cout << "Well shit!" << endl;
}

void menuQuit(){
  cout << "How'd we get here?" << endl;
  cout << "Time to gtfo before everything breaks" << endl;
  exit(0);
}

//Will probably want to use a render 'buffer' paradigm.
int main(int argc, char** argv){
  int opt;
  int select = 0;
  char string1[] = "\t1. Pretty picture!";
  char string2[] = "\t2. Different picture!";
  char string3[] = "\t3. exit..";

  while(true){
    do{
      if(select == 1){
        cout << "\t-----------------------" << endl;
        cout << string1 << endl;
        cout << "\t-----------------------" << endl;
      } else {
        cout << "\t                       " << endl;
        cout << string1 << endl;
        cout << "\t                       " << endl;
      }

      if(select == 2){
        cout << "\t-----------------------" << endl;
        cout << string2 << endl;
        cout << "\t-----------------------" << endl;
      } else {
        cout << "\t                       " << endl;
        cout << string2 << endl;
        cout << "\t                       " << endl;
      }

      if(select == 3){
        cout << "\t-----------------------" << endl;
        cout << string3 << endl;
        cout << "\t-----------------------" << endl;
      } else {
        cout << "\t                       " << endl;
        cout << string3 << endl;
        cout << "\t                       " << endl;
      }

      cout << endl;

      cin >> opt;
      if(opt < 0 && opt > 4){
        cout << endl;
        cout << endl;
        cout << endl;
        cout << "What the actual hell..Try again." << endl;
      }
    }while(opt < 0 && opt > 4);

    switch(opt){
    case 1:
      option1();
      break;
    case 2:
      option2();
      break;
    case 3:
      option3();
      break;
    default:
      menuQuit();
      break;
    }

    cout << endl;
  }

  return 0;
}

