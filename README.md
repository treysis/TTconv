# TTconv
TTconv v4 for TomTom Rider 2013 (also known as K4, v4, or v5)
by treysis (treysis@gmx.net)
------------------------------------------------------------------------

What does it do?

After April 7, 2019 the Rider 2013 isn't able to display the correct time
anymore and loses some functions because of this. The reason for this is
the GPS Week Number Rollover Event (WNRO) which happens every 19.7 years.
TTconv takes care of this.


Bugs?

This is the first version and it "just so" works. But I wanted to make it
available for everyone as fast as possible. The code of the utility is
very(!) very(!!) ugly(!!!). I haven't been coding in years. So it's possible
that there will be some bugs.

1. Should work now also after standby! But shows wrong time for some seconds.
   If signal disappears or if it stops working, manual start by additional
   menu called "TTconv" is possible.

2. I haven't tested it for long time. Maybe it will stop. Just restart as
   noted under 1.

3. I also haven't looked at CPU usage/battery drain. Please tell me if you
   find any unusual battery drain.

4. For a few seconds, the time will be 0:00:00 because I had to introduce
   some delays when starting the scripts and didn't have the time yet to
   optimize this process. I haven't checked yet how this might interfere
   with any logging. So don't be confused about very odd data points.

5. Won't work after the next WNRO Event on November 20, 2038. You'll be
   transported back to 2019. Maybe I will provide a solution (it's already
   in my head), but for now this has to suffice!


Installation?

Just unpack the archive to the main directory of the TomTom. It will then
start automatically. The start script (ttn) also includes the instructions
for starting MiniLog. So if you use MiniLog, it should work just like before.
If you are using minilog, you will have to overwrite the current "ttn" file
when extracting or add this line (preferentially to the beginning) of "ttn":

	/mnt/sdcard/fixdate/resetgps &

After standby you will have to manually start TTconv from the menu. Haven't
figured out yet how to restart automatically after standby.

------------------------------------------------------------------------

I hope this gives you many additional years of joy with the Rider 2013.

Also I have to stress that I am disappointed with TomTom. The device is still
officially supported, and the fix was not so difficult (for me it was, because
I was not used to coding anymore).
On the other hand, fortunately TomTom provided the precompiled toolchain
and uses Linux on the older devices which is the reason it was possible in the
first place to fix it without further help (there was also a bit of luck
involved in how every part of the system works together!).


Acknowledgements:

- Anuj Chauhan (and additions by Mithun Kumar, ayush2904)
https://www.geeksforgeeks.org/date-after-adding-given-number-of-days-to-the-given-date/
for providing a routine to add a specific number of days to a given date.

- Devendra Aaru/MADMAX/https://gist.github.com/DevNaga's source:
https://gist.github.com/DevNaga/fce8e166f4335fa777650493cb9246db
for calculating NMEA0183 checksums

- Users at StackOverflow.com
for answering my questions on named pipes, strings, pointers, and all
the other stuff I couldn't figure out on my own.

------------------------------------------------------------------------
Changelog:

v4 (27-04-2019):
-should work now for non-MiniLog users
-change in Orion.ini to not produce $GPZDA message (was only for testing)

v3 (27-05-2019):
-Adjusted ttn for non-Minilog-users (caused constant restart)

v2 (27-05-2019):
-Added resume after standby

v1 (26-05-2019):
-Initial version
