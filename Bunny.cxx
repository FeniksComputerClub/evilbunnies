#include "Bunny.h"
#include <thread>
#include <chrono>

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

bool Bunny::on_draw(Cairo::RefPtr<Cairo::Context> const& cr, time_point const& /*time*/)
{
  
    // bunny
    //cr->set_source_rgb(1.0, color, color);
    cr->arc(m_x, m_y,m_radius, 0.0, 2 * M_PI);
    cr->fill_preserve();
  return true;
}
