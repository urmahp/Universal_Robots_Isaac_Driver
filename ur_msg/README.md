# UR message

This folder contains messages developed specific to the **Universal_Robots_Isaac_Driver**.
The folder contains:

- **dashboard_command** Consist of two messages used to send dashboard commands
to the codelet **DashboardClientIsaac**. And receive the status of the command.

- **dashboardCommand** Helper functions to translate the dashboard commands from
an enum in capnp format to a C++ enum.

- **speed_slider** Consist of a message to set the actual value of the speedslider.

## Messages

The different messages are described here:

### DashboardCommandProto

```capnp
# A message to represent all dashboard commands available
# For documentation see https://www.universal-robots.com/articles/ur/dashboard-server-e-series-port-29999/
# DISCLAIMER NOT ALL COMMANDS HAS NOT BEEN TESTED
struct DashboardCommandProto {

  # Enum holding all dashboard commands available.
  enum DashboardCommand {
    load                      @0;   # Load program <program.urp>
    play                      @1;   # Play program
    stop                      @2;   # Stop program
    pause                     @3;   # Pause program
    quit                      @4;   # Disconnect client
    shutdown                  @5;   # Shut down robot
    running                   @6;   # Programm running?
    robotmode                 @7;   # Current robot mode
    getLoadedProgram          @8;   # Returns loaded program
    popup                     @9;   # Show popup <message>
    closePopup                @10;  # Close popup
    addToLog                  @11;  # Add message to log <log-message>
    isProgramSaved            @12;  # Is current program saved?
    programState              @13;  # Returns current program state
    polyscopeVersion          @14;  # Polyscope version number
    setOperationalMode        @15;  # Set operational mode <mode>
    getOperationalMode        @16;  # Returns curretn operationalmode
    clearOperationalMode      @17;  # Dashboard server no longer controls operational mode
    powerOn                   @18;  # Power on robot
    powerOff                  @19;  # Power down robot
    brakeRelease              @20;  # Brake release
    safetyStatus              @21;  # Current safetystatus
    unlockProtectiveStop      @22;  # Unlocks protective stop
    closeSafetyPopup          @23;  # Close safety popup
    loadInstallation          @24;  # Load installation <default.installation>
    restartSafety             @25;  # Restart safety
    isInRemoteControl         @26;  # Returns remote control status
    getSerialNumber           @27;  # Returns serial number
    getRobotModel             @28;  # Returns robot model
  }

  # The request/command to send to the dashboardserver.
  dashboardRequest @0: DashboardCommand;

  # Possible argument to the dashboard command can be empty.
  argument @1: Text = "";
}
```

### DashboardCommandStatusProto

```capnp
# A message to represent the status of a dashboard command.
struct DashboardCommandStatusProto {

  # The anwser from the dashboard server.
  anwser @0: Text;

  # Returns whether the command was a succes or not.
  succes @1: Bool;
}
```

### SpeedSliderProto

```capnp
# Message to set the actual value of the speedslider. Values should be between
# 0 and 1. Only set this smaller than 1 if you are using the scaledMultiJointController
# or you know what you're doing. Using this with another controller might lead to
unexpected behaviors.
struct SpeedSliderProto {
  # The speed slider value
  speedSliderValue @0 : Float32;
}
```
