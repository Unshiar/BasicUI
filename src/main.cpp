/*
 * main.cpp
 *
 *  Created on: Jun 7, 2021
 *      Author: root
 */

#include "MainWindow.h"

#include <gtkmm.h>
#include <iostream>

namespace
{
MainWindow *pWindow = nullptr;
Glib::RefPtr<Gtk::Application> app;

void on_app_activate()
{

  auto builder = Gtk::Builder::create();
  try
  {
    builder->add_from_file("./ui/MainWindow.glade");
  }
  catch(const Glib::FileError& ex)
  {
    std::cerr << "FileError: " << ex.what() << std::endl;
    return;
  }
  catch(const Glib::MarkupError& ex)
  {
    std::cerr << "MarkupError: " << ex.what() << std::endl;
    return;
  }
  catch(const Gtk::BuilderError& ex)
  {
    std::cerr << "BuilderError: " << ex.what() << std::endl;
    return;
  }

  builder->get_widget_derived("MainWindow", pWindow);
  if (!pWindow)
  {
    std::cerr << "Could not get the Window" << std::endl;
    return;
  }

  pWindow->signal_hide().connect([] () { delete pWindow; });
  app->add_window(*pWindow);
  pWindow->show();
}
}

int main(int argc, char** argv)
{
  app = Gtk::Application::create("org.gtkmm.example");

  app->signal_activate().connect([] () { on_app_activate(); });

  return app->run(argc, argv);
}

