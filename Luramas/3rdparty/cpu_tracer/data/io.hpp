#pragma once
#include "../boostpp/vector.hpp"
#include <fstream>
#include <type_traits>
#include <vector>

namespace cpu_tracer::io {

      /* Read value */
      template <typename T>
      inline void read(std::ifstream &ifs, T &val) {
            ifs.read(reinterpret_cast<char *>(&val), sizeof(T));
            return;
      }
      template <typename... Args>
      inline void read(std::ifstream &ifs, Args &...args) {
            (read(ifs, args), ...);
      }

      /* Read into vector */
      template <typename T>
      inline void readv(std::ifstream &ifs, std::vector<T> &vec) {
            std::size_t size = 0u;
            read(ifs, size);
            vec.resize(size);
            if (size) {
                  ifs.read(reinterpret_cast<char *>(vec.data()), size * sizeof(T));
            }
            return;
      }
      template <typename T, std::size_t N, typename NT>
      inline void readv(std::ifstream &ifs, boost::fixed_vector<T, N, NT> &vec) {
            std::size_t size = 0u;
            read(ifs, size);
            vec.resize(NT(size));
            if (size) {
                  ifs.read(reinterpret_cast<char *>(vec.data()), size * sizeof(T));
            }
            return;
      }

      /* Write value */
      template <typename T>
      inline void write(std::ofstream &ofs, const T &val) {
            ofs.write(reinterpret_cast<const char *>(&val), sizeof(T));
            return;
      }
      template <typename... Args>
      inline void write(std::ofstream &ofs, const Args &...args) {
            (write(ofs, args), ...);
      }

      /* Write into vector */
      template <typename T>
      inline void writev(std::ofstream &ofs, const std::vector<T> &vec) {
            const std::size_t size = vec.size();
            write(ofs, size);
            if (size) {
                  ofs.write(reinterpret_cast<const char *>(vec.data()), size * sizeof(T));
            }
            return;
      }
      template <typename T, std::size_t N, typename NT>
      inline void writev(std::ofstream &ofs, const boost::fixed_vector<T, N, NT> &vec) {
            const std::size_t size = vec.size();
            write(ofs, size);
            if (size) {
                  ofs.write(reinterpret_cast<const char *>(vec.data()), size * sizeof(T));
            }
            return;
      }
} // namespace cpu_tracer::io