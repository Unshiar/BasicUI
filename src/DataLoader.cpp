/*
 * DataLoader.cpp
 *
 *  Created on: Jun 15, 2021
 *      Author: root
 */

#include "DataLoader.h"

DataLoader::DataLoader() :
  m_fileName("")
{

}

DataLoader::~DataLoader() {

}

void DataLoader::saveData() {

//  std::ofstream myfile;
//  myfile.open(m_fileName);
//  myfile << "123";
//  myfile.close();
}

const std::string& DataLoader::fileName() const {

  return m_fileName;
}

void DataLoader::loadData(TreeData &treedata) {

  bool state = false;
  std::string path = "";
  std::string name = "";
  std::streampos pos = 0;

  std::ifstream myfile;
  myfile.open(m_fileName);

  while(!myfile.eof()) {

    std::getline (myfile, path, ';');
    myfile >> state;
    pos = myfile.tellg();
    pos += 1;
    myfile.seekg(pos);
    std::getline (myfile, name);

    if(myfile.fail()) {
      //TODO(sergeyr) error message
      break;
    }

    treedata.insert({path, {state, name}});
  }

  myfile.close();
}

void DataLoader::setFileName(const std::string &fileName) {

  m_fileName = fileName;
}
