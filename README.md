# TTconv
TTconv for TomTom Rider 2013 (also known as K4, v4, or v5) and TomTom
units with GL1 (Global Locate Hammerhead) GPS chip
by treysis (treysis@gmx.net)
------------------------------------------------------------------------
DISCLAIMER:
Use of this patch is at your own risk! While I don't see any way how
this patch could cause harm to your device (e.g. there is nothing writing
to flash all the time which would degrade flash memory over time) I take
no responsibility!
------------------------------------------------------------------------

What does it do?

After April 7, 2019 the Rider 2013 and devices with GL1 GPS chip (e.g.
ONE 3rd) aren't able to display the correct time anymore and lose some
functions because of this. The reason for this is the GPS Week Number
Rollover Event (WNRO) which happens every 19.7 years.
TTconv takes care of this.


Bugs?

This version seems to work fine as it is now. But I wanted to make it
available for everyone as fast as possible, so it is still missing long
time tests. USE AT YOUR OWN RISK! NO GUARANTEES FOR NOTHING (but it
shouldn't be possible to break something the way it works and it can be
completely reverted!).
The code of the utility is very(!) very(!!) ugly(!!!). I haven't been
coding in years. So it's possible that there will be some bugs.

1. Doesn't seem to work with NavCore 9.541. Use previous version!

2. Should work now also after standby! But shows wrong time for some seconds.
   If signal disappears or if it stops working, manual start by additional
   menu called "TTconv" is possible. Not sure if this is fixible, but seems
   to be just a minor inconvience if any at all. I haven't checked
   thoroughly how this might interfere with any logging, but so far it
   looked good. But don't be confused if you encounter very odd data points:
   E.g. MiniLog will record some very weird dates during the first seconds
   after startup.

3. I haven't tested it for long time. Maybe it will stop. Just restart as
   noted under 1.

4. I also haven't looked at CPU usage/battery drain. Please tell me if you
   find any unusual battery drain.

5. Won't work after the next WNRO Event on November 20, 2038. You'll be
   transported back to 2019. But the time should stay correct. But maybe
   the current GPS won't even be around anymore. Maybe I will provide a
   solution (it's already in my head), but for now this has to suffice!

6. Small memory leak causes increase of RAM usage of 2 KB per hour.


Installation?

Just unpack the archive to the main directory of the TomTom. It will then
start automatically. In version v7 I added two menu options: "MiniLog Yes"
and "MiniLog No". If you are a user of Joghurt's tool "MiniLog" or "Height",
you should select "Yes", which will activate it. Otherwise select "No". The
device will then reboot and both menu icons are deleted automatically.

Advanced users:
If you are using another tool that uses "ttn", you will have
to overwrite the current "ttn" file when extracting or add this line
(preferentially to the beginning) of "ttn":

	/mnt/sdcard/fixdate/resetgps &


Uninstallation?

If you are not happy with the result or you encounter some serious bugs,
the easiest way is to delete the "ttn" file. This will prevent my patch
from starting and your TomTom should work as before (but with the broken
time of course). If you want to clean up your device, just delete the
files that came with this patch. But leaving them on the device will only
occupy a few kilobyte and won't have any effect on the operation of the
device.

------------------------------------------------------------------------

I hope this gives you many additional years of joy with the Rider 2013
and the other GL1 personal navigation devices by TomTom.

Also I have to stress that I am disappointed with TomTom. The Rider 2013
is still officially supported, and the fix was not so difficult (for me it
was, because I was not used to coding anymore).
On the other hand, fortunately TomTom provided the precompiled toolchain
and uses Linux on the older devices which is the reason it was possible in
the first place to fix it without further help (there was also a bit of
luck involved in how every part of the system works together!).


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

v7 (29-08-2019):
-merged with patch for units with GL1 GPS chip
-added menu options to chose if you are MiniLog user or not
-updated readme

v6 (28-05-2019):
-added some sanity checks to ttconv and possibly prevent possible weird
 data points when recording tracks when GPS signal is lost (e.g. passing
 through a tunnel)
-preparation for merging with patch for GL1 devices

v5 (27-05-2019):
-updated/fixed readme, removed v? from file (annoying to update :) )

v4 (27-05-2019):
-should work now for non-MiniLog users
-change in Orion.ini to not produce $GPZDA message (was only for testing)

v3 (27-05-2019):
-Adjusted ttn for non-Minilog-users (caused constant restart)

v2 (27-05-2019):
-Added resume after standby

v1 (26-05-2019):
-Initial version
