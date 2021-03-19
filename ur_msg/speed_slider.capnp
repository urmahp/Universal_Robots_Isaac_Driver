@0x94c62233ca62cd8b;

# Message to set the actual value of the speedslider. Values should be between
# 0 and 1. Only set this smaller than 1 if you are using the scaledMultiJointController
# or you know what you're doing. Using this with another controller might lead to unexpected behaviors.
struct SpeedSliderProto {
  # The speed slider value
  speedSliderValue @0 : Float32;
}