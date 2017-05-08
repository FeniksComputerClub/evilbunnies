#pragma once

#include <gtkmm/drawingarea.h>
#include "Bunny.h"

class MyArea : public Gtk::DrawingArea
{
  private:
    Bunny m_bunny;

  public:
    static int constexpr width = 600;
    static int constexpr height = 600;

    MyArea();
    virtual ~MyArea();

  protected:
    // Override default signal handler:
    bool on_draw(Cairo::RefPtr<Cairo::Context> const& cr) override;
};
