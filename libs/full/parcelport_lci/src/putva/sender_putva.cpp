//  Copyright (c) 2007-2013 Hartmut Kaiser
//  Copyright (c) 2014-2015 Thomas Heller
//  Copyright (c)      2020 Google
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/config.hpp>

#if defined(HPX_HAVE_NETWORKING) && defined(HPX_HAVE_PARCELPORT_LCI)

#include <hpx/modules/lci_base.hpp>
#include <hpx/parcelport_lci/locality.hpp>
#include <hpx/parcelport_lci/putva/sender_putva.hpp>
#include <hpx/parcelport_lci/receiver_base.hpp>
#include "hpx/parcelport_lci/putva/sender_connection_putva.hpp"

#include <hpx/assert.hpp>
#include <memory>

namespace hpx::parcelset::policies::lci {
    sender_putva::connection_ptr sender_putva::create_connection(
        int dest, parcelset::parcelport* pp)
    {
        return std::make_shared<sender_connection_putva>(dest, pp);
    }
}    // namespace hpx::parcelset::policies::lci

#endif
