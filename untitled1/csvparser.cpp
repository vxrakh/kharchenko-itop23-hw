#include <iostream>
#include <string>
#include <stdexcept>
#include <fstream>
#include <vector>
#include <sstream>
#include "csvparser.h"
#include "settings.h"
using namespace std;

Row::Row(const vector<string> &row): _values(row){

}

Row::~Row(){
    _values.clear();
}

const string Row::getValue(size_t pos) const {
    if(pos < 0 || pos > _values.size()){
        throw runtime_error("Error. Try Again.");
    }else{
        return _values[pos];
    }
}

const string Row::operator[](size_t pos) const {
    if(pos < 0 || pos > _values.size()){
        throw runtime_error("Error. Try Again.");
    }else{
        return getValue(pos);
    }
}

size_t Row::size() const{
    return _values.size();
}

void Row::push(const string& pushString){
    _values.push_back(pushString);
}

bool Row::set(size_t pos, const string& value){
    if(pos < 0 || pos > _values.size()){
        throw runtime_error("Error. Try Again.");
    }else{
        _values[pos] = value;
    }
    return true;
}

CSVFile::CSVFile(const string &fileName, char sep): _fileName(fileName), _sep(sep)
{
    int min = settings::instanse()->getMin();
    int max = settings::instanse()->getMax();
    fstream file;
    file.open(fileName, fstream::in | fstream::out | fstream::app);
    if(!file){
        throw runtime_error("Error. Try again.");
    }else{
        file.seekg(0);
        string line = "";
        while(getline(file, line))
        {
            int flag = 0;
            vector<string> result;
            istringstream del(line);
            string new_string = "";
            while(getline(del, new_string, sep))
            {
                result.push_back(new_string);
                std::istringstream iss(new_string);
                double tmp = 0.0;
                if (iss >> tmp) {
                    if (min <= tmp && max >= tmp){
                        flag = 1;
                    }
                }
            }
            if (flag == 1)
            {
                Row a(result);
                _content.push_back(a);
            }
        }
    }
    file.close();
}

CSVFile::~CSVFile(){

}

void CSVFile::save(string new_string){
    fstream file;
    file.open(new_string, fstream::in | fstream::out | fstream::trunc);
    for(int i = 0; i < _content.size(); i++){
        string tempstr = "";
        for(int j = 0; j < _content[i].size(); j++){
            if (j != _content[i].size() - 1){
                tempstr = tempstr + _content[i][j] + ",";
            }else{
                tempstr = tempstr + _content[i][j];
            }
        }
        file << tempstr << endl;
    }
}

void CSVFile::NewRow(){
    vector<std::string> str;
    str.push_back("");
    _content.push_back(str);
}

void CSVFile::NewColumn(){
    auto counter = 0;
    for(auto i = 0; i < _content.size(); i++){
        auto second_counter = 0;
        for(auto j = 0; j < _content[i].size(); j++){
            second_counter++;
        }
        if(counter < second_counter){
            counter = second_counter;
        }
    }
    for(auto i = 0; i < _content.size(); i++){
        while(counter >= _content[i].size()){
            _content[i].push(" ");
        }
    }
}

Row CSVFile::getRow(size_t row) const{
    if(row < 0 || row > _content.size()){
        throw runtime_error("Error. Try Again.");
    }else{
        return _content[row];
    }
}

string CSVFile::getValue(size_t row, size_t column) const{
    if(row < 0 || row > _content.size()){
        throw runtime_error("Error. Try Again.");
    }else if(column < 0 || column > _content[0].size()){
        throw runtime_error("Error. Try Again.");
    }else{
        return _content[row][column];
    }
}

void CSVFile::setValue(size_t row, size_t column, string string){
    if(row < 0 || row > _content.size()){
        throw runtime_error("Error. Try Again.");
    }else if(column < 0 || column > _content[0].size()){
        throw runtime_error("Error. Try Again.");
    }else{
        vector<std::string> str;
        str.push_back(" ");
        for(auto i = _content.size(); i <= row; i++){
            _content.push_back(str);
        }
        for(auto i = 0; i < _content.size(); i++){
            while(column >= _content[i].size()){
                _content[i].push(" ");
            }
        }
        _content[row].set(column, string);
    }
}

size_t CSVFile::rowCount() const{
    return _content.size();
}

size_t CSVFile::columnCount() const{
    int main_counter = 0;
    for(int i = 0; i < _content.size(); i++){
        int counter = 0;
        for(int j = 0; j < _content[i].size(); j++){
            counter++;
        }
        if(counter > main_counter){
            main_counter = counter;
        }
    }
    return main_counter;
}

const string& CSVFile::getFileName() const{
    return _fileName;
}

bool CSVFile::deleteRow(size_t row){
    if(row < 0 || row > _content.size()){
        throw runtime_error("Error. Try Again.");
    }else{
        _content.erase(_content.begin() + row);
    }
    return true;
}

bool CSVFile::addRow(Row &row){
    _content.push_back(row);
    return true;
}

bool CSVFile::addRow(const vector<string>& arr){
    Row ne(arr);
    _content.push_back(arr);
    return true;
}
