#include "main.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define WIRE Wire

// Data source section
AnalogDataSource EGTSensor = {A0, 230};

//LoRaDataSource StarterVoltage;
//LoRaDataSource CurrentSens1;

// Initialize display
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &WIRE);

void setup() {
  // put your setup code here, to run once:

  // Create Widget for each Data Source
  UIWidget EGTSensorWidget;
  EGTSensorWidget.widgetID = 0;
  EGTSensorWidget.dataSrc.analog = EGTSensor;
  EGTSensorWidget.widgetData = 230;
  EGTSensorWidget.widgetContext = "EGT: ";

  // Create Page and apply above widgets to the pages
  UIPage page0;
  page0.pageID = 0;
  page0.widgets[0] = EGTSensorWidget;
  page0.widgetCountCurrent = 1;

  // Create dashboard to display the pages
  Dashboard dashboard;
  dashboard.currentPage = 0;
  dashboard.pages[0] = page0;

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Address 0x3C for 128x32
  

  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  display.print("B");
  display.display();

  Serial.println("Running");



}