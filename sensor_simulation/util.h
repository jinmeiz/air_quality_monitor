/*
 * util.h
 *
 *  Created on: Sep 19, 2017
 *      Author: jinmei
 */

#ifndef UTIL_H_
#define UTIL_H_

#include <string.h>
#include <memory>
#include <prometheus/registry.h>
#include "prometheus/gauge_builder.h"

using namespace prometheus;

// location stores the latitude and longitude
struct sensor_location {
  std::string region;
  std::string area;
};

class gauge_families {
private:
  sensor_location location_;
  std::string sensor_id_;

  detail::GaugeBuilder co2_;

public:
  gauge_families() = default;
  void set_sensor_location();
  void set_sensor_id(const std::string sensor_id);
  Gauge& build_gauge(std::string name, std::string help_label,
      std::shared_ptr<Registry>& registry);
};

void send_targets(const std::string  prometheus_url, const std::string  producer_url,
    const std::string  port_number, const std::string sensor_id);
#endif /* UTIL_H_ */
