#pragma once

#include <stdexcept>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class Row
{

    vector<string> _values;

public:

    Row(const vector<string> &row);
    ~Row();

    const string getValue(size_t pos) const;
    const string operator[](size_t pos) const;

    size_t size() const;


    void push(const string& pushString);

    bool set(size_t pos, const string& value);
};

class CSVFile
{

    string _fileName;
    const char _sep;
    vector<Row> _content;

public:

    CSVFile(const string &fileName, char sep = ',');

    ~CSVFile();


    Row getRow(size_t row) const;

    string getValue(size_t row, size_t column) const;

    void setValue(size_t row, size_t column, string string);

    size_t rowCount() const;

    size_t columnCount() const;

    void save(string new_string);
    void NewRow();
    void NewColumn();


    const string& getFileName() const;

    bool deleteRow(size_t row);
    bool addRow(Row &row);
    bool addRow(const vector<string>& arr);

};
