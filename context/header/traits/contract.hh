#pragma once

namespace flp::trait {

// 'contract group'?
struct ErrorContract {
  enum class Category : uint8_t {
    verbose,
    strict,
    permissive,
  };

  // capture file location?
  struct Interface {
    virtual ~Interface() noexcept = default;

    [[nodiscard]]
    virtual bool is_active() const = 0;
    virtual void report_violation() const                 = 0;
    virtual void report_violation(std::string_view) const = 0;
  };

  template<typename Type>
  struct Implementation : Interface {
    Type contract;

    [[nodiscard]]
    bool is_active() const override {
      return contract.is_active();
    }

    void report_violation() const override {
      contract.report_violation();
    }

    void report_violation(std::string_view message) const override {
      contract.report_violation(message);
    }
  };

  ErrorContract()                         = default;
  ErrorContract(const ErrorContract&)     = default;
  ErrorContract(ErrorContract&&) noexcept = default;

  ErrorContract& operator=(const ErrorContract&)     = default;
  ErrorContract& operator=(ErrorContract&&) noexcept = default;

  ~ErrorContract() = default;

  template<typename Type>
    requires(not std::same_as<Type, ErrorContract>)
  explicit ErrorContract(Type&& logger)
    : implementation(std::make_shared<Implementation<Type>>(std::forward<Type>(logger))) {}

  template<typename Type>
  ErrorContract& operator=(Type&& logger) {
    implementation = std::make_shared<Implementation<Type>>(std::forward<Type>(logger));

    return *this;
  }

  template<typename Logger, typename... Args>
  void emplace(Args&&... args) {
    implementation = std::make_shared<Implementation<Logger>>(std::forward<Args>(args)...);
  }

  [[nodiscard]]
  bool is_active() const {
    return implementation->is_active();
  }

  void report_violation() const {
    implementation->report_violation();
  }

  void report_violation(std::string_view message) const {
    implementation->report_violation(message);
  }

private:
  std::shared_ptr<Interface> implementation;
};

// default
// type safety
// bounds safety
// null safety
// testing
// static-checks

using ContractViolationHandler = std::function<void()>;

}
