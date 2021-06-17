/*
 * ModelColumns.h
 *
 *  Created on: Jun 12, 2021
 *      Author: root
 */

#ifndef RELEASE_MODELCOLUMNS_H_
#define RELEASE_MODELCOLUMNS_H_

#include <gtkmm.h>

class ModelColumns : public Gtk::TreeModel::ColumnRecord {
public:
  ModelColumns();
  virtual ~ModelColumns();

  Gtk::TreeModelColumn<bool> m_col_state;
  Gtk::TreeModelColumn<Glib::ustring> m_col_name;
};

#endif /* RELEASE_MODELCOLUMNS_H_ */
