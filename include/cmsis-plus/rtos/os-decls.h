/*
 * This file is part of the µOS++ distribution.
 *   (https://github.com/micro-os-plus)
 * Copyright (c) 2016 Liviu Ionescu.
 * Copyright (c) 2013 ARM LIMITED
 *
 * µOS++ is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, version 3.
 *
 * µOS++ is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CMSIS_PLUS_RTOS_OS_DECLS_H_
#define CMSIS_PLUS_RTOS_OS_DECLS_H_

// ----------------------------------------------------------------------------

#if defined(__cplusplus)

/**
 * @brief Tell the world that CMSIS++ is in use.
 * @details
 * Macro to inform including files that CMSIS++ RTOS
 * definitions are available.
 */
#define OS_USE_CMSIS_PLUS

#include <cstdint>
#include <cstddef>
#include <cerrno>

// Include the application specific definitions.
#include <cmsis-plus/rtos/os-app-config.h>
// Include the non-portable portable types, enums and constants declarations.
#include <cmsis-plus/rtos/port/os-decls.h>

// ----------------------------------------------------------------------------

/**
 * @brief System namespace.
 */
namespace os
{
  /**
   * @brief RTOS namespace.
   */
  namespace rtos
  {
    // ------------------------------------------------------------------------

    /**
     * @brief Type of values returned by RTOS functions.
     * @details
     * For error processing reasons, most CMSIS++ RTOS functions
     * return a numeric result, which, according to POSIX,
     * when the call was successful, must be `0`
     * (`result::ok`) or an error code defined in `<errno.h>` otherwise.
     */
    using result_t = uint32_t;

    /**
     * @brief Values returned by RTOS functions.
     * @details
     * This namespace is dedicated to grouping all
     * status code values returned by CMSIS++ RTOS functions.
     *
     * However, CMSIS++ favours POSIX error codes, so,
     * except a few enumerated values, most of them are exactly those
     * defined by POSIX, in the
     * `<errno.h>` header, and are not redefined here.
     *
     * Currently in use are:
     * - `EPERM` - Operation not permitted. An attempt was made to perform
     * an operation limited to processes with appropriate privileges
     * or to the owner of a file or other resource. In CMSIS++ this
     * usually means that the call is not available in handler mode.
     * - `EINVAL` - Invalid argument. Some invalid argument was supplied;
     * - `EAGAIN` - Resource temporarily unavailable. This is a temporary
     * condition and later calls to the same routine may complete normally.
     * In CMSIS++ case, this usually means that a call to `try_xxx()`
     * found the resource busy.
     * - `ENOTRECOVERABLE` - State not recoverable. In CMSIS++ this
     * usually means an unrecoverable error occurred.
     * - `EDEADLOCK` - Resource deadlock would occur. An attempt was made
     * to lock a system resource that would have resulted in a deadlock
     * situation.
     * - `EMSGSIZE` - Message too large. A message sent on a transport
     * provider was larger than an internal message buffer or some other
     * network limit, or inappropriate message buffer length.
     * - `EBADMSG` - Bad message. The implementation has detected a
     * corrupted message.
     * - `EINTR` - Interrupted function call. In CMSIS++ this
     * usually mens that a thread waiting for a message is waken
     * before the event or the timeout occurred, at user request.
     * - `ETIMEDOUT` - Operation timed out. The time limit associated
     * with the operation was exceeded before the operation completed.
     * - `EOWNERDEAD` - Previous owner died. The owner of a robust mutex
     * terminated while holding the mutex lock.
     *
     * @par Example
     *
     * @code{.cpp}
     * void
     * func (void)
     * {
     *    Mutex mx;
     *    ...
     *    result_t res = mx.try_lock();
     *    if (res == result::ok)
     *      {
     *        // All is well, mutex locked.
     *      }
     *    else if (res == EAGAIN)
     *      {
     *        // Mutex busy, try again later.
     *      }
     * }
     * @endcode
     *
     */
    namespace result
    {
      /**
       * @brief Custom enumerated values.
       * @details
       * There are not many custom values returned by
       * CMSIS++ RTOS functions, currently there is only one,
       * `ok`, represented by `0`.
       *
       * If more custom codes will be needed and are not present in POSIX,
       * this is the place where to add them. Just be sure their numeric
       * values do not overlap POSIX values (check for a definition with
       * the last allocated POSIX error number).
       */
      enum
        : result_t
          {
            /**
             * @brief Function completed; no errors or events occurred.
             */
            ok = 0,

      };
    } /* namespace result */

    // ------------------------------------------------------------------------

    /**
     * @brief %Clock namespace.
     * @ingroup cmsis-plus-rtos
     */
    namespace clock
    {

      /**
       * @brief Type of variables holding timer ticks.
       * @details
       * A numeric type intended to hold a number of SysTick ticks.
       */
      using systicks_t = uint32_t;

      /**
       * @brief Type of variables holding timer durations.
       * @details
       * A numeric type intended to hold a generic duration, either in ticks
       * or in seconds.
       */
      using duration_t = uint32_t;

      /**
       * @brief Type of variables holding time stamps.
       * @details
       * A numeric type intended to hold a generic timestamp, either in ticks
       * or in seconds.
       */
      using timestamp_t = uint64_t;

      using offset_t = int64_t;

    }

    //using DoubleListNodeClock = DoubleListNodeTimestamp<clock::timestamp_t>;
    //using Waiting_threads_list3 = Waiting_threads_list2<DoubleListNodeClock>;

    // ------------------------------------------------------------------------

    /**
     * @brief Scheduler namespace.
     * @ingroup cmsis-plus-rtos
     */
    namespace scheduler
    {
      /**
       * @brief Type of a variable holding scheduler status codes.
       * @details
       * Usually a boolean telling if the scheduler is
       * locked or not, but for recursive locks it might also be a
       * numeric counter.
       */
      using status_t = bool;

    } /* namespace scheduler */

    /**
     * @brief Interrupts namespace.
     */
    namespace interrupts
    {
      /**
       * @brief Type of a variable holding interrupts status.
       * @details
       * Usually an integer large enough to hold the CPU status register
       * where the interrupt status is stored.
       *
       * It is used to temporarily store the CPU status register
       * during critical sections.
       */
      using status_t = uint32_t;

    } /* namespace interrupts */

    // ----------------------------------------------------------------------

    /**
     * @brief Generic flags namespace.
     * @ingroup cmsis-plus-rtos
     */
    namespace flags
    {
      /**
       * @brief Type of a variable holding a flags mask.
       * @details
       * An unsigned type large enough to store all the flags, usually
       * 32-bits wide.
       *
       * Both thread signal flags and event flags use this definition.
       * @ingroup cmsis-plus-rtos
       */
      using mask_t = uint32_t;

      /**
       * @brief Type of a variable holding the flags mode.
       * @details
       * An unsigned type used to hold the mode bits passed to
       * functions returning flags.
       *
       * Both thread signal flags and event flags use this definition.
       * @ingroup cmsis-plus-rtos
       */
      using mode_t = uint32_t;

      /**
       * @brief Flags modes.
       * @details
       * Container for generic flags enumerations.
       * @ingroup cmsis-plus-rtos
       */
      namespace mode
      {
        /**
         * @brief Bits used to specify the flags mode.
         * @ingroup cmsis-plus-rtos
         */
        enum
          : mode_t
            {
              /**
               * @brief Return when all flags are set.
               */
              all = 1,

              /**
               * @brief Return when at least one flag is set.
               */
              any = 2,

              /**
               * @brief Ask for flags to be cleared after read.
               */
              clear = 4
        };
      } /* namespace mode */
    } /* namespace flags */

    /**
     * @brief %Thread namespace.
     */
    namespace thread
    {
      /**
       * @brief Type of a variable holding thread priorities.
       * @details
       * A numeric type used to hold thread priorities, affecting the thread
       * behaviour, like scheduling and thread wakeup due to events;
       * usually an unsigned 8-bits type.
       *
       * Higher values represent higher priorities.
       * @ingroup cmsis-plus-rtos
       */
      using priority_t = uint8_t;

      /**
       * @brief %Thread priorities namespace.
       * @details
       * The os::rtos::thread::priority namespace is a container for
       * priorities not restricted to an enumeration.
       * @ingroup cmsis-plus-rtos
       */
      namespace priority
      {
        /**
         * @brief Priorities pre-scaler.
         * @details
         * Decreasing this value narrows the range of allowed
         * priorities. It is recommended to keep it low to give the
         * scheduler a chance to optimise accesses to the ready list
         * with an array of priorities, which will require some
         * pointers and counters for each priority level.
         *
         * The default value of 4 gives the full range of 256 priorities;
         * 0 gives 16 priorities,
         * 1 gives 32 priorities, 2 gives 64 priorities, 3 gives 128
         * priorities.
         * @ingroup cmsis-plus-rtos
         */
        constexpr uint32_t range = 4;

        /**
         * @brief Main priorities, intermediate values also possible.
         * @ingroup cmsis-plus-rtos
         */
        enum
          : priority_t
            {
              /**
               * Undefined, thread not initialised.
               */
              none = 0,

              /**
               * System reserved for the IDLE thread.
               */
              idle = (1 << range),

              /**
               * Lowest available for user code.
               */
              lowest = (2 << range),

              low = (2 << range),

              below_normal = (4 << range),

              /**
               * Default priority.
               */
              normal = (6 << range),

              above_normal = (8 << range),

              high = (10 << range),

              realtime = (12 << range),

              /**
               * Highest available for user code.
               */
              highest = (((13 + 1) << range) - 1),

              /**
               * System reserved for the ISR deferred thread.
               */
              isr = (((14 + 1) << range) - 1),

              /**
               * Error.
               */
              error = (((15 + 1) << range) - 1)
        };
      } /* namespace priority */

      /**
       * @brief Type of a variable holding the thread state.
       * @details
       * An enumeration with the possible thread states. The enumeration
       * is restricted to one of these values.
       */
      using state_t = enum class state : uint8_t
        {
          /**
           * @brief Used to catch uninitialised threads.
           */
          undefined = 0,
          inactive = 1,
          ready = 2,
          running = 3,
          waiting = 4,
          /**
           * @brief Reuse possible if terminated or higher.
           */
          terminated = 5,      // Test for here up for reuse
          destroyed = 6
        };

      /**
       * @brief Type of a variable holding a signal set.
       * @details
       * An unsigned type large enough to store all the signal flags,
       * actually a reuse of the more generic flags mask type
       * @ref flags::mask_t.
       */
      using sigset_t = flags::mask_t;

      /**
       * @brief %Thread signals namespace.
       * @details
       * The os::rtos::thread::sig namespace is a container for
       * signal flags masks, which cannot be restricted to an enumeration..
       */
      namespace sig
      {
        /**
         * @brief Signal sets with special meaning.
         */
        enum
          : sigset_t
            {
              /**
               * @brief Special signal mask to represent any flag.
               */
              any = 0,

              /**
               * Special signal mask to represent all flags.
               */
              all = 0xFFFFFFFF,
        };
      } /* namespace sig */

      /**
       * @brief Thread function arguments.
       * @details
       * Type of thread function arguments.
       */
      using func_args_t = void*;

      /**
       * @brief Thread function.
       * @details
       * Type of thread functions. Useful to cast other similar types
       * to silence the compiler warnings.
       */
      using func_t = void* (*) (func_args_t args);

    } /* namespace thread */

    /**
     * @brief Stack namespace.
     */
    namespace stack
    {
      /**
       * @brief Type of a stack element.
       * @details
       * For alignment reasons, the stack is allocated in
       * larger chunks, usually 8-bytes long on Cortex-M cores.
       */
      using element_t = os::rtos::port::stack::element_t;

    } /* namespace stack */

    /**
     * @brief A convenience namespace to access the current running thread.
     * @ingroup cmsis-plus-rtos
     */
    namespace this_thread
    {
    }

    // ========================================================================

    /**
     * @brief User timer namespace.
     */
    namespace timer
    {
      /**
       * @brief Timer call back function arguments.
       */
      using func_args_t = void*;

      /**
       * @brief Entry point of a timer call back function.
       */
      using func_t = void (*) (func_args_t args);

      /**
       * @brief Timer run type.
       */
      using type_t = enum class run : uint8_t
        {
          /**
           * @brief Run only once.
           */
          once = 0,

          /**
           * @brief Run periodically.
           */
          periodic = 1      //
        };
    }

    // ========================================================================

    /**
     * @brief Condition variable namespace.
     */
    namespace condvar
    {

    }

    // ========================================================================

    /**
     * @brief Event flags namespace.
     */
    namespace evflags
    {

    }

    // ========================================================================

    /**
     * @brief Memory pool namespace.
     */
    namespace mempool
    {
      /**
       * @brief Type of memory pool size.
       * @details
       * A numeric value that can hold the maximum size of the
       * memory pool, usually a 16-bits unsigned value.
       */
      using size_t = uint16_t;

      /**
       * @brief Maximum pool size.
       * @details
       * A constant numeric value used to validate the pool size.
       */
      constexpr size_t max_size = (0 - 1);
    } /* namespace mempool */

    // ========================================================================

    /**
     * @brief Message queue namespace.
     */
    namespace mqueue
    {
      /**
       * @brief Type of queue size.
       * @details
       * A numeric value to hold the message queue size, usually
       * an 8-bits value, possibly a 16-bits value if longer
       * queues are needed.
       */
      using size_t = uint8_t;

      constexpr size_t max_size = 0xFF;

      using msg_size_t = uint16_t;

      constexpr msg_size_t max_msg_size = 0xFFFF;

      using index_t = size_t;

      constexpr index_t no_index = max_size;

      /**
       * @brief Type of message priority.
       * @details
       * A numeric value to hold the message priority, which
       * controls the order in which messages are added to the
       * queue (higher values represent higher priorities).
       */
      using priority_t = uint8_t;

      /**
       * @brief Default message priority.
       * @details
       * Use this value with `send()` if no special priorities are required.
       */
      constexpr priority_t default_priority = 0;

      /**
       * @brief Maximum message priority.
       * @details
       * The maximum value allowed by the type, usually used for
       * validation.
       */
      constexpr priority_t max_priority = 0xFF;

    } /* namespace mqueue */

    // ========================================================================

    /**
     * @brief %Mutex namespace.
     */
    namespace mutex
    {
      /**
       * @brief Type of mutex protocol.
       */
      using protocol_t = enum class protocol : uint8_t
        {
          /**
           * @brief Priority and scheduling not affected by mutex ownership.
           */
          none = 0,

          /**
           * @brief Inherit from highest priority thread.
           * @details
           * TODO: add
           */
          inherit = 1,

          /**
           * @brief Protect.
           * @details
           * TODO: add
           */
          protect = 2
        };

      /**
       * @brief Type of mutex robustness.
       */
      using robustness_t = enum class robustness : uint8_t
        {
          /**
           * @brief Normal robustness.
           */
          stalled = 0,
          /**
           * @brief Enhanced robustness.
           */
          robust = 1
        };

      /**
       * @brief Type of mutex behaviour.
       */
      using type_t = enum class type : uint8_t
        {
          /**
           * @brief Normal mutex behaviour.
           */
          normal = 0,
          /**
           * @brief Check mutex behaviour.
           */
          errorcheck = 1,
          /**
           * @brief Recursive mutex behaviour.
           */
          recursive = 2,

          _default = normal,
        };

      /**
       * @brief Type of mutex recursion counter.
       */
      using count_t = uint16_t;

      constexpr count_t max_count = 0xFFFF;

    } /* namespace mutex */

    /**
     * @brief %Semaphore namespace.
     */
    namespace semaphore
    {
      /**
       * @brief Type of semaphore counter.
       * @details
       * A numeric value enough to hold the semaphore counter,
       * usually a 16-bits signed value.
       */
      using count_t = int16_t;

      /**
       * @brief Maximum semaphore value.
       * @details
       * Used to validate the semaphore initial count and max count.
       */
      constexpr count_t max_count_value = 0x7FFF;

    } /* namespace semaphore */

    // ========================================================================

    /**
     * @brief Base class for named objects.
     * @headerfile os.h <cmsis-plus/rtos/os.h>
     */
    class Named_object
    {
    public:

      /**
       * @name Constructors & Destructor
       * @{
       */

      /**
       * @brief Create a named object.
       * @param [in] name Null terminated name. If `nullptr`, "-" is assigned.
       */
      Named_object (const char* name);

      /**
       * @cond ignore
       */
      Named_object (const Named_object&) = default;
      Named_object (Named_object&&) = default;
      Named_object&
      operator= (const Named_object&) = default;
      Named_object&
      operator= (Named_object&&) = default;
      /**
       * @endcond
       */

      /**
       * @brief Destroy the named object.
       */
      ~Named_object () = default;

      /**
       * @}
       * @name Public Member Functions
       * @{
       */

      /**
       * @brief Get name.
       * @par Parameters
       *  None.
       * @return A null terminated string.
       */
      const char*
      name (void) const;

      /**
       * @}
       */

    protected:

      /**
       * @name Private Member Variables
       * @{
       */

      /**
       * @brief Pointer to name.
       */
      const char* const name_;

      /**
       * @}
       */
    };
    // ========================================================================

    // Forward references.
    class Condition_variable;
    class Event_flags;
    class Memory_pool;
    class Message_queue;
    class Mutex;
    class Realtime_clock;
    class Semaphore;
    class Systick_clock;
    class Thread;
    class Timer;

  // ========================================================================
  } /* namespace rtos */
} /* namespace os */

// ===== Inline & template implementations ====================================

namespace os
{
  namespace rtos
  {
    // ------------------------------------------------------------------------

    /**
     * @details
     * All objects return a non-null string; anonymous objects
     * return `"-"`.
     */
    inline const char*
    Named_object::name (void) const
    {
      return name_;
    }

  // ========================================================================
  } /* namespace rtos */
} /* namespace os */

// ----------------------------------------------------------------------------

// Must be included after the declarations
#include <cmsis-plus/rtos/os-lists.h>

// ----------------------------------------------------------------------------

extern "C"
{

  /**
   * @brief Main thread.
   * @param argc Count of arguments.
   * @param argv Array of pointers to arguments.
   * @retval 0 The proram terminated normally.
   * @retval 1 The program terminated with an error.
   *
   * @details
   * The standard `main()` creates a dedicated thread to run this function.
   *
   * The returned value is used in semihosted tests, to inform the
   * host on the result of the test.
   */
  int
  os_main (int argc, char* argv[]);

}

// ----------------------------------------------------------------------------

// Required by os_assert_throw()
#include <cmsis-plus/iso/system_error>

/**
 * @brief Assert or return an error.
 * @details
 * As required by the ANSI standards, if `NDEBUG` is defined,
 * the assertion is disabled and if the condition is true, the
 * given error code is returned.
 */
#ifdef NDEBUG           /* ANSI standard */
#define os_assert_err(__e, __er) \
  do { if (!(__e)) return __er; } while (false)
#else
#define os_assert_err(__e, __er) assert(__e)
#endif

/**
 * @brief Assert or throw a system error exception.
 * @details
 * As required by the ANSI standards, if `NDEBUG` is defined,
 * the assertion is disabled and if the condition is true, a
 * ssytem error exception is thrown (which is replaced by an
 * `abort()` if exceptions are disabled).
 */
#ifdef NDEBUG           /* ANSI standard */
#define os_assert_throw(__e, __er) \
  do { if (!(__e)) os::estd::__throw_system_error(__er, #__e); } while (false)
#else
#define os_assert_throw(__e, __er) assert(__e)
#endif

// ----------------------------------------------------------------------------

#if !defined(OS_INTEGER_SYSTICK_FREQUENCY_HZ)
/**
 * @brief Default definition for the SysTick frequency, in Hz.
 * @details
 * Redefine it in `<os-app-config.h>` to the actual value.
 */
#define OS_INTEGER_SYSTICK_FREQUENCY_HZ                     (1000)
#endif

#if !defined(OS_INTEGER_RTOS_MAIN_STACK_SIZE_BYTES)
/**
 * @brief Default definition for the `main()` stack size, in bytes.
 * @details
 * Redefine it in `<os-app-config.h>` to the actual value.
 */
#define OS_INTEGER_RTOS_MAIN_STACK_SIZE_BYTES               (400)
#endif

#endif /* __cplusplus */

#endif /* CMSIS_PLUS_RTOS_OS_DECLS_H_ */