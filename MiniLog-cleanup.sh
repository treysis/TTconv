#!/bin/sh

# This script cleans up recorded MiniLog tracks,
# except for the most recent 30 files.

limit=30
Cnt=0
for line in `ls -t /mnt/sdcard/MiniLog/*.log`
do
  if (test $Cnt -gt $limit)
    then
      rm $line
  fi
  Cnt=`expr $Cnt + 1`
done
