/*
 * util.cc
 *
 *  Created on: Sep 19, 2017
 *      Author: jinmei
 */

#include <random>
#include <stdio.h>
#include <curl/curl.h>

#include "util.h"

void send_targets(const std::string  prometheus_url, const std::string  producer_url,
    const std::string  port_number, const std::string sensor_id) {
  CURL *curl;
  CURLcode res;

  curl_global_init(CURL_GLOBAL_ALL);

  // get a curl handle
  curl = curl_easy_init();
  if(curl) {
    // set the URL that is about to receive our POST
    const std::string prometheus_address = "http://" + prometheus_url;
    std::cout <<
    curl_easy_setopt(curl, CURLOPT_URL, prometheus_address.c_str());
    
    // specify the POST data
    const std::string post_data = "producer_address=" + producer_url
        + "&port_number=" + port_number + "&sensor_id=" + sensor_id;
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data.c_str());

    // perform the request, res will get the return code
    res = curl_easy_perform(curl);
    
    // check for errors
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));

    // cleanup
    curl_easy_cleanup(curl);
  }
  curl_global_cleanup();
}

sensor_location generate_location() {

  // create random number (in a range) generator for location
  std::default_random_engine generator(std::random_device{}());
  std::uniform_int_distribution<int> region_dist(1, 5);
  std::uniform_int_distribution<int> area_dist(1, 30);
  
  // randomly generate location
  int region = region_dist(generator);
  int area = area_dist(generator);

  // set the area and region for the location
  sensor_location curr_location{std::to_string(region), std::to_string(area)};
  return curr_location;
}

void gauge_families::set_sensor_location() {
  location_ = generate_location();
}

void gauge_families::set_sensor_id(const std::string sensor_id) {
  sensor_id_ = sensor_id;
}

Gauge& gauge_families::build_gauge(std::string name, std::string help_label,
    std::shared_ptr<Registry>& registry) {
  
  // create the metric with sensor_id label
  auto& gauge_family = BuildGauge()
                             .Name(name)
                             .Help(help_label)
                             .Labels({{"sensor_id", sensor_id_}})
                             .Register(*registry);

  // add more location labels
  return gauge_family.Add({{"region", location_.region}, {"area", location_.area}});
}

