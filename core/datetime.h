/**************************************************************************/
/*                                                                        */
/*                              WWIV Version 5.x                          */
/*             Copyright (C)1998-2019, WWIV Software Services             */
/*                                                                        */
/*    Licensed  under the  Apache License, Version  2.0 (the "License");  */
/*    you may not use this  file  except in compliance with the License.  */
/*    You may obtain a copy of the License at                             */
/*                                                                        */
/*                http://www.apache.org/licenses/LICENSE-2.0              */
/*                                                                        */
/*    Unless  required  by  applicable  law  or agreed to  in  writing,   */
/*    software  distributed  under  the  License  is  distributed on an   */
/*    "AS IS"  BASIS, WITHOUT  WARRANTIES  OR  CONDITIONS OF ANY  KIND,   */
/*    either  express  or implied.  See  the  License for  the specific   */
/*    language governing permissions and limitations under the License.   */
/*                                                                        */
/**************************************************************************/
#ifndef __INCLUDED_CORE_DATETIME_H__
#define __INCLUDED_CORE_DATETIME_H__

#include <chrono>
#include <ctime>
#include <string>

#include "core/wwivport.h"

namespace wwiv {
namespace core {

time_t time_t_now();

daten_t daten_t_now();

/**
 * Constructs a daten_t from a date of the format "MM/DD/YY"
 */
daten_t date_to_daten(const std::string& datet);

std::string daten_to_wwivnet_time(daten_t t);
std::string time_t_to_wwivnet_time(time_t t);
daten_t time_t_to_daten(time_t t);

/**
 * Returns the current date as 'MM/DD/YY'
 */
std::string date();

/**
 * Returns the current date as 'MM/DD/YYYY'
 */
std::string fulldate();

/**
 * Returns the current time as 'HH:MM:SS'
 */
std::string times();

/** Displays dd as a human readable time */
std::string to_string(std::chrono::duration<double> dd);

class DateTime final {
public:
  [[nodiscard]] static DateTime from_time_t(time_t t) { return DateTime(t); }

  [[nodiscard]] static DateTime from_tm(tm* t) { return DateTime(t); }

  [[nodiscard]] static DateTime from_daten(daten_t t) {
    return from_time_t(static_cast<time_t>(t));
  }

  [[nodiscard]] static DateTime now();

  [[nodiscard]] int hour() const noexcept { return tm_.tm_hour; }
  [[nodiscard]] int minute() const noexcept { return tm_.tm_min; }
  [[nodiscard]] int second() const noexcept { return tm_.tm_sec; }

  /** Month starting at 1 for this DateTime */
  [[nodiscard]] int month() const noexcept { return tm_.tm_mon + 1; }

  /** Day starting at 1 for this DateTime */
  [[nodiscard]] int day() const noexcept { return tm_.tm_mday; }

  /** Year starting at 0 for this DateTime */
  [[nodiscard]] int year() const noexcept { return tm_.tm_year + 1900; }

  [[nodiscard]] int dow() const noexcept { return tm_.tm_wday; }

  /** Prints a date using the strftime format specified.  */
  [[nodiscard]] std::string to_string(const std::string& format) const;

  /** Prints a Date using asctime but without the trailing linefeed. */
  [[nodiscard]] std::string to_string() const;

  /** Returns this Datetime as a UNIX time_t */
  [[nodiscard]] time_t to_time_t() const noexcept { return t_; }

  /** Returns this Datetime as a WWIV BBS daten_t */
  [[nodiscard]] daten_t to_daten_t() const noexcept { return time_t_to_daten(t_); }

  /** Returns this Datetime as a POSIX tm structure. */
  [[nodiscard]] struct tm to_tm() const noexcept;

  /** Returns this Datetime as a time_point in the std::chrono::system_clock */
  [[nodiscard]] std::chrono::system_clock::time_point to_system_clock() const noexcept;

  friend DateTime operator+(DateTime lhs, std::chrono::duration<double> d);

  DateTime& operator+=(std::chrono::duration<double> d) {
    const auto du = std::chrono::duration_cast<std::chrono::seconds>(d);
    t_ += static_cast<time_t>(du.count());
    update_tm();
    return *this;
  }

  friend DateTime operator-(DateTime lhs, std::chrono::duration<double> d);

  DateTime& operator-=(std::chrono::duration<double> d) {
    const auto du = std::chrono::duration_cast<std::chrono::seconds>(d);
    t_ -= static_cast<time_t>(du.count());
    update_tm();
    return *this;
  }

  friend bool operator<(const DateTime& lhs, const DateTime& rhs) {
    if (lhs.t_ == rhs.t_) {
      return lhs.millis_ < rhs.millis_;
    } else {
      return lhs.t_ < rhs.t_;
    }
  }

  friend bool operator==(const DateTime& lhs, const DateTime& rhs);
  friend bool operator!=(const DateTime& lhs, const DateTime& rhs);

  friend bool operator>(const DateTime& lhs, const DateTime& rhs); 

  friend bool operator<=(const DateTime& lhs, const DateTime& rhs);

  friend bool operator>=(const DateTime& lhs, const DateTime& rhs);

  DateTime();
  ~DateTime() = default;

private:
  explicit DateTime(std::chrono::system_clock::time_point t);
  explicit DateTime(tm* t);
  explicit DateTime(time_t t);
  /** Updates the tm_ structure, should be called anytime the time_t value is changed */
  void update_tm() noexcept;

  time_t t_;
  tm tm_{};
  int millis_;
};

DateTime parse_yyyymmdd(const std::string& date_str);
DateTime parse_yyyymmdd_with_optional_hms(const std::string& date_str);

} // namespace core
} // namespace wwiv

#endif // __INCLUDED_CORE_DATETIME_H__
