#include"string.hh"

void string::init(){
    this->data = NULL;
    this->size = 0;
}

string::string(){
    this->init();
}

string::string(string& str){
    this->init();
    this->assign(str);
}

string::string(const char* s){
    this->init();
    this->assign(s);
}

string::~string(){
    free(this->data);
}

const char* string::getString() const{
    // perhaps add some extra protection.
    return this->data;
}

string& string::append(const string& str){
    return this->append(str, 0, str.length());
}

string& string::append(const string& str, size_t subpos, size_t sublen){
    size_t len = this->length() + str.length();
    char *temp;
    temp = new char[len];
    //char* temp = (char*)malloc(sizeof(char) * len);
    this->copy(temp);
    for(int i = subpos; i < subpos + sublen; i++){
        temp[i + this->length()] = str.data[i];
    }
    free(this->data);
    this->assign(temp);
    delete [] temp;
    //free(temp);
    this->size = len;
    return *this;
}

string& string::append(const char* s){
    int len = 0;
    while(!s[len]){
        len++;
    }
    this->append(s, len);
    return *this;
}

string& string::append(const char* s, size_t n){
    string temp(s);
    this->append(temp, 0, n);
    return *this;
}

string& string::append(size_t n, char c){
    char* temp = (char*)malloc(sizeof(char) * (this->length() + n));
    this->copy(temp);
    for(int i = this->length(); i < this->length() + n; i++){
        temp[i] = c;
    }
    this->assign(temp);
    free(temp);
    return *this;
}

string& string::assign(const string& str){
    this->assign(str, 0, str.length());
    return *this;
}

string& string::assign(const string& str, size_t subpos, size_t sublen){
    str.copy(this->data, subpos, sublen);
    this->size = str.length();
    return *this;
}

string& string::assign(const char* s){
    int len = 0;
    while(!s[len]){
        len++;
    }
    this->assign(s, len);
    return *this;
}

string& string::assign(const char* s, size_t n){
    free(this->data);
    this->data = (char*)malloc(sizeof(char) * n);
    for(int i = 0; i < n; i++){
        this->data[i] = s[i];
    }
    this->size = n;
    return *this;
}

string& string::assign(size_t n, char c){
    free(this->data);
    this->data = (char*)malloc(sizeof(char) * n);
    for(int i = 0; i < n; i++){
        this->data[i] = c;
    }
    return *this;
}

string& string::erase(size_t pos, size_t len){
    string first;
    first.assign(*this, 0, pos);
    string second;
    second.assign(*this, pos + len, len);
    first.append(second);
    this->assign(first);
    return *this;
}

size_t string::copy(char* s, size_t len, size_t pos) const{
    int i;
    for(i = pos; i < pos + len; i++){
        if(s[i]){
            s[i] = this->data[i];
        }
        else if(!s[i]){
            break;
        }
    }
    return i;
}

size_t string::find(char c){
    if(pos > this->length()){
        return string::npos;
    }

    for(i = pos; i < this->length(); i++){
        if(this->data[i] == c){
            break;
        }
    }

    return i;
}

size_t string::find(const string& str, size_t pos) const{
    int i;

    for(i = pos; i < this->length(); i++){
        if(this->data[i] == 
            break;
    }
    return i;
}

size_t string::find(const char* s, size_t pos) const{
    int i;
    if(s[i] != '\0'){
        break;
    } 
    return i;
}

size_t string::rfind(const string& str, size_t pos) const{
    int i;
    for(i = 0; i < this->length(); i++){
        if(this->data[i] == 
            break;
    }
    return i;
}

size_t string::rfind(const char* s, size_t pos) const{
    return 0;
}

size_t string::length() const{
    return this->size;
}

bool string::empty() const{
    return this->size;
}

void string::clear(){
    free(this->data);
    this->size = 0;
}

string& string::operator=(const string& str){
    this->assign(str);
    return *this;
}

string& string::operator=(const char* s){
    this->assign(s);
    return *this;
}

string& string::operator+=(const char* s){
    this->append(s);
    return *this;
}

string& string::operator+=(const string& str){
    this->append(str);
    return *this;
}

string  string::operator+(const string& opstr) const{
}

string  string::operator+(const char* ops) const{
}

string  string::operator+(const char opc) const{
}

char& string::operator[](size_t pos){
}

ostream& operator<<(ostream& os, const string& str){
    char* temp;
    temp = new char[str.length()];
    str.copy(temp);
    os << temp;
    delete [] temp;

    return os;
}

istream& operator>>(istream& is, const string& str){
    char* temp;
    int size = 256;
    temp = new char[size];
    is >> temp;
    //is.get(temp, size);
    str = temp;
    //str = string(temp);
    delete [] temp;

    return is;
}

