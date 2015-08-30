#pragma once

#include <jank/translate/cell/cell.hpp>
#include <jank/interpret/cell/cell.hpp>
#include <jank/interpret/environment/scope.hpp>

namespace jank
{
  namespace interpret
  {
    namespace detail
    {
      cell::cell function_call
      (
        std::shared_ptr<environment::scope> const&,
        translate::cell::function_call const&,
        std::function
        <
          cell::cell
          (
            std::shared_ptr<environment::scope> const&,
            translate::cell::function_body const&
          )
        > const &processor
      );

      cell::cell function_call
      (
        std::shared_ptr<environment::scope> const&,
        translate::cell::function_call const&
      );
    }
  }
}
