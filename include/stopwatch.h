#ifndef STOPWATCH_H
#define STOPWATCH_H
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>


class stopwatch
{
    public:
        stopwatch();
        virtual ~stopwatch();

        void start();
        void restart();
        void stop();
        void reset();

        long get_elapse_milliseconds();
        boost::posix_time::millisec_posix_time_system_config::time_duration_type get_elapse();
    protected:
    private:

    boost::posix_time::ptime begin,end;
};

#endif // STOPWATCH_H
