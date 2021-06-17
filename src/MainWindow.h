/*
 * MainWindow.h
 *
 *  Created on: Jun 8, 2021
 *      Author: root
 */

#ifndef SRC_MAINWINDOW_H_
#define SRC_MAINWINDOW_H_

#include "ModelColumns.h"
#include "DataLoader.h"

#include <gtkmm.h>
#include "common.h"

class MainWindow : public Gtk::Window {
public:
  MainWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);
  virtual ~MainWindow();

protected:
  void on_loadButton_clicked();
  void on_cellToggle_toggled(const Glib::ustring& path);
  void on_cellText_edited(const Glib::ustring& path, const Glib::ustring& new_text);

  ModelColumns m_Columns;
  Glib::RefPtr<Gtk::TreeStore> m_treeModel;

  Glib::RefPtr<Gtk::Builder> m_builder;
  Gtk::Button *m_loadButton;
  Gtk::TreeView *m_treeView;
  Gtk::TreeSelection *m_treeViewSelect;
  Gtk::TreeViewColumn *m_treeViewFirstCol;
  Gtk::CellRendererToggle *m_CellToggle;
  Gtk::CellRendererText *m_CellText;

private:
  bool isUILoaded();
  void connectSignals();
  void printTree(const Gtk::TreeModel::Children &children);

  DataLoader m_dataloader;
  TreeData m_treeData;
};

#endif /* SRC_MAINWINDOW_H_ */
