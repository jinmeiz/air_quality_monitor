#!/bin/bash

# this script generate targets information
# and send it to a intermediate server that
# generate target json file for prometheus server

# instructions:
# move this script to the build directory of sensor_simulation
# run: ./generate_ports.sh [PORT_NUM_START] [PORT_NUM_END] [SENSOR_PREFIX]
# terminate all jobs: killall producer

# Prometheus server url or public dns on aws
# example on aws
PROM_URL="<public dns>:8080"
# example on mac os
#PROM_URL="localhost:8080"
# producer url or public dns
# example on aws
PRODUCER_URL="<public dns>"
# example on mac os
#PRODUCER_URL="localhost"

for ((i=$1; i<=$2; i++))
do
    #echo "$PROM_URL" "$PRODUCER_URL" "$i" "$3$i"

# sleep periodically to avoid overwhelm the network 
    if (($i % 100 == 0))
    then
        echo "$i sleep for 5 seconds"
        sleep 5
    fi
    ./producer "$PROM_URL" "$PRODUCER_URL" "$i" "$3$i" &
done

# count the number of targets
echo "number of targets so far" `ps -f | grep producer | wc -l`

exit 0
