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

// location stores the area and region information
struct sensor_location {
  std::string region;
  std::string area;
};


class gauge_families {
private:
  // location of the sensor
  sensor_location location_;
  // id of the sensor
  std::string sensor_id_;

public:
  // default constructor
  gauge_families() = default;
  
  // set the location for the sensor (randomly generated)
  // output: location_ - set to random value in a range
  void set_sensor_location();
  
  // set the id for the sensor
  // input: sensor_id
  // output: sensor_id_ - set to sensor_id
  void set_sensor_id(const std::string sensor_id);
  
  // generate different metrics with different labels
  // inputs: name - metric name
  //         help_label - annotation for metric
  //         registry - metric registry
  // return: a metric containing location and sensor id information
  Gauge& build_gauge(std::string name, std::string help_label,
      std::shared_ptr<Registry>& registry);
};

// send the target information to a server that generate json file for prometheus server
// inputs: server_url - URL of receiver
//         producer_url - URL of sensor
//         port_number  - port number of sensor's http server
//         sensor_id - ID of sensor
// output: POST data containing URL, port number of sensor's http server, and sensor ID
void send_targets(const std::string  server_url, const std::string  producer_url,
    const std::string  port_number, const std::string sensor_id);
#endif /* UTIL_H_ */
