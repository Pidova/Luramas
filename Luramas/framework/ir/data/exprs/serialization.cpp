#include "../../ir.hpp"

void ir_stat::ir_expr::serialize(std::ostream &os, const std::shared_ptr<std::vector<std::pair<std::string, std::vector<luramas_address>>>> &annotations) const {

      const auto packed_flags = this->flags.pack();
      os.write(reinterpret_cast<const char *const>(&packed_flags), sizeof(std::uint32_t));
      os.write(reinterpret_cast<const char *const>(&this->u), sizeof(this->u));
      os.write(reinterpret_cast<const char *const>(&this->b), sizeof(this->b));
      os.write(reinterpret_cast<const char *const>(&this->k), sizeof(this->k));
      os.write(reinterpret_cast<const char *const>(&this->tk), sizeof(this->tk));
      os.write(reinterpret_cast<const char *const>(&this->e), sizeof(this->e));
      os.write(reinterpret_cast<const char *const>(&this->rk), sizeof(this->rk));
      this->n.serialize(os);
      os.write(reinterpret_cast<const char *const>(&this->bv), sizeof(this->bv));
      os.write(reinterpret_cast<const char *const>(&this->reg), sizeof(this->reg));
      os.write(reinterpret_cast<const char *const>(&this->vreg), sizeof(this->vreg));
      os.write(reinterpret_cast<const char *const>(&this->amount), sizeof(this->amount));

      const auto has_ptr = this->non_native != nullptr;
      os.write(reinterpret_cast<const char *const>(&has_ptr), sizeof(has_ptr));
      if (has_ptr) {
            this->non_native->serialize(os);
      }

      const auto v_size = this->v.size();
      if (v_size && this->k == expr_kinds::reg && annotations) {
            if (const auto *p = dynamic_cast<std::ostringstream *>(&os)) {
                  bool set = false;
                  for (auto &[str, v] : *annotations) {
                        if (this->v == str) {
                              v.emplace_back(p->str().size());
                              set = true;
                        }
                  }
                  if (!set) {
                        annotations->emplace_back(std::make_pair(this->v, std::vector<luramas_address>({p->str().size()})));
                  }
            }
      } else {
            os.write(reinterpret_cast<const char *const>(&v_size), sizeof(v_size));
            os.write(this->v.data(), v_size);
      }

      const auto serialize_expr = [&](const auto &ptr) {
            const auto has_ptr = (ptr != nullptr);
            os.write(reinterpret_cast<const char *const>(&has_ptr), sizeof(has_ptr));
            if (has_ptr) {
                  ptr->serialize(os, annotations);
            }
            return;
      };
      serialize_expr(this->l);
      serialize_expr(this->r);
      serialize_expr(this->ev);
      serialize_expr(this->xv);

      const auto members_size = this->members.size();
      os.write(reinterpret_cast<const char *const>(&members_size), sizeof(members_size));
      for (const auto &i : this->members) {
            serialize_expr(i);
      }

      const auto captures_size = this->captures.size();
      os.write(reinterpret_cast<const char *const>(&captures_size), sizeof(captures_size));
      for (const auto &i : this->captures) {
            serialize_expr(i);
      }

      const auto tmembers_size = this->tmembers.size();
      os.write(reinterpret_cast<const char *const>(&tmembers_size), sizeof(tmembers_size));
      for (const auto &[i, v] : this->tmembers) {
            serialize_expr(i);
            serialize_expr(v);
      }

      const auto closure_size = this->closure.size();
      os.write(reinterpret_cast<const char *const>(&closure_size), sizeof(closure_size));
      for (const auto &i : this->closure) {
            const bool has_i = (i != nullptr);
            os.write(reinterpret_cast<const char *const>(&has_i), sizeof(has_i));
            if (has_i) {
                  i->serialize(os, annotations);
            }
      }
      return;
}
void ir_stat::ir_expr::load(std::istream &is) {

      std::uint32_t packed_flags;
      is.read(reinterpret_cast<char *>(&packed_flags), sizeof(packed_flags));
      this->flags.unpack(packed_flags);

      is.read(reinterpret_cast<char *>(&this->u), sizeof(this->u));
      is.read(reinterpret_cast<char *>(&this->b), sizeof(this->b));
      is.read(reinterpret_cast<char *>(&this->k), sizeof(this->k));
      is.read(reinterpret_cast<char *>(&this->tk), sizeof(this->tk));
      is.read(reinterpret_cast<char *>(&this->e), sizeof(this->e));
      is.read(reinterpret_cast<char *>(&this->rk), sizeof(this->rk));
      this->n.deserialize(is);
      is.read(reinterpret_cast<char *>(&this->bv), sizeof(this->bv));
      is.read(reinterpret_cast<char *>(&this->reg), sizeof(this->reg));
      is.read(reinterpret_cast<char *>(&this->vreg), sizeof(this->vreg));
      is.read(reinterpret_cast<char *>(&this->amount), sizeof(this->amount));

      auto has_ptr = false;
      is.read(reinterpret_cast<char *>(&has_ptr), sizeof(has_ptr));
      if (has_ptr) {
            this->non_native->load(is);
      }

      luramas_count v_size = 0u;
      is.read(reinterpret_cast<char *>(&v_size), sizeof(v_size));
      this->v.resize(v_size);
      is.read(reinterpret_cast<char *>(this->v.data()), v_size);

      const auto load_expr = [&](auto &ptr) {
            auto has_ptr = false;
            is.read(reinterpret_cast<char *>(&has_ptr), sizeof(has_ptr));
            if (has_ptr) {
                  ptr = std::make_shared<ir_expr>();
                  ptr->load(is);
            }
            return;
      };
      load_expr(this->l);
      load_expr(this->r);
      load_expr(this->ev);
      load_expr(this->xv);

      luramas_count members_size = 0u;
      is.read(reinterpret_cast<char *>(&members_size), sizeof(members_size));
      this->members.resize(members_size);
      for (auto &i : this->members) {
            load_expr(i);
      }

      luramas_count captures_size = 0u;
      is.read(reinterpret_cast<char *>(&captures_size), sizeof(captures_size));
      this->captures.resize(captures_size);
      for (auto &i : this->captures) {
            load_expr(i);
      }

      luramas_count tmembers_size = 0u;
      is.read(reinterpret_cast<char *>(&tmembers_size), sizeof(tmembers_size));
      this->tmembers.reserve(tmembers_size);
      for (auto i = 0u; i < tmembers_size; ++i) {
            auto idx = std::make_shared<ir_expr>();
            auto val = std::make_shared<ir_expr>();
            load_expr(idx);
            load_expr(val);
            this->tmembers.emplace_back(std::make_pair(idx, val));
      }

      luramas_count closure_size = 0u;
      is.read(reinterpret_cast<char *>(&closure_size), sizeof(closure_size));
      this->closure.reserve(closure_size);
      for (auto i = 0u; i < closure_size; ++i) {
            bool valid = false;
            is.read(reinterpret_cast<char *>(&valid), sizeof(valid));
            if (valid) {
                  auto stat = std::make_shared<ir_stat>();
                  stat->load(is);
                  this->closure.emplace_back(stat);
            }
      }
      return;
}
std::shared_ptr<ir_stat::ir_expr> ir_stat::ir_expr::c() {

      auto result = weak_from_this().lock();
      if (!result) {
            result = std::shared_ptr<ir_expr>(this, [](ir_expr *) {});
      }
      while (result->k == expr_kinds::cast && result->l) {
            result = result->l;
      }
      return result;
}