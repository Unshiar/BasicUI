/*
 * MainWindow.cpp
 *
 *  Created on: Jun 8, 2021
 *      Author: root
 */

#include "MainWindow.h"

#include <iostream>

MainWindow::MainWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder) :
Gtk::Window(cobject),
m_builder(builder),
m_loadButton(nullptr),
m_treeView(nullptr),
m_treeViewSelect(nullptr),
m_treeViewFirstCol(nullptr),
m_CellToggle(nullptr),
m_CellText(nullptr)
{

  if(isUILoaded()) {
    connectSignals();
  }
}

MainWindow::~MainWindow() {

}

void MainWindow::on_loadButton_clicked() {

  Glib::ustring optionPrefix = "Option_";
  Glib::ustring path = "";

  auto row = *(m_treeModel->append());
  path = m_treeModel->get_path(row).to_string();
  row[m_Columns.m_col_state] = true;
  row[m_Columns.m_col_name] = optionPrefix + path;
  m_treeData.insert({path, {true, optionPrefix + path}});

  auto childrow = *(m_treeModel->append(row.children()));
  path = m_treeModel->get_path(childrow).to_string();
  childrow[m_Columns.m_col_state] = false;
  childrow[m_Columns.m_col_name] = optionPrefix + path;
  m_treeData.insert({path, {true, optionPrefix + path}});

  childrow = *(m_treeModel->append(row.children()));
  path = m_treeModel->get_path(childrow).to_string();
  childrow[m_Columns.m_col_state] = true;
  childrow[m_Columns.m_col_name] = optionPrefix + path;
  m_treeData.insert({path, {true, optionPrefix + path}});

  row = *(m_treeModel->append());
  path = m_treeModel->get_path(row).to_string();
  row[m_Columns.m_col_state] = false;
  row[m_Columns.m_col_name] = optionPrefix + path;
  m_treeData.insert({path, {true, optionPrefix + path}});

  childrow = *(m_treeModel->append(row.children()));
  path = m_treeModel->get_path(childrow).to_string();
  childrow[m_Columns.m_col_state] = true;
  childrow[m_Columns.m_col_name] = optionPrefix + path;
  m_treeData.insert({path, {true, optionPrefix + path}});

  childrow = *(m_treeModel->append(row.children()));
  path = m_treeModel->get_path(childrow).to_string();
  childrow[m_Columns.m_col_state] = true;
  childrow[m_Columns.m_col_name] = optionPrefix + path;
  m_treeData.insert({path, {true, optionPrefix + path}});

  childrow = *(m_treeModel->append(row.children()));
  path = m_treeModel->get_path(childrow).to_string();
  childrow[m_Columns.m_col_state] = false;
  childrow[m_Columns.m_col_name] = optionPrefix + path;
  m_treeData.insert({path, {true, optionPrefix + path}});

  row = *(m_treeModel->append());
  path = m_treeModel->get_path(row).to_string();
  row[m_Columns.m_col_state] = false;
  row[m_Columns.m_col_name] = optionPrefix + path;
  m_treeData.insert({path, {true, optionPrefix + path}});

  childrow = *(m_treeModel->append(row.children()));
  path = m_treeModel->get_path(childrow).to_string();
  childrow[m_Columns.m_col_state] = true;
  childrow[m_Columns.m_col_name] = optionPrefix + path;
  m_treeData.insert({path, {true, optionPrefix + path}});

  //
  TreeData treeData;
  m_dataloader.setFileName("data.txt");
  m_dataloader.loadData(treeData);

  for(auto treeElement : treeData) {
    std::cout << treeElement.first << " " << treeElement.second.first << " " <<  treeElement.second.second << std::endl;
  }
}

bool MainWindow::isUILoaded() {

  m_builder->get_widget("loadButton", m_loadButton);
  if (m_loadButton == nullptr) {
    return false;
  }

  m_builder->get_widget("treeView", m_treeView);
  if (m_treeView) {
    m_treeModel = Gtk::TreeStore::create(m_Columns);

    m_treeView->set_model(m_treeModel);
    m_treeViewSelect = m_treeView->get_selection().get();

    int colNum = 0;
    if((m_treeViewFirstCol = m_treeView->get_column(colNum)) == nullptr) {
      std::cerr << "Can't get column number " << colNum << std::endl;
      return false;
    }

    m_CellToggle = dynamic_cast<Gtk::CellRendererToggle*>(m_treeViewFirstCol->get_cells()[0]);
    m_CellText = dynamic_cast<Gtk::CellRendererText*>(m_treeViewFirstCol->get_cells()[1]);
    m_CellText->property_editable() = true;
  } else {
    return false;
  }

  return true;
}

void MainWindow::on_cellToggle_toggled(const Glib::ustring& path) {

  const auto iter = m_treeModel->get_iter(path);
  if(iter)
  {
    const auto row = *iter;
    row[m_Columns.m_col_state] = !row[m_Columns.m_col_state];
  }
}

void MainWindow::on_cellText_edited(const Glib::ustring &path,
    const Glib::ustring &new_text) {

  const auto iter = m_treeModel->get_iter(path);
  if(iter)
  {
    const auto row = *iter;
    row[m_Columns.m_col_name] = new_text;
  }
}

void MainWindow::connectSignals() {

  m_loadButton->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_loadButton_clicked));
  m_CellToggle->signal_toggled().connect(sigc::mem_fun(*this, &MainWindow::on_cellToggle_toggled));
  m_CellText->signal_edited().connect(sigc::mem_fun(*this, &MainWindow::on_cellText_edited));
}

void MainWindow::printTree(const Gtk::TreeModel::Children &children) {

  for (auto iter = children.begin(), end = children.end(); iter != end; ++iter) {
    auto node = *iter;
    std::cout << m_treeModel->get_path(node).to_string() << std::endl;
    printTree(node->children());
  }
}
