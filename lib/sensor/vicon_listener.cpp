#include "vicon_listener.h"

#include <sstream>

#include "utils/logger.h"

namespace ipme {
namespace sensor {
Vicon_listener::Vicon_listener(std::shared_ptr<Vicon_datahandler> handler)
    : handler_{std::move(handler)}
{
}

void Vicon_listener::onEvent(const omicronConnector::EventData& event)
{
    switch(event.type) {
    case oc::EventData::Trace:
        handler_->handle_trace(event);
        break;

    case oc::EventData::Untrace:
        handler_->handle_untrace(event);
        break;

    case oc::EventData::Update:
        handler_->handle_update(event);
        break;

    case oc::EventData::Down:
        handler_->handle_down(event);
        break;

    case oc::EventData::Up:
        handler_->handle_up(event);
        break;

    default:
        std::stringstream ss;
        ss << "Unknown event of type: " << event.type << " received";
        ERROR() << ss.str();
    }

    ++event_count_;
}

} // namespace sensor
} // namespace ipme
