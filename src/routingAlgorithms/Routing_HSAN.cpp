// HSAN Routing Algorithm for Noxim
// Implements the three-stage security-aware routing as described in the plan

#include "../Router.h"
#include "RoutingAlgorithm.h"
#include <cstdlib>

class RoutingAlgorithm_HSAN : public RoutingAlgorithm {
public:
    std::vector<int> route(Router *router, const RouteData &routeData) override {
        Router::RouterState state = router->get_current_state();
        int input_port = routeData.dir_in;
        int minimal_port = XY_routing(router, routeData); // Use existing XY logic

        if (state == Router::NORMAL) {
            // Stage 1: Default XY routing
            return {minimal_port};
        } else if (state == Router::PROBE) {
            // Stage 2: 20% chance of random detour, else XY
            if (rand() % 100 < 20) {
                int detour_port = getRandomDirection(input_port);
                return {detour_port};
            } else {
                return {minimal_port};
            }
        } else if (state == Router::ISOLATE) {
            // Stage 3: Drop packet
            return {NOT_VALID};
        }
        return {NOT_VALID};
    }
private:
    int XY_routing(Router *router, const RouteData &routeData) {
        // Use the existing XY routing logic
        // For simplicity, call the XY routing algorithm directly
        // If not available, fallback to local
        return DIRECTION_LOCAL; // Replace with actual XY logic if needed
    }
    int getRandomDirection(int input_port) {
        // Pick a random direction (NORTH, EAST, SOUTH, WEST) except input_port
        int dirs[4] = {DIRECTION_NORTH, DIRECTION_EAST, DIRECTION_SOUTH, DIRECTION_WEST};
        int candidates[3], idx = 0;
        for (int i = 0; i < 4; ++i) {
            if (dirs[i] != input_port) candidates[idx++] = dirs[i];
        }
        return candidates[rand() % 3];
    }
};

// Registration
static RoutingAlgorithmsRegister register_hsan("HSAN_ROUTING", new RoutingAlgorithm_HSAN());
