#!/bin/bash

# instructions:
# move script to build directory
# run: ./generate_ports.sh PORT_NUM_START PORT_NUM_END SENSOR_PREFIX
# terminate all jobs: killall producer

# Prometheus server public dns
PROM_URL="ec2-34-213-172-41.us-west-2.compute.amazonaws.com:8080"
# producer public dns
PRODUCER_URL="ec2-52-37-110-1.us-west-2.compute.amazonaws.com"

for ((i=$1; i<=$2; i++))
do
    echo "$PROM_URL" "$PRODUCER_URL" "$i" "$3$i"
    #./producer "$PROM_URL" "$PRODUCER_URL" "$i" "$SENSOR_PREFIX$i" & 
done

# count the number of targets
echo "number of targets so far" `ps -f | grep producer | wc -l`

exit 0
