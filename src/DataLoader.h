/*
 * DataLoader.h
 *
 *  Created on: Jun 15, 2021
 *      Author: root
 */

#include "common.h"

#include <iostream>
#include <fstream>

#ifndef SRC_DATALOADER_H_
#define SRC_DATALOADER_H_

class DataLoader {
public:
  DataLoader();
  virtual ~DataLoader();

  void saveData();
  void loadData(TreeData &treedata);

  const std::string& fileName() const;
  void setFileName(const std::string &fileName);

private:
  std::string m_fileName;
};

#endif /* SRC_DATALOADER_H_ */
