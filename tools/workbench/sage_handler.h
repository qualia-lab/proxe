#ifndef IPME_WB_SAGE_HANDLER_H
#define IPME_WB_SAGE_HANDLER_H

#include <cstdlib>
#include <memory>
#include <string_view>
#include <thread>

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>

#include "state_machine.h"

namespace ipme {
namespace wb {
class Sage_handler {
public:
    Sage_handler();
    ~Sage_handler();

    bool connect(std::string_view host, std::string_view port);
    void start();

    void set_state_machine(std::shared_ptr<State_machine> state_machine);

private:
    void internal_start();

    boost::asio::io_context ioc_;
    boost::asio::ip::tcp::resolver resolver_;
    boost::beast::websocket::stream<boost::asio::ip::tcp::socket> wstream_;
    std::unique_ptr<std::thread> sage_thread_;

    std::shared_ptr<State_machine> state_machine_;
};

} // namespace wb
} // namespace ipme

#endif // IPME_WB_SAGE_HANDLER_H