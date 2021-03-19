@0xfe6f9cc1919289ad;

# A message to represent all dashboard commands available
# For documentation about the dashboard server see 
#   - https://www.universal-robots.com/articles/ur/dashboard-server-e-series-port-29999/
#   - https://www.universal-robots.com/articles/ur/dashboard-server-cb-series-port-29999/
struct DashboardCommandProto 
{
  # Enum holding all dashboard commands available.
  enum DashboardCommand 
  {
    load                      @0;   # Load program </programs/program.urp>
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
    safetystatus              @21;  # Current safety status
    unlockProtectiveStop      @22;  # Unlocks protective stop
    closeSafetyPopup          @23;  # Close safety popup
    loadInstallation          @24;  # Load installation </programs/default.installation>
    restartSafety             @25;  # Restart safety
    isInRemoteControl         @26;  # Returns remote control status
    getSerialNumber           @27;  # Returns serial number
    getRobotModel             @28;  # Returns robot model
    safetymode                @29;  # Current safetymode
    setUserRole               @30;  # Setting user role <role>
    getUserRole               @31;  # Get current user role 
  }

  # The request/command to send to the dashboardserver.
  dashboardRequest @0: DashboardCommand;

  # Possible argument to the dashboard command can be empty.
  argument @1: Text = "";
}

# A message to represent the status of a dashboard command.
struct DashboardCommandStatusProto 
{
  # The anwser from the dashboard server.
  anwser @0: Text;

  # Returns whether the command was a succes or not.
  succes @1: Bool;
}