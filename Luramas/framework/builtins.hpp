/*
    Common builtins an ISA may use to help standardize lifting.
    Though args and returns are a suggestion; you can still use as many as you want.
    Types are not restricted, you can interpret these how you want.

    Schema:
        {Preceeding namespaces with "_" dilemeter + "_" name)
*/
#pragma once
#include <cstdint>
#include <cstring>
#define LURAMAS_MAKE_BUILTIN_NAME(x) ("LURA_" x)

namespace luramas::builtins {

      namespace data {

            struct func {

                  const char *name = "";        /* Name */
                  std::int8_t arg_count = 0;    /* -1 for n */
                  std::int8_t result_count = 0; /* -1 for n */
                  std::size_t id = 0;           /* ID */

                  constexpr func() = default;
                  constexpr func(const char *const name, const std::int8_t argc, const std::int8_t res, const std::size_t id = __COUNTER__)
                      : name(name), arg_count(argc), result_count(res), id(id) {
                  }

                  inline bool empty() const {
                        return !std::strlen(this->name);
                  }
                  inline void clear() {
                        *this = func();
                        return;
                  }
            };
      } // namespace data

      namespace SYS {

            /* (System call)  ... = SYS_CALL(...) */
            static constexpr auto CALL = data::func(LURAMAS_MAKE_BUILTIN_NAME("SYS_CALL"), -1, -1);

            namespace MANAGEMENT {

                  /* (Enter system management mode) RESULT = SYS_MANAGEMENT_EXTER(ARG) */
                  static constexpr auto ENTER = data::func(LURAMAS_MAKE_BUILTIN_NAME("SYS_MANAGEMENT_EXTER"), 1, 1);

                  /* (Exit from system management mode) RESULT = SYS_MANAGEMENT_EXIT(ARG) */
                  static constexpr auto EXIT = data::func(LURAMAS_MAKE_BUILTIN_NAME("SYS_MANAGEMENT_EXIT"), 1, 1);
            } // namespace MANAGEMENT

            /* (Enter HALT State) RESULT = HALT(ARG) */
            static constexpr auto ENTER_HALT = data::func(LURAMAS_MAKE_BUILTIN_NAME("SYS_HALT"), 1, 1);

            /* (Interrupt execution) RESULT = INTERRUPT(VALUE) */
            static constexpr auto INTERRUPT = data::func(LURAMAS_MAKE_BUILTIN_NAME("SYS_INTERRUPT"), 1, 1);
      } // namespace SYS

      namespace IO {

            /* (Input to module port) RESULT = INPUT(VALUE, MODULE, PORT)  */
            static constexpr auto INPUT = data::func(LURAMAS_MAKE_BUILTIN_NAME("IO_INPUT"), 3, 1);

            /* (Read output from module port) RESULT = OUTPUT(MODULE, PORT) */
            static constexpr auto OUTPUT = data::func(LURAMAS_MAKE_BUILTIN_NAME("IO_OUTPUT"), 3, 1);
      } // namespace IO

      namespace VM {

            /* (Launch VM)  RESULT = VM_LAUNCH(ARG) */
            static constexpr auto LAUNCH = data::func(LURAMAS_MAKE_BUILTIN_NAME("VM_LAUNCH"), 1, 1);

            /* (Change VM permissions)  RESULT = VM_PERMISSION(DEST_VALUE, SOURCE_VALUE) */
            static constexpr auto PERMISSION = data::func(LURAMAS_MAKE_BUILTIN_NAME("VM_PERMISSION"), 2, 1);

            /* (Make VM accesses to certain parts of memory invalid) RESULT = VM_ISOLATE(MODULE_ID_VALUE, RANGE_START, RANGE_END) */
            static constexpr auto MEMORY_ISOLATE = data::func(LURAMAS_MAKE_BUILTIN_NAME("VM_MEMORY_ISOLATE"), 3, 1);

            /* (Make VM triggers certain CPU state to throw an exception) RESULT = VM_STATE_ISOLATE(VALUE) */
            static constexpr auto STATE_ISOLATE = data::func(LURAMAS_MAKE_BUILTIN_NAME("VM_STATE_ISOLATE"), 1, 1);

            /* (Pause VM) RESULT = VM_PAUSE(VALUE) */
            static constexpr auto PAUSE = data::func(LURAMAS_MAKE_BUILTIN_NAME("VM_PAUSE"), 1, 1);

            /* (Resume VM) RESULT = VM_RESUME(VALUE) */
            static constexpr auto RESUME = data::func(LURAMAS_MAKE_BUILTIN_NAME("VM_RESUME"), 1, 1);

            /* (Enable VM) RESULT = VM_ENABLE(VALUE) */
            static constexpr auto ENABLE = data::func(LURAMAS_MAKE_BUILTIN_NAME("VM_ENABLE"), 1, 1);

            /* (Disable VM) RESULT = VM_DISABLE(VALUE) */
            static constexpr auto DISABLE = data::func(LURAMAS_MAKE_BUILTIN_NAME("VM_DISABLE"), 1, 1);

            namespace MANAGER {

                  /* (Load VM manager) RESULT = VM_MANAGER_LOAD(MANAGER) */
                  static constexpr auto LOAD = data::func(LURAMAS_MAKE_BUILTIN_NAME("VM_MANAGER_LOAD"), 1, 1);

                  /* (Clear VM manager) RESULT = VM_MANAGER_CLEAR(MANAGER) */
                  static constexpr auto CLEAR = data::func(LURAMAS_MAKE_BUILTIN_NAME("VM_MANAGER_CLEAR"), 1, 1);

                  /* (Read value from VM Manager) RESULT = VM_MANAGER_READ_FIELD(MANAGER, READING_VALUE) */
                  static constexpr auto READ_FIELD = data::func(LURAMAS_MAKE_BUILTIN_NAME("VM_MANAGER_READ_FIELD"), 2, 1);

                  /* (Set value to VM Manager) RESULT = VM_MANAGER_SET_FIELD(MANAGER, DEST_VALUE, WRITE_VALUE) */
                  static constexpr auto SET_FIELD = data::func(LURAMAS_MAKE_BUILTIN_NAME("VM_MANAGER_SET_FIELD"), 3, 1);

                  /* (Disable VM Manager) RESULT = VM_MANAGER_DISABLE(MANAGER) */
                  static constexpr auto DISABLE = data::func(LURAMAS_MAKE_BUILTIN_NAME("VM_MANAGER_DISABLE"), 1, 1);

                  /* (Enable VM Manager) RESULT = VM_MANAGER_ENABLE(MANAGER) */
                  static constexpr auto ENABLE = data::func(LURAMAS_MAKE_BUILTIN_NAME("VM_MANAGER_ENABLE"), 1, 1);
            } // namespace MANAGER

            /* (VM hyper call guest -> host)  ... = VM_CALL(...) */
            static constexpr auto CALL = data::func(LURAMAS_MAKE_BUILTIN_NAME("VM_CALL"), -1, -1);

            /* (Exit VM) RESULT = VM_LAUNCH(ARG) */
            static constexpr auto EXIT = data::func(LURAMAS_MAKE_BUILTIN_NAME("VM_EXIT"), 1, 1);
      } // namespace VM

      namespace MEMORY {

            namespace CACHE {

                  /* (Write to cached memory) RESULT = MEMORY_CACHE_WRITE(VALUE) */
                  static constexpr auto WRITE = data::func(LURAMAS_MAKE_BUILTIN_NAME("MEMORY_CACHE_WRITE"), 1, 1);

                  /* (Read from cached memory) RESULT = MEMORY_CACHE_READ(VALUE) */
                  static constexpr auto READ = data::func(LURAMAS_MAKE_BUILTIN_NAME("MEMORY_CACHE_READ"), 1, 1);

                  /* (Clear cached memory) RESULT = MEMORY_CACHE_CLEAR(VALUE) */
                  static constexpr auto CLEAR = data::func(LURAMAS_MAKE_BUILTIN_NAME("MEMORY_CACHE_CLEAR"), 1, 1);

                  /* (Set entire cache size) RESULT = MEMORY_CACHE_SET_SIZE(VALUE) */
                  static constexpr auto SET_SIZE = data::func(LURAMAS_MAKE_BUILTIN_NAME("MEMORY_CACHE_SET_SIZE"), 1, 1);

                  /* (Get entire cache size) RESULT = MEMORY_CACHE_GET_SIZE(VALUE) */
                  static constexpr auto GET_SIZE = data::func(LURAMAS_MAKE_BUILTIN_NAME("MEMORY_CACHE_GET_SIZE"), 1, 1);

                  /* (Set cache line size) RESULT = MEMORY_CACHE_SET_LINE_SIZE(VALUE) */
                  static constexpr auto SET_LINE_SIZE = data::func(LURAMAS_MAKE_BUILTIN_NAME("MEMORY_CACHE_SET_LINE_SIZE"), 1, 1);

                  /* (Get cache line size) RESULT = MEMORY_CACHE_GET_LINE_SIZE(VALUE) */
                  static constexpr auto GET_LINE_SIZE = data::func(LURAMAS_MAKE_BUILTIN_NAME("MEMORY_CACHE_GET_LINE_SIZE"), 1, 1);

                  /* (Allocate cache) RESULT = MEMORY_CACHE_ALLOC(VALUE) */
                  static constexpr auto ALLOC = data::func(LURAMAS_MAKE_BUILTIN_NAME("MEMORY_CACHE_ALLOC"), 1, 1);

                  /* (Free cache) RESULT = MEMORY_CACHE_FREE(VALUE) */
                  static constexpr auto FREE = data::func(LURAMAS_MAKE_BUILTIN_NAME("MEMORY_CACHE_FREE"), 1, 1);
            } // namespace CACHE

            /* (Allocate memory) RESULT = MEMORY_ALLOC(VALUE) */
            static constexpr auto ALLOC = data::func(LURAMAS_MAKE_BUILTIN_NAME("MEMORY_ALLOC"), 1, 1);

            /* (Free memory) RESULT = MEMORY_FREE(VALUE) */
            static constexpr auto FREE = data::func(LURAMAS_MAKE_BUILTIN_NAME("MEMORY_FREE"), 1, 1);

            /* (Compare memory address to given array) RESULT = MEMORY_COMPARE(ADDRESS, ARRAY) */
            static constexpr auto COMPARE = data::func(LURAMAS_MAKE_BUILTIN_NAME("MEMORY_COMPARE"), 2, 1);

            namespace FENCE {

                  /* (Make memory fence) RESULT = MEMORY_FENCE_SET(VALUE) */
                  static constexpr auto SET = data::func(LURAMAS_MAKE_BUILTIN_NAME("MEMORY_FENCE_SET"), 1, 1);

                  /* (Clear memory fence) RESULT = MEMORY_FENCE_CLEAR(VALUE) */
                  static constexpr auto CLEAR = data::func(LURAMAS_MAKE_BUILTIN_NAME("MEMORY_FENCE_CLEAR"), 1, 1);

                  /* (Check memory fence) RESULT = MEMORY_FENCE_CHECK(VALUE) */
                  static constexpr auto CHECK = data::func(LURAMAS_MAKE_BUILTIN_NAME("MEMORY_FENCE_CHECK"), 1, 1);

                  /* (Get memory fence) RESULT = MEMORY_FENCE_GET(VALUE) */
                  static constexpr auto GET = data::func(LURAMAS_MAKE_BUILTIN_NAME("MEMORY_FENCE_GET"), 1, 1);

                  /* (Remove memory fence) RESULT = MEMORY_FENCE_REMOVE(VALUE) */
                  static constexpr auto REMOVE = data::func(LURAMAS_MAKE_BUILTIN_NAME("MEMORY_FENCE_REMOVE"), 1, 1);
            } // namespace FENCE

      } // namespace MEMORY

      namespace CPU {

            /* (Enable CPU option flag) RESULT = CPU_ENABLE(FLAG) */
            static constexpr auto ENABLE = data::func(LURAMAS_MAKE_BUILTIN_NAME("CPU_ENABLE"), 1, 1);

            /* (Disable CPU option flag) RESULT = CPU_DISABLE(FLAG) */
            static constexpr auto DISABLE = data::func(LURAMAS_MAKE_BUILTIN_NAME("CPU_DISABLE"), 1, 1);

            /* (Add CPU option flag) RESULT = CPU_ADD(FLAG) */
            static constexpr auto ADD = data::func(LURAMAS_MAKE_BUILTIN_NAME("CPU_ADD"), 1, 1);

            /* (Remove CPU option flag) RESULT = CPU_REMOVE(FLAG) */
            static constexpr auto REMOVE = data::func(LURAMAS_MAKE_BUILTIN_NAME("CPU_REMOVE"), 1, 1);

            /* (Gets CPU info) RESULT = CPU_INFO(INPUT) */
            static constexpr auto INFO = data::func(LURAMAS_MAKE_BUILTIN_NAME("CPU_INFO"), 1, 1);

            /* (Get CPU time-stamp counter) RESULT = CPU_GET_TIMESTAMP_COUNTER(INPUT) */
            static constexpr auto GET_TIMESTAMP_COUNTER = data::func(LURAMAS_MAKE_BUILTIN_NAME("CPU_GET_TIMESTAMP_COUNTER"), 1, 1);

            /* (Handles CPU exception) RESULT = CPU_HANDLE_EXCEPTION(INPUT) */
            static constexpr auto HANDLE_EXCEPTION = data::func(LURAMAS_MAKE_BUILTIN_NAME("CPU_HANDLE_EXCEPTION"), 1, 1);

      } // namespace CPU

      namespace INTERRUPT {

            /* (Enable interrupt) RESULT = INTERRUPT_ENABLE(FLAG) */
            static constexpr auto ENABLE = data::func(LURAMAS_MAKE_BUILTIN_NAME("INTERRUPT_ENABLE"), 1, 1);

            /* (Disable interrupt) RESULT = INTERRUPT_DISABLE(FLAG) */
            static constexpr auto DISABLE = data::func(LURAMAS_MAKE_BUILTIN_NAME("INTERRUPT_DISABLE"), 1, 1);

            /* (Add interrupt) RESULT = INTERRUPT_ADD(FLAG) */
            static constexpr auto ADD = data::func(LURAMAS_MAKE_BUILTIN_NAME("INTERRUPT_ADD"), 1, 1);

            /* (Remove interrupt) RESULT = INTERRUPT_REMOVE(FLAG) */
            static constexpr auto REMOVE = data::func(LURAMAS_MAKE_BUILTIN_NAME("INTERRUPT_REMOVE"), 1, 1);

            /* (Invoke interrupt) RESULT = INTERRUPT_INVOKE(FLAG) */
            static constexpr auto INVOKE = data::func(LURAMAS_MAKE_BUILTIN_NAME("INTERRUPT_INVOKE"), 1, 1);

            namespace TABLE {

                  /* (Load interrupt table) RESULT = INTERRUPT_TABLE_LOAD(VALUE) */
                  static constexpr auto LOAD = data::func(LURAMAS_MAKE_BUILTIN_NAME("INTERRUPT_TABLE_LOAD"), 1, 1);

                  /* (Get interrupt table) RESULT = INTERRUPT_TABLE_GET(VALUE) */
                  static constexpr auto GET = data::func(LURAMAS_MAKE_BUILTIN_NAME("INTERRUPT_TABLE_GET"), 1, 1);
            } // namespace TABLE
      } // namespace INTERRUPT

      namespace TIMER {

            /* (Set timer) RESULT = TIMER_SET(VALUE) */
            static constexpr auto SET = data::func(LURAMAS_MAKE_BUILTIN_NAME("TIMER_SET"), 1, 1);

            /* (Clear timer) RESULT = TIMER_CLEAR(VALUE) */
            static constexpr auto CLEAR = data::func(LURAMAS_MAKE_BUILTIN_NAME("TIMER_CLEAR"), 1, 1);
      } // namespace TIMER

      namespace THREAD {

            /* (Create thread) RESULT = THREAD_CREATE(VALUE) */
            static constexpr auto CREATE = data::func(LURAMAS_MAKE_BUILTIN_NAME("THREAD_CREATE"), 1, 1);

            /* (Destroy thread) RESULT = THREAD_DESTROY(VALUE) */
            static constexpr auto DESTROY = data::func(LURAMAS_MAKE_BUILTIN_NAME("THREAD_DESTROY"), 1, 1);

            /* (Join thread) RESULT = THREAD_JOIN(VALUE) */
            static constexpr auto JOIN = data::func(LURAMAS_MAKE_BUILTIN_NAME("THREAD_JOIN"), 1, 1);

            /* (Detach thread) RESULT = THREAD_DETACH(VALUE) */
            static constexpr auto DETACH = data::func(LURAMAS_MAKE_BUILTIN_NAME("THREAD_DETACH"), 1, 1);
      } // namespace THREAD

      namespace DEVICE {

            /* (Enable device) RESULT = DEVICE_ENABLE(DEVICE) */
            static constexpr auto ENABLE = data::func(LURAMAS_MAKE_BUILTIN_NAME("DEVICE_ENABLE"), 1, 1);

            /* (Disable device) RESULT = DEVICE_DISABLE(DEVICE) */
            static constexpr auto DISABLE = data::func(LURAMAS_MAKE_BUILTIN_NAME("DEVICE_DISABLE"), 1, 1);

            /* (Add device) RESULT = DEVICE_ADD(DEVICE) */
            static constexpr auto ADD = data::func(LURAMAS_MAKE_BUILTIN_NAME("DEVICE_ADD"), 1, 1);

            /* (Remove device) RESULT = DEVICE_REMOVE(DEVICE) */
            static constexpr auto REMOVE = data::func(LURAMAS_MAKE_BUILTIN_NAME("DEVICE_REMOVE"), 1, 1);
      } // namespace DEVICE

      namespace RETURN {

            /* (Change return address to n) RESULT = RETURN_CHANGE(PAGE_ID) */
            static constexpr auto CHANGE = data::func(LURAMAS_MAKE_BUILTIN_NAME("RETURN_CHANGE"), 1, 1);

            /* (Gets return address) RESULT = RETURN_GET() */
            static constexpr auto GET = data::func(LURAMAS_MAKE_BUILTIN_NAME("RETURN_GET"), 0, 1);
      } // namespace RETURN

      namespace INTERNAL_REGISTER {

            /* (Store internal register) RESULT = INTERNAL_REGISTER_STORE(ID, VALUE)  */
            static constexpr auto STORE = data::func(LURAMAS_MAKE_BUILTIN_NAME("INTERNAL_REGISTER_STORE"), 2, 1);

            /* (Gets internal register) RESULT = INTERNAL_REGISTER_GET(ID) */
            static constexpr auto GET = data::func(LURAMAS_MAKE_BUILTIN_NAME("INTERNAL_REGISTER_GET"), 1, 1);
      } // namespace INTERNAL_REGISTER

      namespace EXTERNAL_REGISTER {

            /* (Store external register) RESULT = EXTERNAL_REGISTER_STORE(ID, VALUE)  */
            static constexpr auto STORE = data::func(LURAMAS_MAKE_BUILTIN_NAME("EXTERNAL_REGISTER_STORE"), 2, 1);

            /* (Gets external register) RESULT = EXTERNAL_REGISTER_GET(ID) */
            static constexpr auto GET = data::func(LURAMAS_MAKE_BUILTIN_NAME("EXTERNAL_REGISTER_GET"), 1, 1);
      } // namespace EXTERNAL_REGISTER

      namespace EXCEPTION {

            /* (Throw exception) RESULT = EXCEPTION_THROW(VALUE) */
            static constexpr auto THROW = data::func(LURAMAS_MAKE_BUILTIN_NAME("EXCEPTION_THROW"), 1, 1);

            /* (Catch exception) RESULT = EXCEPTION_CATCH(VALUE) */
            static constexpr auto CATCH = data::func(LURAMAS_MAKE_BUILTIN_NAME("EXCEPTION_CATCH"), 1, 1);

            /* (Clear exception) RESULT = EXCEPTION_CLEAR(VALUE) */
            static constexpr auto CLEAR = data::func(LURAMAS_MAKE_BUILTIN_NAME("EXCEPTION_CLEAR"), 1, 1);

            /* (Get exception) RESULT = EXCEPTION_GET(VALUE) */
            static constexpr auto GET = data::func(LURAMAS_MAKE_BUILTIN_NAME("EXCEPTION_GET"), 1, 1);

            /* (Enable exception) RESULT = EXCEPTION_ENABLE(VALUE) */
            static constexpr auto ENABLE = data::func(LURAMAS_MAKE_BUILTIN_NAME("EXCEPTION_ENABLE"), 1, 1);

            /* (Disable exception) RESULT = EXCEPTION_DISABLE(VALUE) */
            static constexpr auto DISABLE = data::func(LURAMAS_MAKE_BUILTIN_NAME("EXCEPTION_DISABLE"), 1, 1);
      } // namespace EXCEPTION

      namespace HINTER {

            /* (Hints to optimize context switching) RESULT = HINTER_CONTEXT_SWITCH(VALUE) */
            static constexpr auto CONTEXT_SWITCH = data::func(LURAMAS_MAKE_BUILTIN_NAME("HINTER_CONTEXT_SWITCH"), 1, 1);
      } // namespace HINTER

      namespace CONTROL_FLOW {

            /* (Indirect branch landing pad) RESULT = CONTROL_FLOW_INDIRECT_BR_PAD(VALUE) */
            static constexpr auto INDIRECT_BR_PAD = data::func(LURAMAS_MAKE_BUILTIN_NAME("CONTROL_FLOW_INDIRECT_BR_PAD"), 1, 1);
      } // namespace CONTROL_FLOW

      namespace RANDOMNESS {

            /* (Generates random number) RESULT = RANDOMNESS_RANDOM(VALUE) */
            static constexpr auto RANDOM = data::func(LURAMAS_MAKE_BUILTIN_NAME("RANDOMNESS_RANDOM"), 1, 1);

            /* (Random seed for random number generator) RESULT = RANDOMNESS_SEED(VALUE) */
            static constexpr auto SEED = data::func(LURAMAS_MAKE_BUILTIN_NAME("RANDOMNESS_SEED"), 1, 1);
      } // namespace RANDOMNESS

      namespace DESCRIPTOR {

            /* (Enable descriptor table) RESULT = DESCRIPTOR_ENABLE(TABLE_ID) */
            static constexpr auto ENABLE = data::func(LURAMAS_MAKE_BUILTIN_NAME("DESCRIPTOR_ENABLE"), 1, 1);

            /* (Disable descriptor table) RESULT = DESCRIPTOR_DISABLE(TABLE_ID) */
            static constexpr auto DISABLE = data::func(LURAMAS_MAKE_BUILTIN_NAME("DESCRIPTOR_DISABLE"), 1, 1);

            /* (Add descriptor entry) RESULT = DESCRIPTOR_ADD(TABLE_ID, ENTRY) */
            static constexpr auto ADD = data::func(LURAMAS_MAKE_BUILTIN_NAME("DESCRIPTOR_ADD"), 2, 1);

            /* (Get descriptor table) RESULT = DESCRIPTOR_CLEAR(TABLE_ID) */
            static constexpr auto GET = data::func(LURAMAS_MAKE_BUILTIN_NAME("DESCRIPTOR_GET"), 1, 1);

            /* (Remove descriptor entry) RESULT = DESCRIPTOR_REMOVE(TABLE_ID, ENTRY_ID) */
            static constexpr auto REMOVE = data::func(LURAMAS_MAKE_BUILTIN_NAME("DESCRIPTOR_REMOVE"), 2, 1);

            /* (Load descriptor table into active state) RESULT = DESCRIPTOR_LOAD(TABLE_ID) */
            static constexpr auto LOAD = data::func(LURAMAS_MAKE_BUILTIN_NAME("DESCRIPTOR_LOAD"), 1, 1);

            /* (Clear descriptor table) RESULT = DESCRIPTOR_CLEAR(TABLE_ID) */
            static constexpr auto CLEAR = data::func(LURAMAS_MAKE_BUILTIN_NAME("DESCRIPTOR_CLEAR"), 1, 1);

            /* (Read descriptor entry) RESULT = DESCRIPTOR_READ_FIELD(TABLE_ID, ENTRY_ID) */
            static constexpr auto READ_FIELD = data::func(LURAMAS_MAKE_BUILTIN_NAME("DESCRIPTOR_READ_FIELD"), 2, 1);

            /* (Write descriptor entry field) RESULT = DESCRIPTOR_SET_FIELD(TABLE_ID, ENTRY_ID, VALUE) */
            static constexpr auto SET_FIELD = data::func(LURAMAS_MAKE_BUILTIN_NAME("DESCRIPTOR_SET_FIELD"), 3, 1);
      } // namespace DESCRIPTOR
} // namespace luramas::builtins