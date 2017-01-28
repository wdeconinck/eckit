/*
 * (C) Copyright 1996-2017 ECMWF.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 * In applying this licence, ECMWF does not waive the privileges and immunities
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

#include "eckit/log/MessageTarget.h"
#include "eckit/runtime/Monitor.h"

namespace eckit {

//----------------------------------------------------------------------------------------------------------------------

MessageTarget::MessageTarget() {
}

void MessageTarget::line(const char* line) {
    Monitor::instance().message(line);
}

void MessageTarget::print(std::ostream& s) const
{
    s << "MessageTarget()";
}

//----------------------------------------------------------------------------------------------------------------------

} // namespace eckit
