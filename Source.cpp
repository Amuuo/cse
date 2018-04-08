#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<fstream>
#include<array>
#include<iomanip>
#include<cctype>

using namespace std;

struct table
{
      unordered_map <string, vector<int>>  rowVec;
      unordered_map<int, string>           colIndex;
      unordered_map<string, int>           colNames;
      vector<vector<string>>               tbl;
      string                               name;
      int                                  cols;
};

table iFile(string fileName);
void searchT(vector<table>&);

int main()
{
      vector<table> tables;
      array<string,3> filenames = { "data1.txt", "data2.txt", "data3.txt" };
      for (int i = 0; i < filenames.size(); ++i)
      {
            tables.push_back(iFile(filenames[i]));
      }
      tables[0].name = "PLAYER LIST:";
      tables[1].name = "SPELLS/CLASSES:";
      tables[2].name = "SPELLS/TYPES:";
            
      char response;
      do
      {
            searchT(tables);
            cout << "\n\nAnother search? (y/n): ";
            cin >> response;
      } while (response == 'y' || response == 'Y');

      return 0;
}

void searchT(vector<table>& tmpTable)
{
      string  files[3] = {"tmpFile1.txt", "tmpFile2.txt", "tmpFile3.txt"};
      vector<table>    tmpVec;
      ofstream         oTable;
      string           search;
      char             newline = '\n';
      table tabl1, tabl2, tabl3;
      tmpVec.push_back(tabl1); tmpVec.push_back(tabl2); tmpVec.push_back(tabl3);

      int k = 0;
      cout << "Search: ";
      cin >> search;

      for (auto iter : tmpTable)
      {         
            if (iter.colNames[static_cast<const string>(search)] == 0)
            {
                  oTable.open(files[k]);
                  int g = 20;
                  cout << "\n\n\n\t" << iter.name << ":\n\n\t";


                  for (int i = 0; i < iter.cols; ++i)
                  {
                        oTable  << iter.tbl[0][i] << " ";
                        cout   << setw(g) << left << iter.tbl[0][i];
                        g -= 5;
                  }

                  cout << "\n\t================================================\n";
                  for (auto iter2 : iter.rowVec[static_cast<const string>(search)])
                  {
                        cout << "\n\t";
                        oTable << newline;
                        int g = 20;

                        //print column headers
                        for (int i = 0; i < iter.cols; ++i)
                        {
                              oTable << iter.tbl[iter2][i] << " ";
                              cout   << setw(g) << iter.tbl[iter2][i];
                              
                              g -= 5;
                        }
                  } oTable << '\n'; oTable.close(); ++k;
            }           
      }
      cout << "k = " << k;
      for (int j = 0; j < k; j++) 
      {             
            tmpVec[j] = iFile(files[j]); 
      }
      cout << "Do you want to search this query? (y/n): "; cin >> search;
      if (search == "y") searchT(tmpVec);
}

table iFile(string fileName)
{
      table tbl1; 
      ifstream inFile;
      string  tmp;
      unsigned int     row = 0;
      unsigned int     col = 0;
      bool    head = false;

      inFile.open(fileName);
      if (inFile.fail())
      {
            cout << "\n\nFile failed to open";
      }
      while (!inFile.eof())
      {
            //char* tmpC = new char;
            while (inFile.peek() != '\n' && !head)
            {
                  inFile >> tmp;
                  if (col > 2) break;
                  tbl1.colNames[tmp] = col;
                  tbl1.colIndex[col] = tmp;
                  tbl1.tbl.resize(row + 1);
                  tbl1.tbl[row].push_back(tmp);
                  tbl1.tbl[row].resize(col + 1);
                  ++col;
                  
            }
            if (!head)
            {
                  tbl1.cols = col;
                  ++row;
                  head = true;
            }
            tbl1.tbl.resize(row+1);
            col = 0;
            for(int i = 0; i < tbl1.cols; ++i)
            {              
                  inFile >> tmp;
                  tbl1.rowVec[tmp].push_back(row);
                  //tbl1.tbl[row].resize(col+1);
                  tbl1.tbl[row].push_back(tmp);
                  ++col;
            } 
            ++row;         
      }
      inFile.close();

      return tbl1;
}