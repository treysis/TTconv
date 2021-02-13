#!/bin/sh

echo "Creating fifos..."
mkfifo /var/run/gpspipe
mkfifo /var/run/gpspip2

echo "Adjusting permissions..."
chmod 0666 /var/run/gpspipe
chmod 0666 /var/run/gpspip2

echo "Stopping GPSD..."
systemctl stop gpsd.socket
systemctl stop gpsd.service

echo "All ready!"

