#pragma once

#include <gtkmm/drawingarea.h>

class MyArea : public Gtk::DrawingArea
{
  public:
    static int const width = 800;
    static int const height = 800;

    MyArea();
    virtual ~MyArea();

  protected:
    // Override default signal handler:
    bool on_draw(Cairo::RefPtr<Cairo::Context> const& cr) override;
};
