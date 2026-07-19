#include "../../ir.hpp"

void ir_stat::clone(std::shared_ptr<ir_stat> &buffer, const bool deep, const bool regs) const {

      buffer->flags.clone(this->flags);

      /* Data */
      buffer->k = this->k;
      buffer->c = this->c;
      buffer->b = this->b;
      buffer->label = this->label;
      buffer->jlabel = this->jlabel;
      buffer->end_label = this->end_label;
      buffer->extra_bits = this->extra_bits;

      /* Metadata */
      buffer->annotation = this->annotation;

      for (const auto &[reg, expr] : this->args) {
            buffer->args.try_emplace(reg, deep ? expr->clone(deep, regs) : expr);
      }
      for (const auto &m : this->upvalues) {
            buffer->upvalues.emplace_back(deep && (regs || !m->is_register_reference()) ? m->clone(deep, regs) : m);
      }

      if (const auto &m = this->lba; m) {
            buffer->lba = deep && (regs || !m->is_register_reference()) ? m->clone(deep, regs) : m;
      }
      if (const auto &m = this->l; m) {
            buffer->l = deep && (regs || !m->is_register_reference()) ? m->clone(deep, regs) : m;
      }
      if (const auto &m = this->r; m) {
            buffer->r = deep && (regs || !m->is_register_reference()) ? m->clone(deep, regs) : m;
      }
      if (const auto &m = this->v; m) {
            buffer->v = deep && (regs || !m->is_register_reference()) ? m->clone(deep, regs) : m;
      }

      for (const auto &m : this->members) {
            buffer->members.emplace_back(deep && (regs || !m->is_register_reference()) ? m->clone(deep, regs) : m);
      }
      for (const auto &m : this->smembers) {
            buffer->smembers.emplace_back(deep && (regs || !m->is_register_reference()) ? m->clone(deep, regs) : m);
      }
      for (const auto &m : this->tmembers) {
            buffer->tmembers.emplace_back(deep && (regs || !m->is_register_reference()) ? m->clone(deep, regs) : m);
      }
      for (const auto &m : this->meta) {
            buffer->meta.emplace_back(deep && (regs || !m->is_register_reference()) ? m->clone(deep, regs) : m);
      }
      return;
}
std::shared_ptr<ir_stat> ir_stat::clone(const bool deep, const bool regs) const {

      auto result = std::make_shared<ir_stat>();
      this->clone(result, deep, regs);
      return result;
}