#include <iostream>

#include "connector/omicronConnectorClient.h"
#include "sensor/vicon_eventlogger.h"
#include "sensor/vicon_listener.h"
#include "utils/logger.h"

int main(int /* argc */, char* argv[])
{
    ipme::utils::Logger::init(argv[0]);

    INFO() << "Starting listener";

    ipme::sensor::Vicon_listener listener{
        std::make_unique<ipme::sensor::Vicon_eventlogger>()};
    omicronConnector::OmicronConnectorClient client(&listener);

    client.connect("131.193.77.108", 28000);

    while(true) {
        client.poll();
    }
}
