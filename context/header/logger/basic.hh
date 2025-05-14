#pragma once

namespace flp {

struct STDLogger : LoggerBase {
  void log(Severity, Noise) override {
  }
};

}
