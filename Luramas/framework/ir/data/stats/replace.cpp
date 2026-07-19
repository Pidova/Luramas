#include "../../ir.hpp"

void ir_stat::replace(const boost::unordered_flat_map<luramas_register, std::shared_ptr<ir_stat::ir_expr>> &exprs) {
      for (auto *i : {&this->lba, &this->l, &this->r, &this->v}) {
            if (*i) {
                  if ((*i)->is_register_reference()) {
                        if (auto it = exprs.find((*i)->reg); it != exprs.end()) {
                              *i = it->second;
                              continue;
                        }
                  }
                  (*i)->replace(exprs);
            }
      }
      for (auto &v : {&this->parameters, &this->upvalues, &this->members, this->k != keywords::page_function_goto ? &this->smembers : nullptr, &this->tmembers}) {
            if (!v) {
                  continue;
            }
            for (auto &i : *v) {
                  if (i) {
                        if (i->is_register_reference()) {
                              if (auto it = exprs.find(i->reg); it != exprs.end()) {
                                    i = it->second;
                                    continue;
                              }
                        }
                        i->replace(exprs);
                  }
            }
      }
      return;
}

void ir_stat::shallow_replace(const boost::unordered_flat_map<luramas_register, std::shared_ptr<ir_stat::ir_expr>> &exprs) {
      for (auto *i : {&this->lba, &this->l, &this->r, &this->v}) {
            if (*i && (*i)->is_register_reference()) {
                  if (auto it = exprs.find((*i)->reg); it != exprs.end()) {
                        *i = it->second;
                  }
            }
      }
      for (auto &v : {&this->parameters, &this->upvalues, &this->members, this->k != keywords::page_function_goto ? &this->smembers : nullptr, &this->tmembers}) {
            if (!v) {
                  continue;
            }
            for (auto &i : *v) {
                  if (i && i->is_register_reference()) {
                        if (auto it = exprs.find(i->reg); it != exprs.end()) {
                              i = it->second;
                        }
                  }
            }
      }
      return;
}
