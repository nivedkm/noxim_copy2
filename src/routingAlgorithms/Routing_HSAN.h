#ifndef __NOXIM_ROUTING_HSAN_H__
#define __NOXIM_ROUTING_HSAN_H__

#include "RoutingAlgorithm.h"

class RoutingAlgorithm_HSAN : public RoutingAlgorithm {
public:
    std::vector<int> route(Router *router, const RouteData &routeData) override;
};

#endif
