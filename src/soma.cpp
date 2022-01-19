#include <morphio/section.h>
#include <morphio/soma.h>
#include <morphio/vector_types.h>

#include "shared_utils.hpp"

namespace morphio {


Soma::Soma(const Property::Properties& properties)
    : soma_type_(properties._cellLevel._somaType),
      properties_(properties._somaLevel) {}


Soma::Soma(const Property::PointLevel& point_properties)
    : properties_(point_properties) {}


std::vector<Point>& Soma::points() noexcept {
    return properties_._points;
}


const std::vector<Point>& Soma::points() const noexcept {
    return properties_._points;
}


std::vector<morphio::floatType>& Soma::diameters() noexcept {
    return properties_._diameters;
}


const std::vector<morphio::floatType>& Soma::diameters() const noexcept {
    return properties_._diameters;
}


SomaType Soma::type() const noexcept {
    return soma_type_;
}


Point Soma::center() const {
    return centerOfGravity(points());
}


floatType Soma::volume() const {
    switch (soma_type_) {
    case SOMA_NEUROMORPHO_THREE_POINT_CYLINDERS: {
        floatType radius = diameters()[0] / 2;
        return 4 * morphio::PI * radius * radius;
    }

    case SOMA_SINGLE_POINT:
    case SOMA_CYLINDERS:
    case SOMA_SIMPLE_CONTOUR:
    case SOMA_UNDEFINED:
    default:
        throw;
    }
}


floatType Soma::surface() const {
    return _somaSurface<std::vector<morphio::floatType>, std::vector<Point>>(type(),
                                                                             diameters(),
                                                                             points());
}


floatType Soma::maxDistance() const {
    return maxDistanceToCenterOfGravity(properties_._points);
}


std::ostream& operator<<(std::ostream& os, const Soma& soma) {
    os << dumpPoints(soma.points());
    return os;
}


std::ostream& operator<<(std::ostream& os, const std::shared_ptr<Soma>& somaPtr) {
    os << *somaPtr;
    return os;
}
}  // namespace morphio
