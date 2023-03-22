#include "main.h"
#include "SSD1306Wire.h"

#define WIRE Wire

// Data source section
AnalogDataSource EGTSensor = {A0, 230};

//LoRaDataSource StarterVoltage;
//LoRaDataSource CurrentSens1;

Dashboard dashboard;

// Initialize display
SSD1306Wire display(DISP_ADR, DISP_SDA, DISP_SCL);

int lastDisplayTime = millis();
int lastInputTime = millis();
bool pageChanged = false;

void setup() {
  Serial.begin(115200);

  // Create Widget for each Data Source
  UIWidget EGTSensorWidget;
  EGTSensorWidget.widgetID = 0;
  EGTSensorWidget.dataSrc.analog = EGTSensor;
  EGTSensorWidget.widgetData = 230;
  EGTSensorWidget.widgetContext = "EGT: ";
  EGTSensorWidget.init_as_analog();

  // Create Page and apply above widgets to the pages
  UIPage page0;
  page0.pageID = 0;
  page0.widgets[0] = EGTSensorWidget;
  page0.widgetCountCurrent = 1;

  // Create dashboard to display the pages
  dashboard.currentPage = 0;
  dashboard.pages[0] = page0;

  // Init display
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_16);

  // Configure button pins
  pinMode(UserButton, INPUT);

  //

  // Testing purposes
  randomSeed(analogRead(A0));
}

void drawPage(int pageNum) {
  Serial.println("Drawing page " + String(pageNum));
  display.clear();
  display.drawString(8, 16, dashboard.pages[pageNum].widgets[0].widgetContext + String(dashboard.pages[pageNum].widgets[0].dataSrc.analog.data) + "c");
  

  // Draw page indicator
  for(int i = 0; i < dashboard.pageCount; i++) {
    if(i == dashboard.currentPage){
      display.drawCircle(48 + i * 8, 60, 3);
    } else {
      display.drawCircle(48 + i * 8, 60, 2);
    }
  }



  display.display();
  
}

void loop() {

  
  if(!digitalRead(UserButton) && millis() - lastInputTime > 250) {
    // Advance to the next page
    dashboard.currentPage++;

    if(dashboard.currentPage >= dashboard.pageCount) {
      dashboard.currentPage = 0;
    }

    lastInputTime = millis();
    pageChanged = true;
    
  }

  if(millis() - lastDisplayTime > 1000 || pageChanged) {
    drawPage(dashboard.currentPage);
    lastDisplayTime = millis();
    pageChanged = false;
  }
  
  
  EGTSensor.data = random(750);

}