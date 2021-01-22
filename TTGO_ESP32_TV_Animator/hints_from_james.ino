
class TVLight {
public:
  TVLight(unsigned long durationMin, unsigned long durationMax)	: 
    _durationMin(durationMin), 
    _durationMax(durationMax),
    _fadeStart(0),
    _duration(0),
    _nextChange(0),
    _startColor(0),
    _endColor(0) {

  }

  unsigned long update() {
    unsigned long now = millis();
    if(now > _nextChange) {
      _fadeStart = now;
      _duration = random(_durationMin, _durationMax);
      _nextChange = now + duration;
      _startColor = _endColor;
      _endColor = random(0xFFFFFF);
    }

    msSinceFadeStart = now - _fadeStart;
    float alpha = (float)msSinceFadeStart / _duration;
    float alphaComplement = 1.0 - alpha;
    currentColor = _startColor * alphaComplement + _endColor * alpha;
    
    return currentColor;
  }

private:
  //Configuration
  unsigned long _durationMin;
  unsigned long _durationMax;
  
  //State
  unsigned long _fadeStart;
  unsigned long _duration;
  unsigned long _nextChange;
  unsigned long _startColor;
  unsigned long _endColor;
};


TVLight tvLight(1000, 2000);

void setup(void) {
}

void loop() {
	unsigned long backgroundColor = tvLight.update();
	tft.fillScreen(backgroundColor);
}
