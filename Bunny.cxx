#include "sys.h"
#include "Bunny.h"
#include "MyArea.h"
#include <thread>
#include <chrono>
#include <math.h>

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

bool Bunny::on_draw(Cairo::RefPtr<Cairo::Context> const& cr, time_point const& /*time*/)
{
  //lock pos
  pos_t::wat pos_w(pos);

  cr->set_source(m_pattern);
  cr->arc(pos_w->getx(), pos_w->gety(), m_radius, 0.0, 2 * M_PI);
  cr->close_path();
  cr->fill_preserve();
  return true;
}

char const* Bunny::state_str_impl(state_type run_state) const
{
  switch(run_state)
  {
    AI_CASE_RETURN(start);
    AI_CASE_RETURN(change);
    AI_CASE_RETURN(move);
    AI_CASE_RETURN(done);
  }
  return "UNKNOWN";
}

void Bunny::multiplex_impl(state_type run_state)
{
  //lock pos
  switch(run_state)
  {
    case start:
    {
      pos_t::wat pos_w(pos);
      pos_w->setx((rand() % 100 + 1) / 100.0);
      pos_w->sety((rand() % 100 + 1) / 100.0);
      set_state(change);
      //fallthrough
    }
    case change:
    {
      double direction = ((rand() % 360) / 360.0) * 2 * M_PI;
      m_deltax = sin(direction) * m_speed;
      m_deltay = cos(direction) * m_speed;
      set_state(move);
      //fallthrough
    }
    case move:
    {
      double move_x = m_deltax * m_speed;
      double move_y = m_deltay * m_speed;
      bool inside;
      {
        pos_t::wat pos_w(pos);
        pos_w->addx(move_x);
        pos_w->addy(move_y);
        inside = is_in(pos_w);
      }
      if (!inside)
      {
        {
          pos_t::wat pos_w(pos);
          pos_w->clamp(m_radius);
        }
        set_state(change);
        yield();
      }
      else
        wait(1);
      break;
    }
    case done:
      finish();
      break;
  }
  m_area.queue_draw();
}
