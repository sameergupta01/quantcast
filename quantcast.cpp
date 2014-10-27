//
//  quantcast
//
//  Created by Sameer Gupta on 3/1/14.
//  Copyright (c) 2014 Sameer Gupta. All rights reserved.
//

#include <iostream>
#include <string.h>
#include <stack>
#include <stdlib.h>
#include <queue>
#include <list>
#include <limits.h>
#include <sstream>
#include<algorithm>
#include<stdlib.h>
#include <set>
#include <time.h>

using namespace std;



class Cell
{
private:
    bool _isSolved;
    int _row;
    int _col;
    string _orignalExp;
    double _value;
    vector<vector<Cell> > *_exSheet;
    deque<string> _tokens;
    deque<double> _terms;
    
public:
    Cell(vector<vector<Cell> > *exSheet,
         int row, int col, const string &exp)
    {
        _exSheet = exSheet;
        _row = row;
        _col = col;
        _orignalExp = exp;
        _isSolved = false;
    }
    
    double GetFinalValue() { return _isSolved ? _value : solveExp(); }
    
    bool IsValue(string s)
    {
        int i=0;
        while(s[i] != '\0')
        {
            if(s[i] < '0' || s[i] > '9')
                return false;
            i++;
        }
        return true;
    }
    
    bool IsOperator(string s)
    {
        return s.length() == 1 &&
        (s[0] == '+' || s[0] == '-' ||
         s[0] == '*' || s[0] == '/');
    }
    
    double RPNCalc(string &token)
    {
        //is a value
        if (IsValue(token))
            return atof(token.c_str());
        //is an operator
        if (IsOperator(token))
        {
            double val1 = _terms.back();
            _terms.pop_back();
            double val2 = _terms.back();
            _terms.pop_back();
            
            switch (token[0]) {
                case '*': return val1 * val2;
                case '/': return val1 / val2;
                case '+': return val1 + val2;
                case '-': return val1 - val2;
            }
        }
        //should be a reference
        else
        {
            int row = token[0] - 'A';
            int col = atoi(token.substr(1, token.length() - 1).c_str()) - 1;
            if(row < 0 || row > 26 || col < 0)
                return -1;
            return (*_exSheet)[row][col].GetFinalValue();
        }
        return -1;
    }
    
    double solveExp()
    {
        _isSolved = true;
        
        string item;
        if(_orignalExp == "")
            return 0;
        stringstream ss(_orignalExp);
        while (getline(ss, item, ' '))
            _tokens.push_back(item);
        
        while (_tokens.size() > 0 || _terms.size() != 1) {
            
            _terms.push_back(RPNCalc(_tokens.front()));
            _tokens.pop_front();
            
        }
        //evaluate the final value
        double ret = _terms.front();
        _terms.pop_front();
        _value = ret;
        return ret;
        
    }
    
    
};


int main(int argc, const char * argv[])
{
    int rows = 0;
    int cols = 0;
    cin>>cols>>rows;
    
    // create excel sheet
    vector<vector<Cell> > excelSheet;
    for (int i = 0; i < rows; i++) {
        excelSheet.push_back(vector<Cell>());
        for (int j = 0; j < cols; j++) {
            string s;
            getline(cin,s);
            Cell val = Cell(&excelSheet, i, j, s);
            excelSheet[i].push_back(val);
        }
    }
    
    cout << cols << " " << rows << endl;
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
            printf("%.5f\n", excelSheet[i][j].GetFinalValue());
        }
    }
    
    return 0;
}







