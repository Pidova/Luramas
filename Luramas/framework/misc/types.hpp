#pragma once
#include "../common.hpp"
#include <cstdint>
#include <memory>
#include <string>

/*
    Representative types.
*/
namespace luramas::types {

      enum class signess : std::uint8_t {
            sign = 0u,  /* Bit[0] = signess */
            unsign = 1u /* Complete number */
      };
      enum class read_type : std::uint8_t {
            bits, /* Bits */
            bytes /* Bytes */
      };
      struct underlying_type {

            bool unsign = false;                /* Unsigned */
            read_type read = read_type::bits;   /* Read type */
            std::uint8_t precision = 0u;        /* Precision */
            luramas_bitwidth storage_size = 0u; /* Storage bits size */

            /* Compare */
            bool weak_compare(const underlying_type &other) const;
            bool compare(const underlying_type &other) const;
            bool compare(const std::uint16_t memsize) const;
            bool compare(const luramas_bitwidth bits, const bool unsign) const;
            void dominant(const underlying_type &other, const signess dom = signess::unsign);
            underlying_type dominant_t(const underlying_type &other, const signess dom = signess::unsign) const;
            luramas_bitwidth bits() const;
            bool empty() const;

            /* Min/Max */
            luramas_int_base bmin() const;
            luramas_int_base bmax() const;

            /* Emit */
            void emit(const std::uint16_t memsize);
            void emit(const luramas_bitwidth bits, const bool unsign, const std::uint8_t precision = 0u);

            /* Eq */
            bool operator==(const underlying_type &other) const;
            bool operator!=(const underlying_type &other) const;
            explicit operator bool() const;

            /* Is */
            template <read_type t>
            inline bool is() const {
                  return this->read == t;
            }

            /* Misc */
            signess signess_t() const;
            underlying_type clone(underlying_type &other) const;
            std::shared_ptr<underlying_type> clone() const;
            std::string str() const;
            void serialize(std::ostream &os) const;
            underlying_type load(std::istream &is) const;
            bool has_native() const;
            void clear();
      };

      namespace is {

            /* Is a and b signess the same but bits are different? */
            bool diff_bits(const underlying_type &a, const underlying_type &b);

            /* Are a and b bits the same but signess is different? */
            bool diff_signess(const underlying_type &a, const underlying_type &b);
      } // namespace is

      namespace native {

            static constexpr auto t_none = underlying_type();                              /* Nothing */
            static constexpr auto t_flag = underlying_type(true, read_type::bits, 0u, 1u); /* Flag value */

            /* Scalar */
            static constexpr auto t_uint8 = underlying_type(true, read_type::bits, 0u, 8u);         /* uint8_t     */
            static constexpr auto t_int8 = underlying_type(false, read_type::bits, 0u, 8u);         /* int8_t      */
            static constexpr auto t_uint16 = underlying_type(true, read_type::bits, 0u, 16u);       /* uint16_t    */
            static constexpr auto t_int16 = underlying_type(false, read_type::bits, 0u, 16u);       /* int16_t     */
            static constexpr auto t_uint32 = underlying_type(true, read_type::bits, 0u, 32u);       /* uint32_t    */
            static constexpr auto t_int32 = underlying_type(false, read_type::bits, 0u, 32u);       /* int32_t     */
            static constexpr auto t_uint64 = underlying_type(true, read_type::bits, 0u, 64u);       /* uint64_t    */
            static constexpr auto t_int64 = underlying_type(false, read_type::bits, 0u, 64u);       /* int64_t     */
            static constexpr auto t_uint128 = underlying_type(true, read_type::bits, 0u, 128u);     /* uint128_t   */
            static constexpr auto t_int128 = underlying_type(false, read_type::bits, 0u, 128u);     /* int128_t    */
            static constexpr auto t_uint256 = underlying_type(true, read_type::bits, 0u, 256u);     /* uint256_t   */
            static constexpr auto t_int256 = underlying_type(false, read_type::bits, 0u, 256u);     /* int256_t    */
            static constexpr auto t_uint512 = underlying_type(true, read_type::bits, 0u, 512u);     /* uint512_t   */
            static constexpr auto t_int512 = underlying_type(false, read_type::bits, 0u, 512u);     /* int512_t    */
            static constexpr auto t_uint1024 = underlying_type(true, read_type::bits, 0u, 1024u);   /* uint1024_t  */
            static constexpr auto t_int1024 = underlying_type(false, read_type::bits, 0u, 1024u);   /* int1024_t   */
            static constexpr auto t_uint2048 = underlying_type(true, read_type::bits, 0u, 2048u);   /* uint2048_t  */
            static constexpr auto t_int2048 = underlying_type(false, read_type::bits, 0u, 2048u);   /* int2048_t   */
            static constexpr auto t_uint4096 = underlying_type(true, read_type::bits, 0u, 4096u);   /* uint4096_t  */
            static constexpr auto t_int4096 = underlying_type(false, read_type::bits, 0u, 4096u);   /* int4096_t   */
            static constexpr auto t_uint8192 = underlying_type(true, read_type::bits, 0u, 8192u);   /* uint8192_t  */
            static constexpr auto t_int8192 = underlying_type(false, read_type::bits, 0u, 8192u);   /* int8192_t   */
            static constexpr auto t_uint16384 = underlying_type(true, read_type::bits, 0u, 16384u); /* uint16384_t */
            static constexpr auto t_int16384 = underlying_type(false, read_type::bits, 0u, 16384u); /* int16384_t  */

            /* Floating-Point Types */
            static constexpr auto t_float = underlying_type(false, read_type::bits, 7u, 32u);      /* float            */
            static constexpr auto t_double = underlying_type(false, read_type::bits, 15u, 64u);    /* double           */
            static constexpr auto t_ldouble = underlying_type(false, read_type::bits, 18u, 80u);   /* long double      */
            static constexpr auto t_lldouble = underlying_type(false, read_type::bits, 33u, 128u); /* long long double */

            /* SIMD Types */
            static constexpr auto t_m128f = underlying_type(false, read_type::bits, 7u, 128u);  /* __m128 (float, 128-bit)      */
            static constexpr auto t_m128d = underlying_type(false, read_type::bits, 15u, 128u); /* __m128 (double, 128-bit)     */
            static constexpr auto t_m128i = underlying_type(false, read_type::bits, 0u, 128u);  /* __m128i (integer, 128-bit)   */

            static constexpr auto t_m256f = underlying_type(false, read_type::bits, 7u, 256u);  /* __m256 (float, 256-bit)      */
            static constexpr auto t_m256d = underlying_type(false, read_type::bits, 15u, 256u); /* __m256 (double, 256-bit)     */
            static constexpr auto t_m256i = underlying_type(false, read_type::bits, 0u, 256u);  /* __m256i (integer, 256-bit)   */

            static constexpr auto t_m512f = underlying_type(false, read_type::bits, 7u, 512u);  /* __m512 (float, 512-bit)      */
            static constexpr auto t_m512d = underlying_type(false, read_type::bits, 15u, 512u); /* __m512 (double, 512-bit)     */
            static constexpr auto t_m512i = underlying_type(false, read_type::bits, 0u, 512u);  /* __m512i (integer, 512-bit)   */

            /* Mask Types */
            static constexpr auto t_mmask8 = underlying_type(true, read_type::bits, 0u, 8u);     /* __mmask8 (8-bit mask)      */
            static constexpr auto t_mmask16 = underlying_type(true, read_type::bits, 0u, 16u);   /* __mmask16 (16-bit mask)    */
            static constexpr auto t_mmask32 = underlying_type(true, read_type::bits, 0u, 32u);   /* __mmask32 (32-bit mask)    */
            static constexpr auto t_mmask64 = underlying_type(true, read_type::bits, 0u, 64u);   /* __mmask64 (64-bit mask)    */
            static constexpr auto t_mmask128 = underlying_type(true, read_type::bits, 0u, 128u); /* __mmask128 (128-bit mask)  */
            static constexpr auto t_mmask256 = underlying_type(true, read_type::bits, 0u, 256u); /* __mmask256 (256-bit mask)  */
            static constexpr auto t_mmask512 = underlying_type(true, read_type::bits, 0u, 512u); /* __mmask512 (512-bit mask)  */

            namespace compiler {

                  /* Objects that can be mapped to the compiler (Differnet from IR types because its more geared towards compilers specifics) */
                  struct object {
                        const char *name = "";       /* Name of the object */
                        underlying_type type;        /* Type of the object */
                        std::uint8_t ptrs = 0u;      /* Pointer count */
                        bool constant_ptr = false;   /* Is the pointer constant */
                        bool constant_value = false; /* Is the value constant */
                        bool synthetic_type = false; /* Is the type synthetic */

                        std::string str() const;
                        void clear();
                        bool empty() const;
                  };

            } // namespace compiler
      } // namespace native

      std::size_t hash_value(const underlying_type &u);
} // namespace luramas::types