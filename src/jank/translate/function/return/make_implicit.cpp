#include <algorithm>

#include <jank/translate/function/return/make_implicit.hpp>
#include <jank/translate/environment/special/return_statement.hpp>
#include <jank/translate/environment/builtin/type/primitive.hpp>
#include <jank/translate/expect/type.hpp>

namespace jank
{
  namespace translate
  {
    namespace function
    {
      namespace ret
      {
        cell::cell make_implicit(cell::function_body const &body)
        {
          return environment::special::return_statement
          (
            parse::cell::list{ { parse::cell::ident{ "return" } } },
            body
          );
        }

        /* Builds an implicit return statement from the last function call. */
        std::experimental::optional<cell::cell>
        make_implicit_from_call(cell::function_body const &body)
        {
          auto const last_function
          (
            std::find_if
            (
              body.data.cells.rbegin(), body.data.cells.rend(),
              [](auto const &c)
              {
                return expect::is<cell::type::function_call>(c) ||
                       expect::is<cell::type::native_function_call>(c);
              }
            )
          );

          /* The function needs to be the last cell in the body. */
          if(std::next(last_function) != body.data.cells.rend())
          { return {}; }

          auto const native_opt
          (
            expect::optional_cast<cell::type::native_function_call>
            (*last_function)
          );
          auto const non_native_opt
          (
            expect::optional_cast<cell::type::function_call>
            (*last_function)
          );
          auto const match
          (
            [&](auto const &opt) -> std::experimental::optional<cell::cell>
            {
              if
              (
                !opt ||
                opt.value().data.definition.return_type !=
                body.data.return_type
              )
              { return {}; }

              auto const &func(opt.value());

              /* Change the cell to be a return. */
              return
              {
                cell::return_statement
                { { func, { func.data.definition.return_type.definition } } }
              };
            }
          );
          auto const matched_native(match(native_opt));
          auto const matched_non_native(match(non_native_opt));

          if(matched_native)
          { return matched_native; }
          else if(matched_non_native)
          { return matched_non_native; }
          else
          { return {}; }
        }
      }
    }
  }
}
