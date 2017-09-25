#!/bin/bash

<path_to_prometheus>/prometheus --config.file=sensor-server.yml --config.file=sensor-server.yml --web.listen-address ":9090" --storage.local.num-fingerprint-mutexes=81920
