#include "sys.h"
#include "Bunny.h"
#include <thread>
#include <chrono>

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

bool Bunny::on_draw(Cairo::RefPtr<Cairo::Context> const& cr, time_point const& /*time*/)
{
  cr->set_source(m_pattern);
  cr->arc(m_x, m_y, m_radius, 0.0, 2 * M_PI);
  cr->fill_preserve();
  
  //move bunny
  m_x += 0.01;
  return true;
}
