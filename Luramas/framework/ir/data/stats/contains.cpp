#include "../../ir.hpp"

bool ir_stat::contains(const expr_kinds k) const {

      if (this->l) {
            if (this->l->contains(k)) {
                  return true;
            }
      }
      if (this->r) {
            if (this->r->contains(k)) {
                  return true;
            }
      }
      if (this->v) {
            if (this->v->contains(k)) {
                  return true;
            }
      }
      if (this->lba) {
            if (this->lba->contains(k)) {
                  return true;
            }
      }
      for (const auto &m : this->members) {
            if (m->contains(k)) {
                  return true;
            }
      }
      if (this->k != keywords::page_function_goto) {
            for (const auto &m : this->smembers) {
                  if (m->contains(k)) {
                        return true;
                  }
            }
      }
      for (const auto &m : this->tmembers) {
            if (m->contains(k)) {
                  return true;
            }
      }
      return false;
}
bool ir_stat::contains(const tkind tk) const {

      if (this->l) {
            if (this->l->contains(tk)) {
                  return true;
            }
      }
      if (this->r) {
            if (this->r->contains(tk)) {
                  return true;
            }
      }
      if (this->v) {
            if (this->v->contains(tk)) {
                  return true;
            }
      }
      if (this->lba) {
            if (this->lba->contains(tk)) {
                  return true;
            }
      }
      for (const auto &m : this->members) {
            if (m->contains(tk)) {
                  return true;
            }
      }
      if (this->k != keywords::page_function_goto) {
            for (const auto &m : this->smembers) {
                  if (m->contains(tk)) {
                        return true;
                  }
            }
      }
      for (const auto &m : this->tmembers) {
            if (m->contains(tk)) {
                  return true;
            }
      }
      return false;
}