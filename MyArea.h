#pragma once

#include <gtkmm/drawingarea.h>
#include "Bunny.h"

class MyArea : public Gtk::DrawingArea
{
  private:
    std::vector<boost::intrusive_ptr<Bunny>> m_bunnies;

  public:
    static int constexpr width = 600;
    static int constexpr height = 600;

    MyArea();
    virtual ~MyArea();
    void add_bunny(boost::intrusive_ptr<Bunny>& bunny_to_add);

  protected:
    // Override default signal handler:
    bool on_draw(Cairo::RefPtr<Cairo::Context> const& cr) override;
};
