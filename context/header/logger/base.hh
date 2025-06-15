#pragma once

namespace flp {

struct LoggerBase {
  enum class Noise {
    Noisy,
    Quiet,
  };

  enum class Severity {
    trace,
    info,
    warn,
    error,
  };

  virtual void log(Severity, Noise) = 0;
};

}
