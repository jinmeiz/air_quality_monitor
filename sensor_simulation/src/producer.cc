/*
 * producer.cc: simulate air sensor data
 *              and send target information to a server
 * run: 
 * ./producer [server url] [producer url] [port number] [sensor id]
 *
 *  Created on: Sep 18, 2017
 *      Author: jinmei
 */

#include <chrono>
#include <map>
#include <memory>
#include <string>
#include <thread>
#include <random>

#include <prometheus/exposer.h>
#include <prometheus/registry.h>

#include "util.h"

int main(int argc, char** argv) {
  using namespace prometheus;

  // the number of inputs is four:
  // 1st argument: server address (URL, e.g. prometheus server url)
  // 2nd argument: producer address (URL)
  // 3rd argument: producer port number
  // 4th argument: sensor id
  if (argc != 5) {
    std::cout << "Inputs are not correct (they should be "
        << "Pserver address, producer address, producer port number, and sensor id."
        << std::endl;
    return 1;
  }
  const std::string prometheus_url = argv[1];
  const std::string producer_url = argv[2];
  const std::string port_number = argv[3];
  const std::string sensor_id = argv[4];

  // create an http server running on a port (sensor http endpoit)
  auto&& exposer = Exposer{port_number};

  // send the target (url:port_number) to a server that generate target json file for
  // prometheus server
  send_targets(prometheus_url, producer_url, port_number, sensor_id);

  // create a metric registry with component=main labels applied to all its
  // metrics
  auto registry = std::make_shared<Registry>();

  // add new gauge families to the registry (families combine values with the
  // same name, but distinct label dimenstions)
  gauge_families gauges = gauge_families();
  
  // set the location and id for the sensor
  // TODO: need add check to add location and sensor id
  gauges.set_sensor_location();
  gauges.set_sensor_id(sensor_id);
  
  // add key:value labels to the metrics
  auto& co2_gauge = gauges.build_gauge("CO2_ppm",
      "CO2 concentration in parts per million", registry);
  auto& co_gauge = gauges.build_gauge("CO_ppm",
      "CO concentration in parts per million", registry);
  auto& no2_gauge = gauges.build_gauge("NO2_ppb",
      "NO2 concentration in parts per billion", registry);
  auto& so2_gauge = gauges.build_gauge("SO2_ppb",
      "SO2 concentration in parts per billion", registry);
  auto& pm25_gauge = gauges.build_gauge("pm25_ugm3",
      "Particulate matter with diameters 2.5 micrometers in ug/m3", registry);
  auto& pm10_gauge = gauges.build_gauge("pm10_ugm3",
      "Particulate matter with diameters 10 micrometers in ug/m3", registry);
  auto& temperature_gauge = gauges.build_gauge("temperature_C",
      "Temperature in Celsius", registry);

  // ask the exposer to scrape the registry on incoming scrapes
  exposer.RegisterCollectable(registry);

  // create random number generators for different metrics
  std::default_random_engine generator(std::random_device{}());
  std::uniform_real_distribution<double> co2_dist(355.07, 455.07);
  std::uniform_real_distribution<double> co_dist(0.0, 9.0);
  std::uniform_real_distribution<double> no2_dist(45.0, 100.0);
  std::uniform_real_distribution<double> so2_dist(0.0, 70.0);
  std::uniform_real_distribution<double> pm25_dist(5.0, 12.0);
  std::uniform_real_distribution<double> pm10_dist(30.0, 120.0);
  std::uniform_real_distribution<double> temperature_dist(-10.0, 40.0);

  // push the metric data to the http server
  for (;;) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    // change the gauge by one (second)
    co2_gauge.Set(co2_dist(generator));
    co_gauge.Set(co_dist(generator));
    no2_gauge.Set(no2_dist(generator));
    so2_gauge.Set(so2_dist(generator));
    pm25_gauge.Set(pm25_dist(generator));
    pm10_gauge.Set(pm10_dist(generator));
    temperature_gauge.Set(temperature_dist(generator));

  }
  return 0;
}


