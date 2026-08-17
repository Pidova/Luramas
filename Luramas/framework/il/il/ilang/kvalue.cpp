#include "../il.hpp"

namespace luramas::il {

      std::string ilang::kvalue::str() const {

            std::string result;

            switch (this->type) {
                  case arch::data::kval_kinds::vector: {
                        result = "VECTOR { ";
                        for (const auto &i : this->vector.vector) {
                              result += std::to_string(i) + " ";
                        }
                        result = "}";
                        break;
                  }
                  case arch::data::kval_kinds::none: {
                        result = "none";
                        break;
                  }
                  case arch::data::kval_kinds::boolean: {
                        result = (this->boolean.b) ? "true" : "false";
                        break;
                  }
                  case arch::data::kval_kinds::integer: {
                        result = this->integer.str;
                        break;
                  }
                  case arch::data::kval_kinds::string: {
                        result = this->string.str;
                        break;
                  }
                  case arch::data::kval_kinds::userdata: {
                        result = this->userdata.str;
                        break;
                  }
                  case arch::data::kval_kinds::table: {
                        result = "node_" + std::to_string(this->table.node_size) + ", array_" + std::to_string(this->table.array_size);
                        break;
                  }
                  case arch::data::kval_kinds::function: {
                        result = this->function.str;
                        break;
                  }
                  case arch::data::kval_kinds::closure: {
                        result = "closure_" + std::to_string(this->closure.id);
                        break;
                  }
                  case arch::data::kval_kinds::thread: {
                        result = this->thread.str;
                        break;
                  }
                  case arch::data::kval_kinds::upvalue: {
                        result = this->upvalue.str;
                        break;
                  }
                  default: {
                        luramas::error::error("Unkown IL kvalue type.");
                  }
            }

            return result;
      }
} // namespace luramas::il