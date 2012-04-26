#ifndef _NDSL_ADVANCE_TIME_WHEEL_HPP_
#define _NDSL_ADVANCE_TIME_WHEEL_HPP_

#include <boost/intrusive/list.hpp>

namespace ndsl {

class InnerTimeWheel;

class AdvanceTimeWheel {
  public:
    class Timer {
      public:
        explicit Timer(int timespan, bool needRepeat = false);
        virtual ~Timer();
        boost::intrusive::list_member_hook
        <
        boost::intrusive::link_mode<boost::intrusive::auto_unlink>
        > timeHook_;
        virtual void callback() = 0;
        int getTimeSpan() const;
        void setTimeSpan(int timespan);
        bool isRegistered() const;
        bool needRepeat() const;
        virtual void stop();
        AdvanceTimeWheel* getAdvanceTimeWheel() const;
      private:
        InnerTimeWheel* getTimeWheel()const;
        void setAdvanceTimeWheel(AdvanceTimeWheel* wheel);
        void setTimeWheel(InnerTimeWheel* wheel);

        int idx_[5];
        int idxlen_;
        int left_[5];

        int timespan_;
        int rc_;
        bool needRepeat_;
        AdvanceTimeWheel* wh_;
        InnerTimeWheel* inner_;

        friend class AdvanceTimeWheel;
        friend class InnerTimeWheel;
        Timer(const Timer&);
        Timer& operator=(const Timer&);
    };
  public:
    AdvanceTimeWheel();
    virtual ~AdvanceTimeWheel();

    void run(int milliseconds);

    void addTimer(AdvanceTimeWheel::Timer& timer);
    size_t totalTimers() const;
  private:
    void tick();
    void move_timers(int wheelId);
    InnerTimeWheel* wheels_[5];
    Timer* timers_[4];
    friend class Timer0;
    friend class Timer1;
    friend class Timer2;
    friend class Timer3;
};

inline int AdvanceTimeWheel::Timer::getTimeSpan()const {
  return timespan_;
}

inline void AdvanceTimeWheel::Timer::setTimeSpan(int timespan) {
  timespan_ = timespan;
}

inline bool AdvanceTimeWheel::Timer::isRegistered() const {
  return timeHook_.is_linked();
}

inline bool AdvanceTimeWheel::Timer::needRepeat() const {
  return needRepeat_;
}

inline InnerTimeWheel* AdvanceTimeWheel::Timer::getTimeWheel() const {
  return inner_;
}

inline AdvanceTimeWheel* AdvanceTimeWheel::Timer::getAdvanceTimeWheel() const {
  return wh_;
}

inline void AdvanceTimeWheel::Timer::setAdvanceTimeWheel(
  AdvanceTimeWheel* wh) {
  wh_  = wh;
}

inline void AdvanceTimeWheel::Timer::setTimeWheel(
  InnerTimeWheel* inner) {
  inner_ = inner;
}


} //namespace ndsl
#endif //_NDSL_ADVANCE_TIME_WHEEL_HPP_