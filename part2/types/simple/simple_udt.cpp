#include <iostream>
#include <iomanip>
#include <boost/make_shared.hpp>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include "gen-cpp/simple_udt_types.h"

using namespace apache::thrift::transport;
using namespace apache::thrift::protocol;

int main() {
    auto trans = boost::make_shared<TMemoryBuffer>(1024);
    auto proto = boost::make_shared<TBinaryProtocol>(trans);

    EarthRelPosition ep;
    ep.latitude = 0.0;
    ep.longitude = 180.0;
    ep.elevation = 42164.0;

    proto->getTransport()->open();
    ep.write(proto.get());
    proto->getTransport()->flush();

    std::cout << "Wrote Position: " << std::setprecision(2) << std::fixed
              << std::setw(8) << ep.latitude
              << ", " << std::setw(8) << ep.longitude
              << ", " << std::setw(8) << ep.elevation << std::endl;

    EarthRelPosition epRead;
    epRead.read(proto.get());
    proto->getTransport()->close();

    std::cout << "Read  Position: " << std::setprecision(2) << std::fixed
              << std::setw(8) << epRead.latitude
              << ", " << std::setw(8) << epRead.longitude 
              << ", " << std::setw(8) << epRead.elevation << std::endl;
}

