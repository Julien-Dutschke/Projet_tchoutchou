#ifndef RAIL_HPP
#define RAIL_HPP

# include <string>
# include "node.hpp"

class Rail
{
private:
    const Node* _from;
    const Node* _to;

    double _lengthKm;
    double _speedLimitKmh;

public:
    Rail(const Node* from,
         const Node* to,
         double lengthKm,
         double speedLimitKmh) : _from(from),
								 _to(to),
								 _lengthKm(lengthKm),
								 _speedLimitKmh(speedLimitKmh) {}

    // Getters
    const Node* getFrom() const { return _from; }
    const Node* getTo() const { return _to; }

    double getLengthKm() const { return _lengthKm; }
    double getSpeedLimitKmh() const { return _speedLimitKmh; }
};

#endif // RAIL_HPP
