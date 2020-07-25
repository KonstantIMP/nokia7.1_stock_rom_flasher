#ifndef GTKMM_LOG_HPP
#define GTKMM_LOG_HPP

#include <gtkmm.h>

#include "log.hpp"

namespace KonstantIMP {
    class gtkmm_log : public KonstantIMP::log {
    public:
        gtkmm_log(std::ostream *, Gtk::TextView *);

        virtual void make_record(const std::string &);

    protected:
        Gtk::TextView * log_viewer;
    };
}

#endif // GTKMM_LOG_HPP
