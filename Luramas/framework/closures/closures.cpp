#include "closures.hpp"

inline void set_nodes(std::shared_ptr<luramas::closures::closure> &closure) {

      for (const auto &i : closure->il->dis) {
            auto node = std::make_shared<luramas::closures::node>();
            node->address = i->addr;
            node->lex = luramas::il::lexer::lexer(i);
            closure->nodes.emplace_back(node);
      }
      return;
}

std::shared_ptr<luramas::closures::closure> luramas::closures::gen_closure(std::shared_ptr<luramas::il::ilang> &il_data) {

      auto result = std::make_shared<closure>();
      std::deque<std::shared_ptr<closure>> closures = {result};

      /* Set closure and closure. */
      result->il = il_data;
      result->nodes.reserve(result->il->dis.size());
      set_nodes(result);

      do {
            auto current_closure = closures.back();
            closures.pop_back();

            for (const auto &i : current_closure->il->closures) {

                  auto child = std::make_shared<closure>();
                  child->il = i;
                  child->nodes.reserve(child->il->dis.size());
                  set_nodes(child);

                  current_closure->closures.emplace_back(child);
                  closures.emplace_back(child);
            }

            current_closure->set_flags();
      } while (!closures.empty());
      return result;
}