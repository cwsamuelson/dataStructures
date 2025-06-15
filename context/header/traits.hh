#pragma once

// type erasure is probably not great for logger performance
// this can be important if lots of logs are made
// that's not an unreasonable expectation either

#include <traits/allocator.hh>
#include <traits/contract.hh>
#include <traits/logger.hh>
