#include "stopwatch.h"

stopwatch::stopwatch()
{
    //ctor
}

stopwatch::~stopwatch()
{
    //dtor
}

void stopwatch::start()
{
    begin = boost::posix_time::microsec_clock::universal_time();
}

void stopwatch::restart()
{
    begin = boost::posix_time::microsec_clock::universal_time();
}

void stopwatch::stop()
{
    end = boost::posix_time::microsec_clock::universal_time();
}

void stopwatch::reset()
{
    begin=end;
}

long stopwatch::get_elapse_milliseconds()
{
    return get_elapse().total_milliseconds();
}

boost::posix_time::millisec_posix_time_system_config::time_duration_type stopwatch::get_elapse()
{
    return end-begin;
}
