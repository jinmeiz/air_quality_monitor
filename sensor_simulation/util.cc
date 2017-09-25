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

// send
void send_targets(const std::string  prometheus_url, const std::string  producer_url,
    const std::string  port_number, const std::string sensor_id) {
  CURL *curl;
  CURLcode res;

  curl_global_init(CURL_GLOBAL_ALL);

  // get a curl handle
  curl = curl_easy_init();
  if(curl) {
    /* First set the URL that is about to receive our POST. This URL can
       just as well be a https:// URL if that is what should receive the
       data. */
    const std::string prometheus_address = "http://" + prometheus_url;
    std::cout <<
    curl_easy_setopt(curl, CURLOPT_URL, prometheus_address.c_str());
    /* Now specify the POST data */
    const std::string post_data = "producer_address=" + producer_url
        + "&port_number=" + port_number + "&sensor_id=" + sensor_id;
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data.c_str());

    /* Perform the request, res will get the return code */
    res = curl_easy_perform(curl);
    /* Check for errors */
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));

    /* always cleanup */
    curl_easy_cleanup(curl);
  }
  curl_global_cleanup();
}

sensor_location generate_location() {
  // randomly generate location
  std::default_random_engine generator(std::random_device{}());
  std::uniform_int_distribution<int> region_dist(1, 5);
  std::uniform_int_distribution<int> area_dist(1, 30);
  int region = region_dist(generator);
  int area = area_dist(generator);

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
  auto& gauge_family = BuildGauge()
                             .Name(name)
                             .Help(help_label)
                             .Labels({{"sensor_id", sensor_id_}})
                             .Register(*registry);

  return gauge_family.Add({{"region", location_.region}, {"area", location_.area}});
}

