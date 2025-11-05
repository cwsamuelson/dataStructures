#pragma once

#include "uuid/guid.hh"
#include "uuid/v1.hh"
#include "uuid/v4.hh"
#include "uuid/v7.hh"

namespace flp {

using GUID = UUID::GUID;
using UUIDv1 = UUID::V1;
using UUIDv2 = UUID::V2;
using UUIDv3 = UUID::V3;
using UUIDv4 = UUID::V4;
using UUIDv5 = UUID::V5;
using UUIDv7 = UUID::V7;
using UUIDv4_1 = UUIDv2;
using UUIDv4_2 = GUID;
using UUID = UUIDv4; // I think for 'reasons' v4 is typically used

} // namespace flp
