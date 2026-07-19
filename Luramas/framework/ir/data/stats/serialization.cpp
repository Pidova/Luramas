#include "../../ir.hpp"

void ir_stat::serialize(std::ostream &os, const std::shared_ptr<std::vector<std::pair<std::string, std::vector<luramas_address>>>> &annotations) const {

      const auto packed_flags = this->flags.pack();
      os.write(reinterpret_cast<const char *const>(&packed_flags), sizeof(packed_flags));

      os.write(reinterpret_cast<const char *const>(&this->k), sizeof(this->k));
      os.write(reinterpret_cast<const char *const>(&this->c), sizeof(this->c));
      os.write(reinterpret_cast<const char *const>(&this->b), sizeof(this->b));
      os.write(reinterpret_cast<const char *const>(&this->label), sizeof(this->label));
      os.write(reinterpret_cast<const char *const>(&this->jlabel), sizeof(this->jlabel));
      os.write(reinterpret_cast<const char *const>(&this->end_label), sizeof(this->end_label));
      os.write(reinterpret_cast<const char *const>(&this->elif_end_label), sizeof(this->elif_end_label));
      os.write(reinterpret_cast<const char *const>(&this->table_index), sizeof(this->table_index));
      os.write(reinterpret_cast<const char *const>(&this->extra_bits), sizeof(this->extra_bits));
      os.write(reinterpret_cast<const char *const>(&this->underlying_jump), sizeof(this->underlying_jump));

      const auto serialize_expr = [&](const auto &ptr) {
            const bool has_value = static_cast<bool>(ptr);
            os.write(reinterpret_cast<const char *const>(&has_value), sizeof(has_value));
            if (has_value) {
                  ptr->serialize(os, annotations);
            }
            return;
      };
      serialize_expr(this->lba);
      serialize_expr(this->l);
      serialize_expr(this->r);
      serialize_expr(this->v);

      const auto serialize_data = [&](const auto &vec) {
            const auto size = vec.size();
            os.write(reinterpret_cast<const char *const>(&size), sizeof(size));
            for (const auto &i : vec) {
                  serialize_expr(i);
            }
            return;
      };
      serialize_data(this->parameters);
      serialize_data(this->upvalues);
      serialize_data(this->members);
      serialize_data(this->smembers);
      serialize_data(this->tmembers);
      serialize_data(this->meta);

      const auto args_size = this->args.size();
      os.write(reinterpret_cast<const char *const>(&args_size), sizeof(args_size));
      for (const auto &[k, v] : this->args) {
            os.write(reinterpret_cast<const char *const>(&k), sizeof(k));
            serialize_expr(v);
      }

      const auto annotation_size = this->annotation.size();
      os.write(reinterpret_cast<const char *const>(&annotation_size), sizeof(annotation_size));
      os.write(this->annotation.data(), annotation_size);
      return;
}
void ir_stat::load(std::istream &is) {

      std::uint32_t packed_flags = 0u;
      is.read(reinterpret_cast<char *>(&packed_flags), sizeof(packed_flags));
      this->flags.unpack(packed_flags);

      is.read(reinterpret_cast<char *>(&this->k), sizeof(this->k));
      is.read(reinterpret_cast<char *>(&this->c), sizeof(this->c));
      is.read(reinterpret_cast<char *>(&this->b), sizeof(this->b));

      is.read(reinterpret_cast<char *>(&this->label), sizeof(this->label));
      is.read(reinterpret_cast<char *>(&this->jlabel), sizeof(this->jlabel));
      is.read(reinterpret_cast<char *>(&this->end_label), sizeof(this->end_label));
      is.read(reinterpret_cast<char *>(&this->elif_end_label), sizeof(this->elif_end_label));
      is.read(reinterpret_cast<char *>(&this->table_index), sizeof(this->table_index));
      is.read(reinterpret_cast<char *>(&this->extra_bits), sizeof(this->extra_bits));
      is.read(reinterpret_cast<char *>(&this->underlying_jump), sizeof(this->underlying_jump));

      auto load_expr = [&](auto &ptr) {
            bool valid = false;
            is.read(reinterpret_cast<char *>(&valid), sizeof(valid));
            if (valid) {
                  ptr = std::make_shared<ir_expr>();
                  ptr->load(is);
            }
      };
      load_expr(this->lba);
      load_expr(this->l);
      load_expr(this->r);
      load_expr(this->v);

      auto load_data = [&](auto &vec) {
            luramas_count size = 0u;
            is.read(reinterpret_cast<char *>(&size), sizeof(size));
            vec.resize(size);
            for (auto &i : vec) {
                  load_expr(i);
            }
            return;
      };
      load_data(this->parameters);
      load_data(this->upvalues);
      load_data(this->members);
      load_data(this->smembers);
      load_data(this->tmembers);
      load_data(this->meta);

      luramas_count args_size = 0u;
      is.read(reinterpret_cast<char *>(&args_size), sizeof(args_size));
      this->args.clear();
      for (auto i = 0; i < args_size; ++i) {
            luramas_register key = 0u;
            is.read(reinterpret_cast<char *>(&key), sizeof(key));
            auto value = std::make_shared<ir_expr>();
            load_expr(value);
            this->args.try_emplace(key, value);
      }

      luramas_count annotation_size = 0u;
      is.read(reinterpret_cast<char *>(&annotation_size), sizeof(annotation_size));
      this->annotation.resize(annotation_size);
      is.read(reinterpret_cast<char *>(this->annotation.data()), annotation_size);
      return;
}