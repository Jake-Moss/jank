#pragma once

#include <vector>
#include <memory>

#include <jank/translate/cell/cell.hpp>

namespace jank
{
  namespace translate
  {
    namespace function
    {
      namespace ret
      {
        /* null */
        cell::cell make_implicit(cell::function_body const &body);

        /* Builds an implicit return statement from the last function call. */
        std::experimental::optional<cell::cell>
        make_implicit_from_call(cell::function_body const &body);
      }
    }
  }
}
