/*  RMT Pixel Example 
    Copyright (C) 2020  Sebastian Tilders

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>
*/
#include <RMT_Pixel.h>


// Number of leds on connected strip
#define NUM_LEDS 7

// Order of led strip (RMT_PIXEL_GRB or RMT_PIXEL_RGB)
#define COLOR_ORDER RMT_PIXEL_GRB

// Pin which drives led strip
#define GPIO_PIN 18

// Switching delay in ms
#define DELAY 500

// Helper to convert millisecond delays to ticks (argument to vTaskDelay)
#define MSToTick(t) (t/portTICK_PERIOD_MS)


void setup() {
  Serial.begin(115200);
  int err = RMTPixel.Begin(GPIO_PIN, NUM_LEDS, COLOR_ORDER);
  if (err) {
    log_e("Error %d",err);
  }
  Serial.println("Setup finished");
}

void loop() {
  RMTPixel.FillLED(0,NUM_LEDS,22,0,0); 	// Fill framebuffer with low red
  RMTPixel.Write(); 						// Start transmission
  vTaskDelay(MSToTick(DELAY));
  for (int i = 0; i<NUM_LEDS; i++) {
    RMTPixel.SetLED(i,0,0,22);			// Change i-th LED in framebuffer to low blue
    RMTPixel.Write();					// Start transmission
    vTaskDelay(MSToTick(DELAY));							// Wait before switching to next led
  }
}
