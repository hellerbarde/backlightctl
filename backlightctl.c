/*  
    (MIT/X11 License)
    
    Copyright (c) 2012 Philip Stark
 
    Permission is hereby granted, free of charge, to any person obtaining
    a copy of this software and associated documentation files (the
    "Software"), to deal in the Software without restriction, including
    without limitation the rights to use, copy, modify, merge, publish,
    distribute, sublicense, and/or sell copies of the Software, and to
    permit persons to whom the Software is furnished to do so, subject to
    the following conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
    IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
    CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
    TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
    SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <unistd.h>
#include <stdio.h>

int main(int argc, char** argv)
{
	if (getuid() != 0){
		printf("You need to be a superuser to use this program.\n");
		return 5;
	}

	static const char* CONFIG_PATH = "/etc/backlightctl.conf";
	FILE *config, *brightness, *max_brightness;
	char brightness_path[1024];
	char max_brightness_path[1024];
	int cur_br, max_br, delta_perc, set_perc, set_br;

	config = fopen( CONFIG_PATH, "r" );
	if (config == NULL) {
		return 2;
	}

	fscanf(config, "%s\n%s", brightness_path, max_brightness_path);
	fclose(config);


	brightness     = fopen(brightness_path, "r+");
	if (brightness == NULL) {
		return 3;
	}

	max_brightness = fopen(max_brightness_path, "r");
	if (max_brightness == NULL) {
		return 4;
	}

	fscanf(brightness, "%d", &cur_br);
	fscanf(max_brightness, "%d", &max_br);
	fclose(max_brightness);

	set_perc = (int) (((float)cur_br / (float)max_br) * 100.0 + 0.5f);

	if (argc < 2) {
		printf("%d\n", set_perc);
		return 0;
	} 
	else if (argc == 2) {
		if (strcmp(argv[1], "-h") == 0) {
			printf("Usage: %s [[{+,-}]PERCENTAGE]\n\t when no parameters are given, the current percentage is printed out.\n", argv[0]);
			return 0;
		}
		else if (sscanf(argv[1], "%d", &delta_perc) != 0) {
			if (argv[1][0] == '+'){
				//return 3;
				/* this is incrementing */
				set_perc += delta_perc;
				set_perc = (set_perc > 100) ? 100 : set_perc;
			}
			else if (argv[1][0] == '-') {
				/* this is decrementing */
				set_perc += delta_perc;
				set_perc = (set_perc < 1) ? 1 : set_perc;
			}
			else {
				/* this is setting */
				set_perc = delta_perc;
				set_perc = (set_perc > 100) ? 100 : set_perc;
				set_perc = (set_perc < 1) ? 1 : set_perc;
			}
		}
		else {
			/* the failz... */
			printf("invalid parameter\n");
			return 1;
		}
	}

	/* here we'll set the value in the file */
	set_br = (int) ((((float)set_perc)/100.0) * ((float)max_br));
	set_br = (set_br < 50) ? 50 : set_br;
	//printf("percentage set: %d\nvalue set: %d/%d\n", set_perc, set_br, max_br);
	fprintf(brightness, "%d\n", set_br);

	fclose(brightness);
	return 0;
}