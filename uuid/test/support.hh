#pragma once

#include <uuid.hh>

#include <catch2/catch_all.hpp>
#include <rapidcheck.h>
#include <rapidcheck/seq/Operations.h>
#include <rapidcheck/catch.h>

// template<>
// struct rc::Arbitrary<flp::GUID> {
//   static Gen<flp::GUID> arbitrary() {
//     return rc::gen::construct<flp::GUID>(
//       rc::gen::arbitrary<uint64_t>(),
//       rc::gen::arbitrary<uint64_t>(),
//     );
//   }
// };
// 
// template<>
// struct rc::Arbitrary<flp::UUIDv1> {
//   static Gen<flp::UUIDv1> arbitrary() {
//     return rc::gen::construct<flp::UUIDv1>(
//       rc::gen::arbitrary<uint64_t>(),
//       rc::gen::arbitrary<uint64_t>(),
//     );
//   }
// };
// 
// template<>
// struct rc::Arbitrary<flp::UUIDv2> {
//   static Gen<flp::UUIDv2> arbitrary() {
//     return rc::gen::construct<flp::UUIDv2>(
//       rc::gen::arbitrary<uint64_t>(),
//       rc::gen::arbitrary<uint64_t>(),
//     );
//   }
// };
// 
// template<>
// struct rc::Arbitrary<flp::UUIDv3> {
//   static Gen<flp::UUIDv3> arbitrary() {
//     return rc::gen::construct<flp::UUIDv3>(
//       rc::gen::arbitrary<uint64_t>(),
//       rc::gen::arbitrary<uint64_t>(),
//     );
//   }
// };
// 
// template<>
// struct rc::Arbitrary<flp::UUIDv4> {
//   static Gen<flp::UUIDv4> arbitrary() {
//     return rc::gen::construct<flp::UUIDv4>(
//       rc::gen::arbitrary<uint64_t>(),
//       rc::gen::arbitrary<uint64_t>(),
//     );
//   }
// };
// 
// template<>
// struct rc::Arbitrary<flp::UUIDv5> {
//   static Gen<flp::UUIDv5> arbitrary() {
//     return rc::gen::construct<flp::UUIDv5>(
//       rc::gen::arbitrary<uint64_t>(),
//       rc::gen::arbitrary<uint64_t>(),
//     );
//   }
// };
// 
// template<>
// struct rc::Arbitrary<flp::UUIDv7> {
//   static Gen<flp::UUIDv7> arbitrary() {
//     return rc::gen::construct<flp::UUIDv7>(
//       rc::gen::arbitrary<uint64_t>(),
//       rc::gen::arbitrary<uint64_t>(),
//     );
//   }
// };
