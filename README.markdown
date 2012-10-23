# BacklightCtl

Because xbacklight takes too long to execute, i decided to write my own really lightweight (<100 SLOC) utility that directly writes to the /sys/ filesystem.
## Building

BacklightCtl uses cmake to build, because I can't be bothered to figure out the arcane autotools. So sue me!
In a nutshell:

	$ mkdir Build && cd Build
	$ cmake ..
	$ make all
	
	(optional)
	# make install

If you want to package it or otherwise need a different PREFIX or install destination, try this:
	
	$ mkdir Build && cd Build
	$ cmake -DCMAKE_INSTALL_PREFIX:PATH=<your prefix> ..
	$ make all
	$ make DESTDIR=<your destination directory> install

keep in mind that &lt;your prefix&gt; probably has to be absolute (don't quote me on this), but &lt;your destination directory&gt; can be relative.

## Configuration

The config file is read from /etc/backlightctl.conf. It must contain exactly 2 lines. The first one points to the file controlling the brightness. The second line points to the file containing the maximal brightness. The file bundled with backlightctl will always be tailored to my personal laptop. (at the time of writing, a Samsung NP900X3C with Archlinux)

## Usage

BacklightCtl accepts as a command-line parameter either a percentage or a percentage delta. 

## Examples

	backlightctl 100

Sets the backlight to full.

	backlightctl -20

Decreases the backlight by 20 percent of the maximal value.

	backlightctl +20

Increases the backlight by 20 percent.

